#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <strings.h>
#include <bitset>
#include <fstream>

using namespace std;
using namespace cv;

string readFile(string name){

    string result; 
    string aux; 

    ifstream f (name);

    if (!f.is_open())
    perror("error while opening file");

    while (getline(f, aux)){

        result+=aux;

    }

    f.close();

    return result;
}

void cipher (unsigned char* &input, unsigned char* &output, int cols, int rows, string word){

    int sizeWord = word.length();
    
    for (int i = 0; i < sizeWord; i++){

        unsigned char ca = word[i];

        for(int x = 0; x < 8; x++){

            int bit = (ca >> x) & 1U;
            
            unsigned char imgColor = input[(i*8)+x];

            if(bit)
            {
                imgColor |= 1 << 0;
            }
            else
            {
                imgColor = imgColor & ~(1u<<0);
            }

            output[(i*8)+x]= imgColor;
        } 
    }
}

void decipher (unsigned char* input, int width, int height, unsigned char * word){

    int totalSize = height * width;

    for ( int i = 0; i < totalSize/8; i++){

        int index = i*8;

        unsigned char letra;

        for(int j = 0; j < 8; j++){

            unsigned char color = input[index+j];

            int bit = (color >> 0) & 1U;

            if(bit)
            {
                letra |= 1 << j;
            }
            else
            {
                letra = letra & ~(1u<<j);
            
            } 
        }  

        word[i] = letra;
    }
}

void readImageFile(string file){

    Mat image;
    Mat output; 

    image = imread(file, CV_LOAD_IMAGE_COLOR);

    size_t colorBytes = image.step * image.rows;

    unsigned char * image1D = new unsigned char [colorBytes];
    unsigned char * output1D = new unsigned char [colorBytes];

    memcpy(image1D, image.ptr(), colorBytes);
    memcpy(output1D, image.ptr(), colorBytes);

    int answ;
    string text;

    cout << "¿Qué deseas hacer?" << endl;
    cout << "1. Codificar un mensaje" << endl;
    cout << "2. Decodificar un mensaje" << endl;
    cin >> answ;

    if(!image.data)
    {
        cout <<  "Could not open or find the image" << std::endl ;
        
    }else{

        int x = image.cols;
        int y = image.rows;

        int totalWords = (y*x)/8;

        unsigned char * word = new unsigned char[x*y];

        cout << "Input image step: " << image.step << " cols: " << x << " rows: " << y << " Total characters: " << totalWords << endl;

        switch(answ){

            case 1: {

                cout << "¿De qué archivo desea obtener el mensaje?" << endl;
                cin >> text;
                string message = readFile(text);
                cout << "Número de caracteres del texto: " << message.length() << endl;
                cipher(image1D, output1D, x, y, message);
                Mat output = Mat(image.rows, image.cols,CV_8UC3, output1D);
                imwrite( "coded_Image.png", output);
                cout << "Imagen codificaca en: 'coded_Image.png'"<< endl;
                break;
            }
            case 2: {
                
                decipher(image1D,x,y,word);
                ofstream exit ("mensaje.txt");
                exit << word;
                exit.close();
                cout << "mensaje guardado en: mensaje.txt" << endl;
                break;

            }
            default: {

                cout << "Opción no valida" << endl;
                break;
            }
        }

        /*image = Mat(image.rows,image.cols,CV_8UC3, image1D);
        Mat output = Mat(image.rows, image.cols,CV_8UC3, output1D);

        /*namedWindow("Original", cv::WINDOW_NORMAL);
        resizeWindow("Original", 800, 600);
        imshow("Original", image);
        namedWindow("Output", cv::WINDOW_NORMAL);
        resizeWindow("Output", 800, 600);
        imshow("Output", output);*/
    }

}


int main (int argc, char** argv){

    if (argc < 2){
         
        cout << "No hay argumentos suficientes" << endl;

    }else{

        auto startTime = chrono::high_resolution_clock::now();
        readImageFile(argv[1]);
        auto endTime = chrono::high_resolution_clock::now();
        chrono::duration<float, std::milli> duration_ms = endTime - startTime;

        printf("Tiempo transcurrido:  %f ms \n", duration_ms.count());

    }
    waitKey(0); 

    return 0;
}