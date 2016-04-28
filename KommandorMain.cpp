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

class runVars{
	public:
		string runVar;
};

runVars rv;

// PROMPT
void help(){
	cout << "\nUsage: " << endl;
	cout << "help       : Displays this help prompt." << endl; 
	cout << "users      : Displays the system users." << endl; 
	cout << "groups     : Displays the system groups." << endl; 
	cout << "removeuser : Completely removes a specified user." << endl; 
	cout << "memuse     : Show the system memory usage." << endl;
	cout << "encrypt    : Encrypts a file using gpg." << endl;
	cout << "serverstat : Display the server utilization.\n" << endl;
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
	rv.runVar = "sudo userdel -r " + string( argv[2] );
	system( (rv.runVar).c_str() );
	cout << " " << endl;
}

void encryptFile( int argc, char* argv[] ){
	cout << yellow << "encrypting file " << argv[2] << normal << endl;
	rv.runVar = "sudo gpg -c " + string( argv[2] );
	system ( (rv.runVar).c_str() );
	cout << " " << endl;
}

void serverUtilization( int argc, char* argv[]){
	cout << yellow << "Displaying server utilization information: " << normal << endl;

	cout << green << "Uptime: " << normal << endl;
	system("sudo uptime");
	cout << "\n --- \n" << endl;
	
	cout << green << "Users connected: " << normal << endl;
	system("sudo who -a");
	cout << "\n --- \n" << endl;

	cout << green << "Last 3 logins: " << normal << endl;
	system("sudo last -a | head -3");
	cout << "\n --- \n" << endl;
	
	cout << green << "Most expensive processes: " << normal << endl;
	system("sudo top -b | head -10 | tail -4");
	cout << "\n --- \n" << endl;

	cout << green << "Open ports (scanned with Nmap): " << normal << endl;
	system("sudo nmap -sT localhost | grep -E \"(tcp|udp)\"");
	cout << "\n --- \n" << endl;

	cout << green << "Current connections: " << normal << endl;
	system("sudo ss -s");
	cout << "\n --- \n" << endl;


	// IN DEVELOPMENT

	/*
	char emailopt[] = "emailadmin";
	if ( string(argv[2]) == string(emailopt) ){
		cout << yellow << "Emailing administrator: " << normal << endl;
		system("kommandor serverstat | mail -s 'Kommandor serverstat output' root ");
		cout << "OK." << endl;
		cout << " " << endl;
	}
	*/
	
}

// show system memory
void showMemory(){
	cout << yellow << "Displaying memory usage: \n" << normal << endl;

	cout << green << "\nused memory: " << normal << endl;
	system("vmstat -s -SM | grep used | grep memory | sed -e 's/^[ \t]*//'");
	cout << "\n --- \n" << endl;

	cout << green << "\nused swap: " << normal << endl;
	system("vmstat -s -SM | grep used | grep swap | sed -e 's/^[ \t]*//'");
	cout << "\n --- \n" << endl;

	cout << green << "\nfree disk space: " << normal << endl;
	system("df -h | grep -v Filesystem");
	cout << "\n --- \n" << endl;

	cout << green << "\ncpu usage: " << normal << endl;
	system("lscpu | grep CPU");
	cout << "\n --- \n" << endl;

	cout << green << "\nload average: " << normal << endl;
	double load[3];  
   	if (getloadavg(load, 3) != -1){  
   		printf("%f , %f , %f\n", load[0],load[1],load[2]);
		if ( load [0] > 0.50 ){
			cout << red << "CPU load average is above 0.50!" << normal << endl;
		}
	}
	cout << "\n --- \n" << endl;

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
	else if ( argtest == "encrypt" ){
		encryptFile( argc, argv );
	}
	else if ( argtest == "serverstat" ){
		serverUtilization( argc, argv );
	}
	else{
		cout << red << "\nargument not found.\n" << normal << endl;
		help();
	}
	return 0;
}

