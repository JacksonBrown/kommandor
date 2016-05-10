#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdbool.h>
#include <unistd.h>
#include <vector>
#include <sstream>

using namespace std;

//INITAL VARIABLES
char blue  [] = { 0x1b, '[', '0', ';', '3', '6', 'm', 0 };
char red   [] = { 0x1b, '[', '0', ';', '3', '1', 'm', 0 };
char green [] = { 0x1b, '[', '0', ';', '3', '2', 'm', 0 };
char normal[] = { 0x1b, '[', '0', ';', '3', '9', 'm', 0 };
char yellow[] = { 0x1b, '[', '0', ';', '3', '3', 'm', 0 };

// RUN VARIABLE CLASS
class runVars{
	public:
		string runVar;
};

// RUN VARIABLE INSTANE
runVars rv;

// GENERATE HELP FUNCTION
void help(){

        // USAGE SYNTAX
        //cout << blue << "\nUsage: " << normal << endl;
        cout << "\nUsage: " << endl;
        cout << "kommandor [options] [parameters] " << endl;

        // OPTIONS
        //cout << blue << "\nOptions: " << normal << endl;
        cout << "\nOptions: " << endl;
        cout << "help        : Displays this help prompt." << endl;
        cout << "users       : Displays the system users." << endl;
        cout << "addusers    : Adds the listed users in an interactive prompt." << endl;
        cout << "groups      : Displays the system groups." << endl;
        cout << "removeusers : Completely removes a specified user." << endl; 
        cout << "memuse      : Show the system memory usage." << endl;
        cout << "encrypt     : Encrypts a file using gpg." << endl;
        cout << "serverstat  : Display the server utilization." << endl;
        cout << "iptobinary  : Converts the following IP address to binary notation." << endl;
        cout << "setiptable  : Interactively generate iptables firewalls. \n" << endl;
}

// COLOR PRINT FUNCTIONS
void pcol( string x, string y ){

	// GREEN SETTING
	if      ( x == "green"  )
		cout << green  << y << normal << endl;

	// RED SETTING
	else if ( x == "red"    )
		cout << red    << y << normal << endl;

	// BLUE SETTING
	else if ( x == "blue"   )
		cout << blue   << y << normal << endl;

	// YELLOW SETTING
	else if ( x == "yellow" )
		cout << yellow << y << normal << endl;

}

// BINARY STRING FOR IP
string toBinary(vector<int> octets){

	// GENERATE RESULT STRING
	string result;

	// FOR UNSIGNED J IN THE OCTET SIZE
	for (unsigned j=0; j < octets.size(); j++){

		// IF J IS GREATER THAN 0
		if (j>0)

			// CONCAT. A PERIOD TO THE BINARY RESULT
			result += '.';

		// SET THE MASK INTEGER
		int mask = 256;

		// WHILE MASK IS GREATER THAN OR EQUAL TO 1
		while (mask>>=1)

			// RESULT ADDS 0 + J IN OCTETS AND MASK INT DIFF THAN 0
			result += '0' + ((octets[j] & mask ) != 0);
	}

	// RETURN THE RESULT STRING
	return result;

}


// CONVERT STRING TO INT VECTOR
int getOctets(string ip, vector<int> &octets){

	// GENERATE SSTREAM
	stringstream ss(ip);

	// GENERATE TEMP STRING
	string temp;

	// WHILE GETLINE OF SS, TEMP, AND PERIOD
	while (getline(ss,temp,'.'))

		// PUSHBACK OCTETS, GENERATE C STRING
		octets.push_back(atoi(temp.c_str()));

	// RETURN 0
	return 0;

}

// GENERTE ERROR CALL FUNCTION
void err_call( string x ){

	// PRINT STIRNG IN RED
	cout << red << x << normal << endl;

	// PRINT BLANK LINE
	cout << "  " << endl;

}

