CXXFLAGS += -I/opt/homebrew/opt/boost/include
LDFLAGS  += -L/opt/homebrew/opt/boost/lib

all: 
	c++ -std=c++20  Assembler.cpp -o assembler -g -O0 $(CXXFLAGS) $(LDFLAGS) 

clean: 
	rm -rf assembler 

re: clean all
