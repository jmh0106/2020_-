#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"
#include <list>

class GameScene : public Scene
{
private:
	float gravity;
	bool isJump;
	bool doubleJump;

	std::list<Sprite*> backGroundList;
	std::list<Sprite*> bridgeList;
	Animation* player;

public:
	GameScene();
	~GameScene();

	void Render();
	void Update(float dTime);
};

