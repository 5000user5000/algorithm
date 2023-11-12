CC = g++
CFLAGS = -std=c++11 -Wall

SRC = ./src/maxPlanarSubset.cpp  # source files
OUT = ./bin/mps  #  output executable file

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(OUT) 
