#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

//INITAL VARIABLES
char blue  [] = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
char red   [] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
char yellow[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };

// PROMPT
void help(){
	ifstream helpStream;
	helpStream.open("README.md");
	string helpVar;
	cout << " " << endl; // gen blank line 

	if ( helpStream.is_open() ){
		while ( !helpStream.eof() ){
			getline(helpStream,helpVar);
			cout << helpVar << endl;
		}
	}

	helpStream.close();
}

// show the system users delimited by shell
void showUsers(){
	ifstream passwd("/etc/passwd");

	if ( passwd ){
		cout << yellow << "\nUsers with bash shell: " << normal << endl;
		system("cat /etc/passwd | grep bash");
		cout << "\n --- \n" << endl;

		cout << yellow << "\nUsers with zsh shell: " << normal << endl;
		system("cat /etc/passwd | grep zsh");
		cout << "\n --- \n" << endl;

		cout << yellow << "\nUsers with ksh shell: " << normal << endl;
		system("cat /etc/passwd | grep ksh");
		cout << "\n --- \n" << endl;
	}else{
		cout << red << "/etc/passwd not found." << normal << endl;
	}
}

// PROMPT
void prompt(){
	ifstream promptMainStream;
	promptMainStream.open("prompt");
	string mainPrompt;
	cout << " " << endl;

	if ( promptMainStream.is_open() ){
		while ( !promptMainStream.eof() ){
			getline(promptMainStream,mainPrompt);
			cout << blue << mainPrompt << normal << endl;
		}
	}

	promptMainStream.close();
}

void editNetwork(){
	ifstream interfaces("/etc/network/interfaces");

	if( interfaces ){
		cout << yellow << "Opening the interfaces file for editing" << normal << endl;
		system("sudo vi /etc/network/interfaces");
	}else{
		cout << red << "/etc/network/interfaces file not found." << normal << endl;
	}
}

void run_test( string x ){
	if (x == "help" ){
		help();
	}
	else if ( x == "users" ){
		showUsers();
	}
	else if ( x == "editnetwork" ){
		editNetwork();
	}
} 

int main(int argc, char* argv[]){
	prompt();
	if (argc < 2){
		help();
		return 1;
	}
	run_test(argv[1]);
	return 0;
}
