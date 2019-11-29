#include "pch.h"
#include "Adventure_Functionality.h"
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
int pts = 0;
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
//prints out text in a typewriter-like fashion
void textToScreen(std::string text, int speed) {
	for (const auto i : text) {
		std::cout << i << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	}
}

void GameOver() {
	textToScreen("\nSadly, this is where your quest ends. Had you only been a better player then perhaps this wouldn't have happened!\n");
	textToScreen("You finished with " + std::to_string(pts) + " points.\n\n");
}