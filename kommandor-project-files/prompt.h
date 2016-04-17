#include <iostream>
#include <fstream>

using namespace std;

//INITAL VARIABLES
char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };

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
