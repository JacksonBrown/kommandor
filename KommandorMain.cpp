#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

//INITAL VARIABLES
char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };

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

void showUsers(){
	system("cat /etc/passwd | grep bash");
	cout << "\n --- \n" << endl;
}

// PROMPT
void prompt(){
	ifstream promptMainStream;
	promptMainStream.open("prompt");
	string mainPrompt;

	if ( promptMainStream.is_open() ){
		while ( !promptMainStream.eof() ){
			getline(promptMainStream,mainPrompt);
			cout << "\n" << blue << mainPrompt << normal << endl;
		}
	}

	promptMainStream.close();
}

void run_test( string x ){
	if (x == "help" ){
		help();
	}
	else if ( x == "users" ){
		showUsers();
	}
} 

int main(int argc, char* argv[]){
	prompt();
	if (argc < 2){
		cerr << "no options are present." << endl;
		help();
		return 1;
	}
	run_test(argv[1]);
	return 0;
}
