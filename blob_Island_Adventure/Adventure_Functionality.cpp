#include "pch.h"
#include "Adventure_Functionality.h"
#include <string>
#include <iostream>

//Basic input for the user to interact with the world
void  ProcessTextInput(char p[MAXSTRING]) {
	do {
		std::cin.getline(p, MAXSTRING);
	} while (strlen(p) == 0);
	//Put it to lowercase so there's no bullshit
	for (int i = 0; i <= sizeof(p); i++) {
		p[i] = tolower(p[i]);
	}
}