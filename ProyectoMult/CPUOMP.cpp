#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <math.h>
#include <strings.h>
#include <omp.h>
#include <pthread.h>
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

    int i;

    #pragma omp parallel for private(i) shared(input, output, word)
    
    for (i = 0; i < sizeWord; i++){

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

    int i;

    #pragma omp parallel for private(i) shared(input, word)

    for (i = 0; i < totalSize; i++){

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

            for (int x = 0; x < 8 ; x++){

                int a = (letra >> x) & 1U;
  
            } 
        }  

        word[i] = letra;
    }
}

void readImageFile(string file, string text){

    Mat image;
    Mat output; 

    image = imread(file, CV_LOAD_IMAGE_COLOR);

    size_t colorBytes = image.step * image.rows;

    unsigned char * image1D = new unsigned char [colorBytes];
    unsigned char * output1D = new unsigned char [colorBytes];

    memcpy(image1D, image.ptr(), colorBytes);
    memcpy(output1D, image.ptr(), colorBytes);

    if(!image.data)
    {
        cout <<  "Could not open or find the image" << std::endl ;
        
    }else{

        int x = image.cols;
        int y = image.rows;

        int totalWords = (y*x)/8;

        unsigned char * word = new unsigned char[x*y];

        cout << "Input image step: " << image.step << " cols: " << x << " rows: " << y << " Total characters: " << totalWords << endl;
        
        string a = readFile(text);

        cipher(image1D, output1D, x, y, a);

        decipher(output1D,x,y,word);

        cout << "mensaje: " << word << endl;

        /*image = Mat(image.rows,image.cols,CV_8UC3, image1D);
        Mat output = Mat(image.rows, image.cols,CV_8UC3, output1D);

        /*namedWindow("Original", cv::WINDOW_NORMAL);
        resizeWindow("Original", 800, 600);
        imshow("Original", image);
        namedWindow("Output", cv::WINDOW_NORMAL);
        resizeWindow("Output", 800, 600);
        imshow("Output", output);

        imwrite( "coded_Image.png", output);*/
    }

}

int main (int argc, char** argv){

    if (argc < 3){
         
        cout << "No hay argumentos suficientes" << endl;

    }else{

        auto startTime = chrono::high_resolution_clock::now();
        readImageFile(argv[1], argv[2]);
        auto endTime = chrono::high_resolution_clock::now();
        chrono::duration<float, std::milli> duration_ms = endTime - startTime;

        printf("Tiempo transcurrido:  %f ms \n", duration_ms.count());

    }
    waitKey(0); 

    return 0;
}