// SHOW USERS FUNCTION
void showUsers(){

	// GENERATE INPUT FILE STREAM FOR PASSWD CHECK
	ifstream passwd("/etc/passwd");

	// IF PASSWD IS EXISTING
	if ( passwd ){

		// SHOW BASH SHELL USERS
		pcol("yellow", "\nUsers with bash shell: ");
		system("cat /etc/passwd | grep bash");
		cout << "\n --- \n" << endl;

		// SHOW ZSH SHELL USERS
		pcol("yellow", "Users with zsh shell: ");
		system("cat /etc/passwd | grep zsh");
		cout << "\n --- \n" << endl;

		// SHOW KSH SHELL USERS
		pcol("yellow", "Users with ksh shell: ");
		system("cat /etc/passwd | grep ksh");
		cout << "\n --- \n" << endl;

		// CLOSE THE PASSWD FILE STREAM
		passwd.close();
	}else{

		// IF PASSWD IS NOT FOUND SHOW THIS
		err_call("/etc/passwd file not found.");

	}

	// CLOSE THE PASSWD FILE STREAM
	passwd.close();

}

// ADD USERS FUNCTIION
void addUsers( int argc, char* argv[] ){

	// IF ARGUMENTS ARE ADEQUIT
	if ( argc < 3){

		// IF NOT PRINT THIS
		err_call("missing parameters.");

	}
	else{

		// SHOW ADDING USER PROMPT
		cout << yellow << "adding user " << argv[2] << normal << endl;

		// SET RUNVAR EQUAL TO THIS, THEN RUN THE COMMAND
		rv.runVar = "sudo adduser " + string( argv[2] );
		system( (rv.runVar).c_str() );

		// IF ARGUMENTS ARE GREATER
		if ( argc > 3 ){

			// SET RUNVAR EQUAL TO THIS, THEN RUN THE COMMAND
			rv.runVar = "sudo adduser " + string( argv[3] );
			system( (rv.runVar).c_str() );

			// IF ARGUMENTS ARE GREATER
			if ( argc > 4 ){

				// SET RUNVAR EQUAL TO THIS, THEN RUN THE COMMAND
				rv.runVar = "sudo adduser " + string( argv[3] );
				system( (rv.runVar).c_str() );

			}
			// END IF ARGUMENTS ARE GREATER

		}
		// END IF ARGUMENTS ARE GREATER

	}
	// END ELSE OF IF ARGUMENTS ARE ADEQUIT

	// GENERATE A BLANK LINE
	cout << " " << endl;
}

// SHOW GROUPS FUNCTION
void showGroups( int argc, char* argv[] ){

	// GENERATE INPUT FILE STREAM FOR GROUP
	ifstream group("/etc/group");

	// IF THE GROUP FILE IS EXISTING
	if( group ){

		// SHOW DISPLAY GROUP PROMPT
		pcol("yellow", "\nDisplaying groups in the system: ");

		// RUN CAT GROUP
		system("cat /etc/group");

		// GENERATE BLANK LINE
		cout << " " << endl;

		// CLOSE THE GROUP FILE STREAM
		group.close();

	}else{

		// ERROR CALL GROUP NOT FOUND
		err_call("/etc/group not found.");

	}

	// CLOSE GROUP FILE STREAM
	group.close();

}

// GENERATE PROMPT VALUE
void prompt(){

	// GENERATE PROMPT MESSAGE
	pcol("blue", "\nKommandor v0.01 by Jackson Brown (jacksonconnerbrown@gmail.com)");

}

