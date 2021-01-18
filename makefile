# specifiying the compiler to use. Here, we make use of g++ for C++
CC= g++

# compiler flags
# -g for debugging information to the executable file
# - Wall to turn on most compiler warnings
CFLAGS = -g -Wall -std=c++14

# the build target
vnc-app: main.o data_structure.o
	$(CC) $(CFLAGS) -o vnc-app main.o data_structure.o
