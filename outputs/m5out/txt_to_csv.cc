#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv) {
	if(argc != 2) {
		cerr << "Usage: " << argv[0] << " [file.txt]" << endl;
		exit(1);
	}

	string input_name(argv[1]);
	size_t eq = input_name.find('.');
	string output_name = input_name.substr(0, eq);	
	output_name += ".csv";

	ifstream input_stream;
    input_stream.open(argv[1]);
	ofstream output_stream(output_name);

    if(input_stream.is_open() && output_stream.is_open()) {
		string line;	
		while(getline(input_stream, line)) {
			if(line.size() == 0 || line[0] == '-') continue;
			size_t eq = line.find('#');
			string front = line.substr(0, eq);
			string back = line.substr(eq, line.size() - 1);

			unsigned space = 0;	
			for(auto it= front.begin(); it != front.end(); ++it) {
				if(*it == ' ' || *it == '\t') {
					if(space == 0)
						output_stream << ',';
					space++;
				}
				else {
					output_stream << *it;
					space = 0;
				}
			}
			output_stream << "," << back << "\n";
		}
	}
	return 0;
}
