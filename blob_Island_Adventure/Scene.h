#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:
	Scene();
	~Scene();
	void EntryText();
private:
	//Shows the lore of something the player specifies
	void ShowLore();
	//I will probably not use these, they seem unecessary and stupid
	void WriteLoreToFile();
	void GetLoreFromFile();
	//the current scene the player resides in
	int CurrentScene();
	//What happens in each scene
	void SceneAction(enum SceneName);
	//Jumping to the next scene
	void GoToScene();


};
#endif