# the compiler: g++ for C++ program
CC = g++
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
# the build target executable:
TARGET = mylinkstate
all: $(TARGET)
$(TARGET): %:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm -rf $(TARGET)
