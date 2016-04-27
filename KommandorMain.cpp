#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

//INITAL VARIABLES
char blue  [] = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
char red   [] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char green [] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
char yellow[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };

// PROMPT
void help(){
	cout << "\nUsage: " << endl;
	cout << "help       : Displays this help prompt." << endl; 
	cout << "users      : Displays the system users." << endl; 
	cout << "groups     : Displays the system groups." << endl; 
	cout << "removeuser : Completely removes a specified user.\n" << endl; 
	cout << "memuse     : Show the system memory usage."
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
		passwd.close();
	}else{
		cout << red << "/etc/passwd not found." << normal << endl;
	}
	passwd.close();
}

void showGroups( int argc, char* argv[] ){
	ifstream group("/etc/group");

	if( group ){
		cout << yellow << "Displaying groups in the system: " << normal << endl;
		system("cat /etc/group");
		cout << " " << endl;
		group.close();
	}else{
		cout << red << "/etc/group not found." << normal << endl;
	}
	group.close();
}

// PROMPT
void prompt(){
	cout << blue << "\nKommandor v0.01 by Jackson Brown (jacksonconnerbrown@gmail.com)" << normal << endl; 
}

void removeUser( int argc, char* argv[] ){
	cout << yellow << "removing user " << argv[2] << normal << endl;
	string username = "sudo userdel -r " + string(argv[2]);
	system( (username).c_str() );
	cout << " " << endl;
}

// show system memory
void showMemory(){
	cout << yellow << "Displaying memory usage: " << normal << endl;

	cout << green << "\nused memory: " << normal << endl;
	system("vmstat -s -SM | grep used | grep memory | sed -e 's/^[ \t]*//'");

	cout << green << "\nused swap: " << normal << endl;
	system("vmstat -s -SM | grep used | grep swap | sed -e 's/^[ \t]*//'");

	cout << green << "\nfree disk space: " << normal << endl;
	system("df -h | grep -v Filesystem");

	cout << green << "\ncpu usage: " << normal << endl;
	system("lscpu | grep CPU");

	cout << green << "\nload average: " << normal << endl;
	double load[3];  
   	if (getloadavg(load, 3) != -1){  
   		printf("%f , %f , %f\n", load[0],load[1],load[2]);
		if ( load [0] > 0.50 ){
			cout << red << "CPU load average is above 0.50!" << normal << endl;
		}
	}

	cout << " " << endl;
}

int main(int argc, char* argv[]){
	prompt();
	if (argc < 2){
		help();
		return 1;
	}
	string argtest = argv[1];
	if ( argtest == "help" ){
		help();
	}
	else if ( argtest == "users" ){
		showUsers();
	}
	else if ( argtest == "removeuser" ){
		removeUser( argc, argv );
	}
	else if ( argtest == "groups" ){
		showGroups( argc, argv );
	}
	else if ( argtest == "memuse" ){
		showMemory();
	}
	else{
		cout << red << "\nargument not found.\n" << normal << endl;
		help();
	}
	return 0;
}

