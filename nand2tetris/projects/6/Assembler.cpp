/* Assembler.cpp */ 

#include "Assembler.hpp"

void Assembler::assemble(string inFile, string outFile) {
	

	ifstream inputFile(inFile);
	if (inputFile.is_open()) {
		string line;
		int romAddress = 0;

		while (getline(inputFile, line)) {
			string cleanedLine = cleanLine(line);
			
			if (cleanedLine == "") continue;
			else if (Assembler::isLabel(cleanedLine)) {
				string label = Assembler::extractLabel(cleanedLine);
			cout << "label: " << label << endl;
			Assembler::symbolTable[label] = romAddress;
		}
		else romAddress++;
		cout << "'" << cleanedLine << "'" << ",   " << "romAddress: " << romAddress << endl;
		}
		Assembler::printMap();
		inputFile.close();
	} 
	else cerr << "Error in opening file." << endl;
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
	try {
		assembler.assemble(av[1], av[2]);
	} catch (const logic_error& e) {
		cerr << "An unknown error occurred --> " << e.what()  << endl;
	}

}
