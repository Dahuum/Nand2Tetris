/* Assembler.cpp */ 

#include "Assembler.hpp"

void Assembler::assemble(string inFile, string outFile) {
	
	initSymbolTable();
	ifstream inputFile(inFile);
	ofstream outputFile(outFile);

	if (inputFile.is_open()) {
		string line; int romAddress = 0;

		PassOne(inputFile, line, romAddress);
		inputFile.clear(); inputFile.seekg(0);
		PassTwo(inputFile, outputFile, line);

		//Assembler::printMap();
		inputFile.close();
		outputFile.close();
	} 
	else cerr << "Error in opening file." << endl;
}

void Assembler::PassTwo(ifstream& inputFile, ofstream& outputFile, string& line) {
	while (getline(inputFile, line)) {
		string cleanedLine = cleanLine(line);
		if (cleanedLine == "" || isLabel(cleanedLine)) continue;

		if (cleanedLine[0] == '@') {
			string binary = aInstructionToBinary(cleanedLine.erase(0, 1));
			outputFile << binary + '\n';
		} else {
			string binary = cInstructionToBinary(cleanedLine);
			outputFile << binary + '\n';
		}
	}	
}

void Assembler::PassOne(ifstream& inputFile, string& line, int& romAddress)  {
	while (getline(inputFile, line)) {
		string cleanedLine = cleanLine(line);
		
		if (cleanedLine == "") continue;
		else if (Assembler::isLabel(cleanedLine)) {
			string label = Assembler::extractLabel(cleanedLine);
			Assembler::symbolTable[label] = romAddress;
		}
		else romAddress++;
	}
}

vector<string> Assembler::split(const string& s, const string& delimiters) {
	vector<string> tokens;
	size_t lastPos = 0;
	size_t pos = s.find_first_of(delimiters, lastPos);

	while (pos != string::npos) {
		tokens.push_back(s.substr(lastPos, (pos - lastPos)));
		lastPos = pos+1;
		pos = s.find_first_of(delimiters, lastPos);
	}
	tokens.push_back(s.substr(lastPos)); // latest we7da
	return tokens;
}

/* 111accccccdddjjj
 *
 * 1: dest=comp 
 * 2: comp;jmp 
 * 3: dest=comp;jmp 
 * 4: comp 
 *
 * */
string Assembler::cInstructionToBinary(string s) {
	vector<string> tokens = split(s, "=;");
	string binary, empty = "";

	for (auto &tok : tokens)
    	std::transform(tok.begin(), tok.end(), tok.begin(), ::toupper);


	if (tokens.size() == 1) {
			binary = compMap[tokens[0]] + destMap[empty] + jumpMap[empty];
			return "111" + binary;
	} else if (tokens.size() == 2) {
		if (tokens[1][0] == 'J') binary = compMap[tokens[0]] + destMap[empty] + jumpMap[tokens[1]];
		else binary = compMap[tokens[1]] + destMap[tokens[0]] + jumpMap[empty];
		return "111" + binary;
	} else {
		return "111" + compMap[tokens[0]] + destMap[tokens[1]] + jumpMap[tokens[2]];
	}
	return "";
}

string Assembler::aInstructionToBinary(string value) {
	char *p;
	const char *s = value.c_str();
	long converted = strtol(s, &p, 10);

	if (*p) {
		if (symbolTable.find(value) == symbolTable.end()) symbolTable[value] = nextRamAddress++;
		
		string binary = bitset<15>(symbolTable[value]).to_string();
		return "0" + binary;
	}
	string binary = bitset<15>(converted).to_string();
	return "0" + binary;
}

void Assembler::initSymbolTable() {
	/* R0 -> R15, and other predefined ones */
	for (int i = 0; i <= 15; i++) 
		Assembler::symbolTable["R" + to_string(i)] = i;

	Assembler::symbolTable["SP"] 	 = 0;
	Assembler::symbolTable["LCL"] 	 = 1;
	Assembler::symbolTable["ARG"] 	 = 2;
	Assembler::symbolTable["THIS"] 	 = 3;
	Assembler::symbolTable["THAT"] 	 = 4;
	Assembler::symbolTable["SCREEN"] = 16384;
	Assembler::symbolTable["KBD"] 	 = 24576; 
}

string Assembler::extractLabel(string line) {
	// return [1 -- size - 1]
	return line.substr(1, line.size() - 2);
}

bool Assembler::isLabel(string line) {
	if (line[0] != '(' && line[line.size() - 1] != ')') return false;
	return true;
}

string Assembler::cleanLine(string line) {
	line.erase(line.size() - 1);
	if (line.empty()) return "";

	auto it = find_if(line.begin(), line.end(), [](unsigned int c) { return !isspace(c);});
	if (it != line.end()) {
		if (*it == '/' && *it++ == '/') return "";
		size_t foundPos = line.find('/'); // i think i got an better way to do it
		if (foundPos != string::npos) line.erase(foundPos);
	}
	boost::trim(line);
	return line;
}

// Helper function: Print symboltable unordered Map
void Assembler::printMap() {
	 for (const auto& pair: Assembler::symbolTable) {
		cout << "[  " << pair.first << ", " << pair.second << "  ]" << endl;
	}
}

int main (int ac, char* av[]) {
	Assembler assembler;

	string inFile= av[1], temp = av[1];
	string outFile = temp.erase(temp.size() - 4) + ".hack";

	try { assembler.assemble(inFile, outFile);
	} catch (const exception& e) { cerr << "An unknown error occurred --> " << e.what()  << endl; }
}
