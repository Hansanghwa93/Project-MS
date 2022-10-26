#include "PlayScene.h"
#include "SceneMgr.h"
#include "../Framework/Framework.h"
#include "../Framework/InputMgr.h"
#include "../Framework/ResourceMgr.h"
#include "../GameObject/TextObj.h"
#include "../Framework/SoundMgr.h"
#include "../GameObject/Player.h"

PlayScene::PlayScene() : Scene(Scenes::Play)
{
}
PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	Release();

	background = new SpriteObj();
	background->SetTexture(*RESOURCE_MGR->GetTexture("graphics/Map/Map1.png"));
	objList.push_back(background);

	FloatRect boxs[9] = { {0,840,2770,50},{188,635,235,50 },{510,547,300,50},{915,459,300,50},{1320,370,200,50},{1640,465,300,50},{2040,550,300,50},{2450,640,200,50},{1100,641,650,50} };

	for(int i = 0; i<9; ++i)
	{
		Floor* floor_obj = new Floor();
		floor.push_back(floor_obj);
		floor_obj->SetHitBox(boxs[i]);
		objList.push_back(floor_obj);
	}
	
	player = new Player();
	player->SetFloor(floor);
	player->Init();
	player->SetBackgound(background);
	objList.push_back(player);

	for (auto obj : objList)
	{
		obj->Init();
	}
	
	
}

void PlayScene::Release()
{
	Scene::Release();
}

void PlayScene::Enter() 
{
	for (auto obj : objList)
	{
		obj->Reset();
	}

	FRAMEWORK->GetWindow().setMouseCursorVisible(true);
	FRAMEWORK->GetWindow().setMouseCursorGrabbed(false);
	Vector2i size = FRAMEWORK->GetWindowSize();
	Vector2f centerPos(size.x * 0.5f, size.y * 0.5f);

	worldView.setSize(size.x, size.y);
	worldView.setCenter(1920/2, 1080/2);

}

void PlayScene::Exit()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(true);
}

void PlayScene::Update(float dt)
{
	Scene::Update(dt);

	FloatRect wallBound = background->GetGlobalBounds();

	Vector2f pos = player->GetPos();
	float border = 10.f;
	pos.x = Utils::Clamp(pos.x, 960, 2770 - 960);
	pos.y = Utils::Clamp(pos.y, 515, 1030 - 515);
	worldView.setCenter(pos);
}

void PlayScene::Draw(RenderWindow& window)
{
	Scene::Draw(window);
}