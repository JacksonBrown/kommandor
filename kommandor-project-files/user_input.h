#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

void userInput();

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

// USER INPUT WHILE LOOP
void userInputLoop(string x){
    while ( x != "exit" ){
        if (x == "help"){
            help();
            userInput();
        }
        else if (x == "exit"){
            cout << " Goodbye :) " << endl;
        }
    }
}

// INPUT PROMPT
void userInput(){
	string userInputVar;
	string userInputPrompt = InpV.inputPrompt + " ";

	cout << userInputPrompt;
	cin >> userInputVar;

	InpV.input = userInputVar;
	userInputLoop(userInputVar);
}


