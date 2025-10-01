/* Assembler.hpp */ 

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;
class Assembler {
	private:
		unordered_map<string, int> symbolTable;
		int nextRamAddress = 16;

	public:
		void assemble(string, string);
	private:
		string cleanLine(string line);
		bool isLabel(string line);
		string extractLabel(string line);
		string aInstructionToBinary(string value);
		string cInstructionToBinary(string line);
		void initSymbolTable();
	
		void printMap();	
};
