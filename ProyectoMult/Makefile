CC = g++
CFLAGS = -std=c++11 -fopenmp -Wall -Ofast -lopencv_core -lopencv_highgui -lopencv_imgproc -Dlopencv_imgcodecs
INCLUDES = 
LDFLAGS = -lpthread
SOURCES = CPUOMP.cpp
OUTF = CPUOMP.exe

$(OUTF): CPUOMP.o
	$(CC) $(CFLAGS) -o $(OUTF) $< $(LDFLAGS)

CPUOMP.o: $(SOURCES)
	$(CC) $(CFLAGS) -c $<

rebuild: clean $(OUTF)

clean:
	rm *.o CPUOMP