#include "stdafx.h"
#include "GameScene.h"

GameScene::GameScene()
{
	gravity = 0;
	isJump = false;
	doubleJump = false;
	score - 0;

	//================================================================================//

	backGroundList.push_back(new Sprite("Resources/Image/Background.png"));

	Sprite* tmpBackground = new Sprite("Resources/Image/Background.png");
	tmpBackground->setPos(SCREEN_WIDTH, 0);
	backGroundList.push_back(tmpBackground);

	//================================================================================//

	bridgeList.push_back(new Sprite("Resources/Image/LoopMap.png"));

	bridgeList.front()->setPos(0, 500);

	Sprite* tmpBridge = new Sprite("Resources/Image/LoopMap.png");
	tmpBridge->setPos(SCREEN_WIDTH, 500);
	bridgeList.push_back(tmpBridge);

	//================================================================================//

	Sprite* tempCoin = new Sprite("Resources/Image/coin-yellow.png");
	tempCoin->setPos(SCREEN_WIDTH + 70, 400);
	coinList.push_back(tempCoin);

	//================================================================================//

	Sprite* tempObstacle = new Sprite("Resources/Image/Drop.png");
	tempObstacle->setPos(SCREEN_WIDTH, 400);
	obstacleList.push_back(tempObstacle);

	//================================================================================//

	for (int i = 0; i < 4; i++)
		numArray[i].setPos(0 + 60 * i, 10);

	//================================================================================//
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

	for (auto& obstacle : obstacleList)
		obstacle->Render();

	for (auto& coin : coinList)
		coin->Render();
	
	for (int i = 0; i < 4; i++)
		numArray[i].Render();

	player->Render();
}

void GameScene::Update(float dTime)
{
	Scene::Update(dTime);
	gravity += 9.8f;

	int randNum = rand() % 10 + 1;
	if (randNum == 1)
	{
		Sprite* tempCoin = new Sprite("Resources/Image/coin-yellow.png");
		tempCoin->setPos(SCREEN_WIDTH + 70, 500);
		coinList.push_back(tempCoin);
	}

	numArray[0].setNum(score / 1000);
	numArray[1].setNum(score % 1000 / 100);
	numArray[2].setNum(score % 100 / 10);
	numArray[3].setNum(score % 10);

	player->setPos(player->getPosX(), player->getPosY() + gravity * dTime);

	if (isJump)
	{
		player->setPos(player->getPosX(), player->getPosY() - 300 * dTime);

		if (doubleJump)
		{
			player->setPos(player->getPosX(), player->getPosY() - 200 * dTime);
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

	int obstacleDiff = 500 * dTime;
	for (auto iter = obstacleList.begin(); iter != obstacleList.end(); iter++)
	{
		(*iter)->setPos((*iter)->getPosX() - obstacleDiff, (*iter)->getPosY());


		if (player->IsCollisionRect((*iter)))
		{
			sceneManager->ChangeScene(new MainScene);
			return;
		}

		if ((*iter)->getPosX() < -SCREEN_WIDTH)
		{
			SAFE_DELETE((*iter));

			iter = obstacleList.erase(iter);


			if (iter == obstacleList.end())
				break;

			Sprite* tempObstacle = new Sprite("Resources/Image/Drop.png");
			tempObstacle->setPos(SCREEN_WIDTH, 500);
			obstacleList.push_back(tempObstacle);
		}
	}

	int coinDiff = 500 * dTime;
	for (auto iter = coinList.begin(); iter != coinList.end(); iter++)
	{
		(*iter)->setPos((*iter)->getPosX() - coinDiff, (*iter)->getPosY());

		if ((*iter)->getPosX() < -SCREEN_WIDTH)
		{
			SAFE_DELETE((*iter));

			iter = coinList.erase(iter);
		}
	}

	for (auto iter = coinList.begin(); iter != coinList.end(); iter++)
	{
		if (player->IsCollisionRect((*iter)))
		{
			score += 1;
			SAFE_DELETE((*iter));
			iter = coinList.erase(iter);

			if (iter == coinList.end())
				break;
		}
	}
}
