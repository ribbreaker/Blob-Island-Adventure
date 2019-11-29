#include "pch.h"
#include "Scene.h"
#include "Adventure_Functionality.h"
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <random>
#include <map>

SceneName currentScene;
char dumbo[MAXSTRING];
std::string input;
bool dead;


Scene::Scene() {
	currentScene = HOUSE;
	SceneAction(currentScene);
}

Scene::~Scene() {
}

void Scene::EntryText() {
	printf("hello world!\n");
}
int Scene::CurrentScene() {
	return	currentScene;
}

void Scene::SceneAction(SceneName scene) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 3);
	std::string secondWord;
	std::map<std::string, int> inventory;
	switch (scene)
	{
		//Your house that you start in
		case(HOUSE):{
			//textToScreen("You wake up one summer evening, something is afoot. But you cannot tell what it is.\n");
			//textToScreen("A darkness is approaching...\n", 100);
			enum Area { BED, SWORD, WINDOW, DOOR};
			Area location = BED;
			int danger = 0;
			bool standing = false;
			bool open = true;
			do {
				//process the text input
				ProcessTextInput(dumbo);
				//test for context sensitive user input
				//Excellent, put this into it's own function, with multiple variations on the "looking" word
				//Only register the "looking" word if it's the first word in the string

				std::stringstream s{ dumbo };
				std::string word;
				s >> word;

				switch (location)
				{
				case BED: {
						//look command, combine with other words for more stuff
						if (word == "look") {
							s >> secondWord;
							//ignore unecessary words 
							while (secondWord == "at" || secondWord == "to" || secondWord == "the" || secondWord == "my") {
								s >> secondWord;
							}
							//if you're just looking
							if (secondWord == "") {
								if (!standing) {
									textToScreen("The house you live in. you're currently SITTING in your Bed, there's a window Westward, and a door Estward.");
									textToScreen(" Southwise you'll find your trusty BLADE and MASK on your desk...\n");
								}
								else {
									textToScreen("The house you live in. you're currently STANDING by your Bed, there's a window Westward, and a door Estward.");
									textToScreen(" Southwise you'll find your trusty BLADE and MASK on your desk...\n");
								}
							}
							//are you looking at the door
							else if (secondWord == "door") {
								textToScreen("The door to the outside.\n");
							}
							//are you looking at the window 
							else if (secondWord == "window") {
								textToScreen("The window to your house, it's Open, but you can't really see anything from here. Try moving closer.\n");
							}
							else {
								textToScreen("you can't look at " + secondWord + '\n');
							}
						}
						//kill command
						else if (word == "kill" || word == "attack" || word == "fight") {
							textToScreen("WHy would you do that, and who would you" + word + "?\n");
						}
						//stand command
						else if (word == "stand") {
							if (!standing) {
								textToScreen("You stood up from your Bed, now you can move around using your feetsicles!\n");
								standing = true;
							}
							else {
								textToScreen("You stand where you stand, standing your ground, you stand like a strand. You can't stand this\n");
							}
						}
						else if (word == "lore") {

						}
						//Go to places
						else if (word == "go" || word == "walk" || word == "run") {
							if (standing) {
								s >> secondWord;
								if (secondWord == "east") {
									textToScreen("I'm sorry, i couldn't quite catch that, did you mean est?\n.");
								}
								else if (secondWord == "est") {
									textToScreen("How far est would you like to go?\n");
								}
								else if (secondWord == "estward") {
									textToScreen("You went estward towards your entrance door. \n");
									location = DOOR;
								}
								else if (secondWord == "west" || secondWord == "westward") {
									textToScreen("You've gone westward to the window.\n");
									textToScreen("On the window sill you spot a ruby key, glimmering beautifully. You wonder how in the world you are able to sleep");
									textToScreen(" with this discoball of a housekey in your room.\n");
									location = WINDOW;
								}
								else if (secondWord == "south" || secondWord == "southwise") {
									textToScreen("You went southward to your desk.\n");
									location = SWORD;
								}
								else {
									textToScreen("You can't go there.\n");
								}
							}
							else {
								textToScreen("You need to stand up first, unless you plan to crawl throughout this whole adventure game.\n");
							}
						}
						//sitting (why would you do that?)
						else if (word == "sit") {
							textToScreen("You probably shouldn't do that.\n");
						}
						//if it doesn't make any sense
						else {
							switch (dis(gen)) {
							case(1):
								textToScreen("You can't do that.\n");
								break;
							case(2):
								textToScreen("Have you tried saying something that makes sense?\n");
								break;
							case(3):
								textToScreen("use keywords, dipshit.\n");
								break;
							}
						}
					break;
				}
				//Standing by the sword and mask
				case SWORD:
					break;
				//standing by the window
				case WINDOW:{
					if (word == "look") {
						s >> secondWord;
						while (secondWord == "through" || secondWord == "the") {
							s >> secondWord;
						}
						//if you're just looking
						if (secondWord == "") {
							//if the window is open
							if (open) {
								textToScreen(" the window is open, you should probably LOOK through it.\n");
							}
							else {
								textToScreen("You've closed the window.\n");
							}

							//if the key isn't taken
							if (inventory["ruby key"] != 1) {
								textToScreen("The ruby Key sits there on the sill, waiting to be TAKEn by someone.\n");
							}
						}
						//looking through the window
						else if (secondWord == "window") {
							if (danger <= 5) {
								if (open) {
									textToScreen("The evening sun shines brightly, a gigantic shadowy presence is approaching rapidly towards your home.\n");
								}
								else {
									textToScreen("The evening sun shines brightly, a gigantic shadowy presence is approaching rapidly towards your home.\n");
									textToScreen("You've closed the window.\n");
								}

							}
							//It's getting dangerous...
							if (danger > 5) {
								if (open) {
									textToScreen("It is nearly here. you feel your life is in danger\n");
								}
								else {
									//if you've closed the window 
									textToScreen("You've closed the window. But it wont hold for much longer.\n");
									textToScreen("You see only darkness on the other side of the window.\n");
									textToScreen("You need to get out of here\n");
								}
							}
							//it's almost inside
							if (danger >= 8) {
								if (open) {
									textToScreen("The darkness is seeping in. You need to go before it's too late!\n");
								}
								else {
									textToScreen("The glass is cracking, and the darkness is seeping in. If you don't leave now it'll be too late\n");
								}
							}	
						}
						else {
							textToScreen("You can't look at that\n");
						}
					}
					//add the ruby key to the inventory
					if (word == "take" || word == "grab" | word == "pick" || word == "get") {
						s >> secondWord;
						if (secondWord == "key" || "ruby" && inventory["ruby key"] != 1) {
							textToScreen("You grabbed the ruby key!\n");
							inventory["ruby key"] = 1;
						}
						else {
							textToScreen("You can't take that\n");
						}
					}
					if (word == "close" || word == "shut") {
						s >> secondWord;
						//ignore unecessary words 
						while (secondWord == "the") {
							s >> secondWord;
						}
						if (secondWord == "") {
							textToScreen("What do you want to close?\n");
						}
						else if (secondWord == "window") {
							textToScreen("You shut the window. You feel safer now.\n");
							textToScreen("But you should hurry.\n");
							danger -= 7;
						}
					}
					break;
				}
				//standing by the door
				case DOOR:
					break;
				default:
					break;
				}
				if (danger < 5) {
					textToScreen("\nA darkness is approaching...\n\n", 100);
				}
				if (danger > 5 && danger < 10) {
					textToScreen("\nThe darkness is moving closer at an alarming rate..\n\n");
				}
				if (danger == 10) {
					textToScreen("\nIt's here!\n\n");
				}
				if (danger > 10) {
					dead = true;
					textToScreen("\n\nBefore you even knew what had happened, the darkness had made it's way to you through the window. There was nothing you could do.\n");
					textToScreen("Everything was pitch black.\n", 100);
					textToScreen("And you were consumed before your quest had even begun...\n", 100);
				}
				word = "";
				secondWord = "";
				//It get more dangerous the longer you stay, you need to MOVE
				danger++;
			} while (!dead);
		}	
	}
	if (dead) {
		GameOver();
	}

}
