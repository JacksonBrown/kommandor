#ifndef KOMMANDOR_CMD_H
#define KOMMANDOR_CMD_H

using namespace std;

void help();
void pcol( string x, string y );
string toBinary( vector<int> octets );
int getOctets( string ip, vector <int> &octets );
void err_call( string x );
void showUsers( int argc, char* argv[] );
void addUsers( int argc, char* argv[] );
void showGroups( int argc, char* argv[] );
void prompt();
void removeUser( int argc, char* argv[] );
void encryptFile( int argc, char* argv[] );
void serverUtilization( int argc, char* argv[]);
void editFirewall(int argc, char* argv[]);
void ipInfoConv( int argc, char* argv[] );
void showMemory();
void editConfigFile( int argc, char* argv[] );

#endif
