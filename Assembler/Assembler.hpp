/* Assembler.hpp */ 

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <bitset>
#include <boost/algorithm/string.hpp>

using namespace std;
class Assembler {

	private:
		unordered_map<string, int> symbolTable;
		int nextRamAddress = 16;
		unordered_map<string, string> compMap = {
    		// a=0 (A register)
		    {"0",   "0101010"}, {"1",   "0111111"}, {"-1",  "0111010"},
    		{"D",   "0001100"}, {"A",   "0110000"}, {"!D",  "0001101"},
    		{"!A",  "0110001"}, {"-D",  "0001111"}, {"-A",  "0110011"},
    		{"D+1", "0011111"}, {"A+1", "0110111"}, {"D-1", "0001110"},
    		{"A-1", "0110010"}, {"D+A", "0000010"}, {"D-A", "0010011"},
    		{"A-D", "0000111"}, {"D&A", "0000000"}, {"D|A", "0010101"},

    		// a=1 (M register)
    		{"M",   "1110000"}, {"!M",  "1110001"}, {"-M",  "1110011"},
    		{"M+1", "1110111"}, {"M-1", "1110010"}, {"D+M", "1000010"},
    		{"D-M", "1010011"}, {"M-D", "1000111"}, {"D&M", "1000000"},
    		{"D|M", "1010101"}
		};

		unordered_map<string, string> destMap = {
    		{"",    "000"}, {"M",   "001"}, {"D",   "010"}, {"MD",  "011"},
    		{"A",   "100"}, {"AM",  "101"}, {"AD",  "110"}, {"AMD", "111"}
		};

		unordered_map<string, string> jumpMap = {
    		{"",    "000"}, {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"},
    		{"JLT", "100"}, {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"}
		};

	public:
		void assemble(string, string);

	private:
		
		void PassOne(ifstream&, string&, int&);
		void PassTwo(ifstream&, ofstream&, string&);
		string cleanLine(string);
		bool isLabel(string);
		string extractLabel(string);
		string aInstructionToBinary(string);
		string cInstructionToBinary(string);
		void initSymbolTable();
	
		void printMap();	
		vector<string> split(const string&, const string&);
};