// REMOVE USER FUNCTION
void removeUser( int argc, char* argv[] ){

	// IF INPUT ARGUMENTS ARE LESS THAN 3
	if ( argc < 3){

		// GENERATE THIS ERROR MESSAGE
		err_call("missing parameters.");

	}
	else{

		// DISPLAY REMOVE USER PROMPT
		cout << yellow << "removing user " << argv[2] << normal << endl;

		// REMOVE USER RUN THIS
		rv.runVar = "sudo userdel -r " + string( argv[2] );

		// RUN THE ABOVE PUT INTO THE RUN VARIABLE
		system( (rv.runVar).c_str() );

		// IF ARGUMENTS ARE GREATER THAN 3
		if ( argc > 3 ){

			// SET RUNVAR TO THIS
			rv.runVar = "sudo userdel -r " + string( argv[3] );

			// RUN THE ABOVE PUT INTO RUN VARIABLE
			system( (rv.runVar).c_str() );

			// IF ARGUMENTS ARE GREATER THAN 4
			if ( argc > 4 ){

				// SET RUNVAR TO THIS
				rv.runVar = "sudo userdel -r " + string( argv[4] );

				// RUN THE ABOVE PUT INTO RUN VARIABLE
				system( (rv.runVar).c_str() );

			}
			// END IF ARGUMENTS ARE GREATER THAN 4

		}
		// END IF ARGUMENTS ARE GREATER THAN 3

	}

	// GENERATE BLANK LINE
	cout << " " << endl;

}

void encryptFile( int argc, char* argv[] ){
	if ( argc < 3){
		err_call("missing parameters.");
	}
	else{
		cout << yellow << "encrypting file " << argv[2] << normal << endl;
		rv.runVar = "sudo gpg -c " + string( argv[2] );
		system ( (rv.runVar).c_str() );
		cout << " " << endl;
	}
}

void serverUtilization( int argc, char* argv[]){
	pcol("yellow", "Displaying server utilization information: ");
	pcol("green", "Uptime: ");
	system("sudo uptime");
	cout << "\n --- \n" << endl;
	pcol("green", "Users connected: ");
	system("sudo who -a");
	cout << "\n --- \n" << endl;
	pcol("green", "Last 3 logins: ");
	system("sudo last -a | head -3");
	cout << "\n --- \n" << endl;
	pcol("green", "Most expensive process: ");
	system("sudo top -b | head -10 | tail -4");
	cout << "\n --- \n" << endl;
	pcol("green", "Open ports: ");
	system("sudo nmap -sT localhost | grep -E \"(tcp|udp)\"");
	cout << "\n --- \n" << endl;
	pcol("green", "Current connections: ");
	system("sudo ss -s");
	cout << "\n --- \n" << endl;
}

