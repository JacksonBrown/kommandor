#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

char blue   []    = { 0x1b, '[', '0', ';', '3', '4', 'm', 0 };
char normal []    = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
char red    []    = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char cyan   []    = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
char green  []    = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };

// HELP OUTPUT
// LET THIS ACT AS A MAP FOR THIS FILE
void help(){

    cout << cyan << "\nhelp    " << normal << "   show this help prompt." << endl;
    cout << cyan << "emailalias" << normal << " edit the /etc/aliases file, then compile the changes.\n" << endl;

}

void emailAlias(){

    if ( ifstream("/etc/aliases") ){
        system("vim /etc/aliases");
    }else{
        cout << red << "\n/etc/aliases file not found\n" << normal << endl;
    }

}
