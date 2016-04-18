#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void userInputLoop(string x);

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

// INPUT PROMPT
void userInput(){
	string userInputVar = "";
	string userInputPrompt = InpV.inputPrompt + " ";

    cout << green << endl;
	cout << userInputPrompt;
	cout << normal;
	cin >> userInputVar;

	InpV.input = userInputVar;
	userInputLoop(userInputVar);
}

// USER INPUT WHILE LOOP
void userInputLoop(string x){
    if (x == "help"){
        help();
        userInput();
    }
    else if (x == "emailalias"){
        emailAlias();
        userInput();
    }
    else if (x == "exit")
        cout << "Good Bye :) " << endl;
    else{
        system( (x).c_str() );
        userInput();
    }
}
