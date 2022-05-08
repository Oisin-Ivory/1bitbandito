CC := g++
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
INC=-I "C:/SFML_MW/include"
LIBFILES=-L"C:/SFML_MW/lib"
SRC_FILES := $(wildcard *.cpp)
HEADER_SRC_FILES := $(wildcard *.hpp)
COMPILEROPTIONS = -static-libgcc -static-libstdc++

all: leveleditor

leveleditor: main.o
	$(CC) $(COMPILEROPTIONS) $(SRC_FILES) $(HEADER_SRC_FILES) -o main $(LIBFILES) $(LIBS) $(INC)
main.o: main.cpp
	$(CC) $(COMPILEROPTIONS) -c $(SRC_FILES) $(HEADER_SRC_FILES) $(INC) $(LIBS)
clean:
	del *.o leveleditor
	
	