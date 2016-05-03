#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdbool.h>
#include <unistd.h>

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

// COLOR PRINT FUNCTIONS
void pcol( string x, string y ){
	if      ( x == "green"  )
		cout << green  << y << normal << endl;
	else if ( x == "red"    )
		cout << red    << y << normal << endl;
	else if ( x == "blue"   )
		cout << blue   << y << normal << endl;
	else if ( x == "yellow" )
		cout << yellow << y << normal << endl;
}

void err_call( string x ){
	cout << red << x << normal << endl;
}

void help(){
	cout << blue << "\nUsage: " << normal << endl;
	cout << "kommandor [options] [parameters] " << endl;

	cout << blue << "\nOptions: " << normal << endl;
	cout << "help        : Displays this help prompt." << endl; 
	cout << "users       : Displays the system users." << endl; 
	cout << "addusers    : Adds the listed users in an interactive prompt." << endl;
	cout << "groups      : Displays the system groups." << endl; 
	cout << "removeusers : Completely removes a specified user." << endl; 
	cout << "memuse      : Show the system memory usage." << endl;
	cout << "encrypt     : Encrypts a file using gpg." << endl;
	cout << "serverstat  : Display the server utilization." << endl;
	cout << "setiptable  : Interactively generate iptables firewalls. \n" << endl;
}

void showUsers(){
	ifstream passwd("/etc/passwd");
	if ( passwd ){
		pcol("yellow", "\nUsers with bash shell: ");
		system("cat /etc/passwd | grep bash");
		cout << "\n --- \n" << endl;

		pcol("yellow", "Users with zsh shell: ");
		system("cat /etc/passwd | grep zsh");
		cout << "\n --- \n" << endl;

		pcol("yellow", "Users with ksh shell: ");
		system("cat /etc/passwd | grep ksh");
		cout << "\n --- \n" << endl;
		passwd.close();
	}else{
		err_call("/etc/passwd file not found.");
	}
	passwd.close();
}

void addUsers( int argc, char* argv[] ){
	if ( argc < 3){
		err_call("missing parameters.");
	}
	else{
		cout << yellow << "adding user " << argv[2] << normal << endl;
		rv.runVar = "sudo adduser " + string( argv[2] );
		system( (rv.runVar).c_str() );
		if ( argc > 3 ){
			rv.runVar = "sudo adduser " + string( argv[3] );
			system( (rv.runVar).c_str() );
			if ( argc > 4 ){
				rv.runVar = "sudo adduser " + string( argv[3] );
				system( (rv.runVar).c_str() );
			}
		}
	}
	cout << " " << endl;
}

void showGroups( int argc, char* argv[] ){
	ifstream group("/etc/group");
	if( group ){
		pcol("yellow", "\nDisplaying groups in the system: ");
		system("cat /etc/group");
		cout << " " << endl;
		group.close();
	}else{
		err_call("/etc/group not found.");
	}
	group.close();
}

void prompt(){
	pcol("blue", "\nKommandor v0.01 by Jackson Brown (jacksonconnerbrown@gmail.com)");
}

void removeUser( int argc, char* argv[] ){
	if ( argc < 3){
		err_call("missing parameters.");
	}
	else{
		cout << yellow << "removing user " << argv[2] << normal << endl;
		rv.runVar = "sudo userdel -r " + string( argv[2] );
		system( (rv.runVar).c_str() );
		if ( argc > 3 ){
			rv.runVar = "sudo userdel -r " + string( argv[3] );
			system( (rv.runVar).c_str() );
			if ( argc > 4 ){
				rv.runVar = "sudo userdel -r " + string( argv[4] );
				system( (rv.runVar).c_str() );
			}
		}
	}
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

int main(int argc, char* argv[]){
	if ( getuid() != 0 ){
		err_call("\n**************** PLEASE RUN AS ROOT ****************\n");
	}
	else{
		prompt();
		if ( argc < 2 ){
			help();
			return 1;
		}
		string argtest = argv[1];
		if      ( argtest == "help"               )
			help();
		else if ( argtest == "users"              )
			showUsers();
		else if ( argtest == "removeusers"        )
			removeUser( argc, argv );
		else if ( argtest == "groups"             )
			showGroups( argc, argv );
		else if ( argtest == "memuse"             )
			showMemory();
		else if ( argtest == "encrypt"            )
			encryptFile( argc, argv );
		else if ( argtest == "serverstat"         )
			serverUtilization( argc, argv );
		else if ( argtest == "setiptable"         )
			editFirewall( argc, argv );
		else if ( argtest == "addusers"            )
			addUsers( argc, argv );
		else
			err_call("\nArgument not found.\n");
	}
	return 0;
}
