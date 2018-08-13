CC = g++
CFLAGS = -std=c++11 -fopenmp -Wall -Ofast
INCLUDES = 
LDFLAGS = -lpthread
SOURCES = hello_omp.cpp
OUTF = hello_omp

$(OUTF): hello_omp.o
	$(CC) $(CFLAGS) -o $(OUTF) $< $(LDFLAGS)

hello_omp.o: $(SOURCES)
	$(CC) $(CFLAGS) -c $<

rebuild: clean $(OUTF)

clean:
	rm *.o hello_omp