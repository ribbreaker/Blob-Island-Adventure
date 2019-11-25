#ifndef ADV_FUNC_H
#define ADV_FUNC_H
//Process text input
//Go to another screen/scene
//Display help
//Display inventory
//Display status
//look at stuff
//kick stuff
//stab/slice/cut/attack stuff
//talk to stuff
//obtain item
//Use item
//"Lore" Object (get detailed, unnecessary information about something)
enum SceneName {
	HOUSE
};
const int MAXSTRING = 50;
void ProcessTextInput(char p[MAXSTRING]);
void GoToScene(enum SceneName);
#endif



