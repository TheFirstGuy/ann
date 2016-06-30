/*
6/26/2016
Programmer: Urs Evora
*/

#include "shell.h"
#include "utils.h"		// toLower
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
				temp.value = str.substr( bPos + 1, (fPos-bPos) );
				args.push_back(temp);
				bPos = fPos + 1;
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
				std::cout << "Could not identify argument: " << subStr << std::endl;
				return -1;
			}
	}
	return 0;
}
