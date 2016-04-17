#include <iostream>
#include <fstream>

using namespace std;

// PROMPT
void help(){

	ifstream helpStream;
	helpStream.open("README.md");
	string helpVar;

	if ( helpStream.is_open() ){
		while ( !helpStream.eof() ){
			getline(helpStream,helpVar);
			cout << helpVar << endl;
		}
	}

	helpStream.close();

}
