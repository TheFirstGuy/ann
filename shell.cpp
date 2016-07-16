/*
6/26/2016
Programmer: Urs Evora
*/

#include "shell.h"
#include "utils.h"		// toLower
#include "ANN.h"
#include "Instance.h"
#include <vector>
#include <string>
#include <iostream>



int parseArgs( const std::string& str,  std::vector<Arg>& args ){
	char space = ' ';
	char quote = '"';
	char dash = '-';
	char equals = '=';
	std::size_t bPos = 0;
	std::size_t fPos = 0;
	while( fPos < str.length() ){
		Arg temp;
		if( str[fPos] == quote ){
			bPos = fPos;
			// Find end of string argument
			++fPos;
			//std::cerr << "HERE";
			while( fPos < str.length() && str[fPos] != quote ){ ++fPos; }
			if( fPos >= str.length() ){ 
				std::cout << "Missing double quote." << std::endl;
				return -1;
			}
			else{
				temp.type = VAL;
				temp.value = str.substr( bPos + 1, (fPos-bPos) - 1 );
				args.push_back(temp);
				// seek next word
				++fPos;
				while( fPos + 1 < str.length() && str[fPos] == space ){ bPos = ++fPos; }
			}
		}
		else if( str[fPos] == space && bPos != fPos){
			std::string subStr = str.substr( bPos, fPos-bPos );
			// Command argument
			if( bPos == 0 ){
				temp.type = CMD;
				temp.value = subStr;
				args.push_back(temp);
			}
			// Flag argument
			else if( subStr[0] == dash ){
				temp.type = FLAG;
				temp.value = subStr;
				args.push_back(temp);
			}
			// Descriptor argument
			else if( subStr[subStr.length() - 1] == equals ){
				temp.type = DSC;
				temp.value = subStr;
				args.push_back(temp);
			}
			else{
				std::cout << "Could not identify argument: " << subStr << std::endl;
				return -1;
			}
			bPos = fPos + 1;
		}
		//std::cerr << (int)str[fPos] << std::endl;
		//std::cerr << fPos << std::endl;
		++fPos;
	}
	// Probably make this a function...
	if( fPos == str.length() && bPos != fPos){
			Arg temp;
			std::string subStr = str.substr( bPos, fPos-bPos );
			// Command argument
			if( bPos == 0 ){
				temp.type = CMD;
				temp.value = subStr;
				args.push_back(temp);
			}
			// Flag argument
			else if( subStr[0] == dash ){
				temp.type = FLAG;
				temp.value = subStr;
				args.push_back(temp);
			}
			// Descriptor argument
			else if( subStr[subStr.length() - 1] == equals ){
				temp.type = DSC;
				temp.value = subStr;
				args.push_back(temp);
			}
			else{
				temp.type = VAL;
				temp.value = subStr;
				args.push_back(temp);
			}
	}
	return 0;
}


int executeCmd( const std::vector<Arg>& args, ShellMem& memory ){
	if( args.size() <= 0 ){
	 	std::cout << "No arguments provided." << std::endl;
	 	return -1; 
	}
	if( args[0].type != CMD ){
		std::cout << "No command found." << std::endl;
		return -1;
	}
	// Check if all commands have function pointers
	if( (sizeof(COMMAND_FUNCS)/sizeof(COMMAND_FUNCS[0]) )!= COMMANDS.size() ){
		std::cout << "Not all commands initalized." << std::endl;
		return -1;
	}
	// Match first argument to available commands
	std::string cmd = toLower(args[0].value);
	for( size_t i = 0; i < COMMANDS.size(); ++i ){
		if( cmd == COMMANDS[i] ){
			return COMMAND_FUNCS[i](args, memory);
		}
	}
	std::cout << "No command: " << args[0].value << " found." << std::endl;

}

int annCmd( const std::vector<Arg>& args, ShellMem& memory){
	if( args.size() < 2 || args[1].type != FLAG ){
		std::cout << "No flag provided." << std::endl;
		return -1;
	}
	if( args[1].value == "-a" ){ annActivate( args, memory ); }
	else if( args[1].value == "-c"){ annCreate( args, memory.anns ); }
	else if( args[1].value == "-t"){ annTrain( args, memory ); }
	else if( args[1].value == "-d"){ annDisplay( args, memory.anns ); }
	else if( args[1].value == "-rm"){ annRemove( args, memory.anns ); }
	return 1;
}

// ANN helper functions
int annActivate( const std::vector<Arg>& args, ShellMem& memory ){}
int annCreate( const std::vector<Arg>& args, std::vector<ANN>& anns ){}
int annTrain( const std::vector<Arg>& args, ShellMem& memory ){}
int annDisplay( const std::vector<Arg>& args, std::vector<ANN>& anns ){}
int annRemove( const std::vector<Arg>& args, std::vector<ANN>& anns ){}

int setCmd( const std::vector<Arg>& args, ShellMem& memory ){}

int helpCmd( const std::vector<Arg>& args, ShellMem& memory ){}

int saveCmd( const std::vector<Arg>& args, ShellMem& memory ){}

