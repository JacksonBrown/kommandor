#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//INITAL VARIABLES
char blue[] = { 0x1b, '[', '1', ';', '3', '4', 'm', 0 };
char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };

// INITIAL VARIABLE CLASS
class InputVars{
public:
	string input;
	string inputPrompt;
};

static InputVars InpV;

// OPEN PROMPT STREAM
void inputPromptGen(){

	ifstream promptFileStream;
	promptFileStream.open("input_prompt");
	string promptOutput;

	if ( promptFileStream.is_open() ){
		while ( !promptFileStream.eof() ){
			promptFileStream >> promptOutput;
			InpV.inputPrompt = promptOutput;
		}
	}

	promptFileStream.close();

}

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

// INPUT PROMPT
void userInput(){
	string userInput;
	string userInputPrompt = InpV.inputPrompt + " ";

	cout << userInputPrompt;
	cin >> userInput;

	InpV.input = userInput;

	if ( userInput == "help" ){
		help();
	}
}

int main(){
	inputPromptGen();
	prompt();
	userInput();
	return 0;
}
