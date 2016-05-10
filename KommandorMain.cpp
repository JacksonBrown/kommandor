#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stdbool.h>
#include <unistd.h>
#include <vector>
#include <sstream>

// FILE INCLUDE
#include "kommandor_cmd.h"

using namespace std;

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
		else if ( argtest == "addusers"           )
			addUsers( argc, argv );
		else if ( argtest == "iptobinary"         )
			ipInfoConv( argc, argv );
		else
			err_call("\nArgument not found.\n");
	}
	return 0;
}
