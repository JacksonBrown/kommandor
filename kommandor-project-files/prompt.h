#include <iostream>
#include <fstream>

using namespace std;

// PROMPT
void prompt(){

	ifstream promptMainStream;
	promptMainStream.open("prompt");
	string mainPrompt;

	if ( promptMainStream.is_open() ){
		while ( !promptMainStream.eof() ){
			getline(promptMainStream,mainPrompt);
			cout << blue << mainPrompt << normal << endl;
		}
	}

	promptMainStream.close();

}
