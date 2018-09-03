CC = g++
CFLAGS = -std=c++11 -Wall -Ofast
INCLUDES = 
LDFLAGS = -lpthread
SOURCES = hello_threads.cpp
OUTF = hello_threads

$(OUTF): hello_threads.o
	$(CC) $(CFLAGS) -o $(OUTF) $< $(LDFLAGS)

hello_threads.o: $(SOURCES)
	$(CC) $(CFLAGS) -c $<

rebuild: clean $(OUTF)

clean:
	rm *.o hello_threads