#include "pch.h"
#include "Scene.h"
#include "Adventure_Functionality.h"
#include <stdio.h>
#include <iostream>
SceneName currentScene;
char dumbo[MAXSTRING];
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
	switch (scene)
	{
	//Your house that you start in
	case(HOUSE):
		ProcessTextInput(dumbo);

		//test for context sensitive user input
		//Excellent, put this into it's own function, with multiple variations on the "looking" word
		char* temp;
		temp = strstr(dumbo, "look");
		if (temp) {
			printf("What are you looking at?");
		}

		break;
	}
}

void Scene::GoToScene() {

}