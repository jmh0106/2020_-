#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene()
{
	gravity = 0;
	isJump = false;
	doubleJump = false;

	backGroundList.push_back(new Sprite("Resources/Image/Background.png"));

	Sprite* tmpBackground = new Sprite("Resources/Image/Background.png");
	tmpBackground->setPos(SCREEN_WIDTH, 0);
	backGroundList.push_back(tmpBackground);

	bridgeList.push_back(new Sprite("Resources/Image/LoopMap.png"));

	Sprite* tmpBridge = new Sprite("Resources/Image/LoopMap.png");
	tmpBridge->setPos(SCREEN_WIDTH, 500);
	bridgeList.push_back(tmpBridge);

	player = new Animation(10);
	player->AddFrame("Resources/Image/player-stop.png");
	player->AddFrame("Resources/Image/player-run.png");
	player->setPos(50, 100);
}

GameScene::~GameScene()
{

}

void GameScene::Render()
{
	for (auto& background : backGroundList)
		background->Render();

	for (auto& bridge : bridgeList)
		bridge->Render();

	player->Render();
}

void GameScene::Update(float dTime)
{
	Scene::Update(dTime);
	gravity += 9.8f;

	player->setPos(player->getPosX(), player->getPosY() + gravity * dTime);

	if (isJump)
	{
		player->setPos(player->getPosX(), player->getPosY() - 500 * dTime);

		if (doubleJump)
		{
			player->setPos(player->getPosX(), player->getPosY() - 300 * dTime);
		}

		if (inputManager->GetKeyState(VK_SPACE) == KEY_DOWN)
		{
			doubleJump = true;
		}
	}

	if (player->getPosY() > 350)
	{
		player->setPos(player->getPosX(), 350);
		isJump = false;
		doubleJump = false;
	}

	if (inputManager->GetKeyState(VK_SPACE) == KEY_DOWN)
	{
		if (player->getPosY() == 350)
		{
			isJump = true;
			gravity = 0;
		}
	}

	player->Update(dTime);

	int bridgeDiff = 500 * dTime;
	for (auto iter = bridgeList.begin(); iter != bridgeList.end(); iter++)
	{
		(*iter)->setPos((*iter)->getPosX() - bridgeDiff, (*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH)
		{
			SAFE_DELETE((*iter));

			iter = bridgeList.erase(iter);

			if (iter == bridgeList.end())
				break;

			Sprite* tmpBridge = new Sprite("Resources/Image/LoopMap.png");
			tmpBridge->setPos(SCREEN_WIDTH, 500);
			bridgeList.push_back(tmpBridge);
		}
	}


	int backgroundDiff = 500 * dTime;
	for (auto iter = backGroundList.begin(); iter != backGroundList.end(); iter++)
	{
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH)
		{
			SAFE_DELETE((*iter));

			iter = backGroundList.erase(iter);

			if (iter == backGroundList.end())
				break;

			Sprite* tmpBackground = new Sprite("Resources/Image/Background.png");
			tmpBackground->setPos(SCREEN_WIDTH, 0);
			backGroundList.push_back(tmpBackground);
		}
	}
}
