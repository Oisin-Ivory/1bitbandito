LIBS=-L"C:/SFML_MW/lib" -L"C:/TGUI_MW/lib" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CXX := g++
BIN= ./
SRC_DIR := src/
INC_DIR := include/
OBJ_DIR := obj/
SRC_FILES := $(wildcard $(SRC_DIR)*.cpp) $(wildcard $(SRC_DIR)/components/*.cpp)
OBJ_FILES :=  $(patsubst %.cpp,%.o,$(SRC_FILES))
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
COMPILEROPTIONS = -Lstatic-libgcc -Lstatic-libstdc++

LDFLAGS :=

CPPFLAGS := -Iincludes -Iincludes/components -I "C:/SFML_MW/include" -I"C:/TGUI_MW/include"
%.o: %.cpp
	$(CXX) $(COMPILEROPTIONS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

%.o: %.hpp
	$(CXX) $(COMPILEROPTIONS) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(COMPILEROPTIONS) $(CPPFLAGS) -c $< -o $@

all: 1bitbandito

.PHONY: all clean

clean: 
	rm $(OBJ_DIR)*.o 1bitbandito $(SRC_DIR)*.o $(SRC_DIR)/components/*.o

1bitbandito: $(OBJ_FILES)
	$(CXX) $(COMPILEROPTIONS) $(LDFLAGS) -o $(BIN)$@ $^ $(LIBS)

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

-include $(OBJ:.o=.d)