void editFirewall(int argc, char* argv[]){
	if ( argc < 3 ){
		err_call("missing parameters.");
	}
	else{
		string argtwo = argv[2];
		if ( argtwo == "save" )
			system("iptables save");
		else if ( argtwo == "status" )
			system("iptables status");
		else if ( argtwo == "flush" )
			system("iptables -F");
		else if ( argtwo == "build" ) {
			pcol("green", "Choose filter chain: ");
			cout << "1.) chain=\"INPUT\"" << endl;
			cout << "2.) chain=\"OUTPUT\"" << endl;
			cout << "3.) chain=\"FORWARD\"" << endl;
			string filteropt;
			cout << ">";
			cin >> filteropt;
			string chain;
			if ( filteropt == "1" ){
				chain = "INPUT";
			}
			else if ( filteropt == "2"){
				chain = "OUTPUT";
			}
			else if ( filteropt == "3" ){
				chain = "FORWARD";
			}
			else{
				err_call("Invalid parameter.");
			}
			pcol("green", "Get source IP address: ");
			cout << "1.) Firewall using a single source IP." << endl;
			cout << "2.) Firewall using a source subnet." << endl;
			cout << "3.) Firewall using all source networks." << endl;
			string filtertype;
			cout << ">";
			cin >> filtertype;
			string ipsource;
			if ( filtertype == "1" ){
				cout << "Entre the IP of the source: " << endl;
				cout << ">";
				cin >> ipsource;
			}
			else if ( filtertype == "2"  ){
				cout << "Enter the SUBNET of the source" << endl;
				cout << ">";
				cin >> ipsource;
			}
			else if ( filtertype == "3" ){
				ipsource = "0/0";
			}
			else{
				err_call("Invalid parameter.");
			}
			pcol("green", "Get destination IP address: ");
			cout << "1.) Firewall using a single destination IP." << endl;
			cout << "2.) Firewall using a destination SUBNET." << endl;
			cout << "3.) Firewall using all destination networks." << endl;
			string filterdest;
			cout << ">";
			cin >> filterdest;
			string ipdest;
			if ( filterdest == "1" ){
				cout << "Enter the IP of the destination: " << endl;
				cout << ">";
				cin >> ipdest;
			}
			else if ( filterdest == "2" ){
				cout << "Enter the SUBNET of the destination: " << endl;
				cout << ">";
				cin >> ipdest;
			}
			else if ( filterdest == "3" ){
				ipdest = "0/0";
			}
			else{
				err_call("Invalid parameter.");
			}
			pcol("green", "Get protocol: ");
			cout << "1.) Block all TCP traffic." << endl;
			cout << "2.) Block a specific TCP service." << endl;
			cout << "3.) Block a specific port." << endl;
			string filterprot;
			cout << ">";
			cin >> filterprot;
			string proto;
			if ( filterprot == "1" ){
				proto = "TCP";
			}
			else if ( filterprot == "2" ) {
				cout << "Enter the TCP service name: " << endl;
				cout << ">";
				cin >> proto;
			}
			else if ( filterprot == "3" ){
				cout << "Enter the port name: " << endl;
				cout << ">";
				cin >> proto;
			}
			else{
				err_call("Invalid parameter.");
			}
			pcol("green", "Get rule: ");
			cout << "1.) rule=\"ACCEPT\"" << endl;
        		cout << "2.) rule=\"REJECT\"" << endl;
  	     		cout << "3.) rule=\"DROP\"" << endl;
       			cout << "4.) rule=\"LOG\"" <<endl;
			string filterrule;
			cout << ">";
			cin >> filterrule;
			string rule;
			if ( filterrule == "1" ){
				rule = "ACCEPT";
			}
			else if ( filterrule == "2" ){
				rule = "REJECT";
			}
			else if ( filterrule == "3" ){
				rule = "DROP";
			}
			else if ( filterrule == "4" ){
				rule = "LOG";
			}
			else{
				err_call("Invalid parameter.");
			}
			cout << "The generated rule is: " << endl;
			cout << red << "iptables -A " << chain << " -s " << ipsource << " -d " << ipdest << " -p " << proto << " -j " << rule << normal << endl;
			pcol("yellow", "Save the rule to IP tables (y/n)?");
			string savetables;
			cout << ">";
			cin >> savetables;
			if ( savetables == "y"){
				string runipt = "iptables -A " + chain + " -s " + ipsource + " -d " + ipdest + " -p " + proto + " -j " + rule;
				system( (runipt).c_str() );
			}
			else{
				err_call("Option other than \"y\" specified.");
			}
		}
	}
}

void ipInfoConv( int argc, char* argv[] ){

	if ( argc < 3 ){
		err_call("mssing parameters.");
	}
	else{
		string string_ip = string( argv[2] );
		vector<int> octetsIP;

		getOctets(string_ip, octetsIP);
		cout << "Binary IP: " << toBinary(octetsIP) << endl;

		cout << " " << endl;
	}
}



void showMemory(){
	pcol("yellow", "Displaying memory usage: \n");
	pcol("green", "\nUsed memory: ");
	system("vmstat -s -SM | grep used | grep memory | sed -e 's/^[ \t]*//'");
	cout << "\n --- \n" << endl;
	pcol("green", "\nUsed swap: ");
	system("vmstat -s -SM | grep used | grep swap | sed -e 's/^[ \t]*//'");
	cout << "\n --- \n" << endl;
	pcol("green", "\nFree disk space: ");
	system("df -h | grep -v Filesystem");
	cout << "\n --- \n" << endl;
	pcol("green", "\nCPU usage: ");
	system("lscpu | grep CPU");
	cout << "\n --- \n" << endl;
	pcol("green", "Load average: ");
	double load[3];  
   	if (getloadavg(load, 3) != -1){  
   		printf("%f , %f , %f\n", load[0],load[1],load[2]);
		if ( load [0] > 0.50 ){
			cout << red << "CPU load average is above 0.50!" << normal << endl;
		}
	}
	cout << "\n --- \n" << endl;
}

