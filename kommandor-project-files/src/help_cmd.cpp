#include "help_cmd.h"
#include <fstream>

help_cmd::help_cmd()
{
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
}

help_cmd::~help_cmd()
{
    //dtor
}
