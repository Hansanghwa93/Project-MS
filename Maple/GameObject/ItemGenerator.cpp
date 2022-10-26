#include "ItemGenerator.h"
#include "../Framework/Utils.h"
#include "../Scenes/SceneMgr.h"
#include "../Scenes/SceneDev1.h"
#include "Pickup.h"
#include "../GameObject/Player.h"

ItemGenerator::ItemGenerator() 
	: createIntervalMin(2.f), createIntervalMax(3.f),createInterval(0.f), createTimer(0.f), radius(300.f) ,createMax(3)
{
}

ItemGenerator::~ItemGenerator()
{
}

void ItemGenerator::Reset()
{
	itemList.clear();
	createTimer = 0.f;
	createInterval = Utils::RandomRange(createIntervalMin, createIntervalMax);
}

void ItemGenerator::Update(float dt)
{
	createTimer += dt;
	if (createTimer > createInterval)
	{
		int count = Utils::RandomRange(1, createMax + 1);
		for (int i = 0; i < count; ++i)
		{
			Generate();
		}		
		createTimer = 0.f;
		createInterval = Utils::RandomRange(createIntervalMin, createIntervalMax);
	}
}

void ItemGenerator::Generate()
{
	Scene* scene = SCENE_MGR->GetCurrScene();


	Pickup::Types itemtype = (Pickup::Types)Utils::RandomRange(0, (int)Pickup::Types::Count);
	
	Pickup* item = new Pickup();
	item->SetType(itemtype);
	item->SetValue(30);
	item->Setplayer((Player*)scene->FindGameObj("Player"));
	item->Init();

	Vector2f center = ((Player*)scene->FindGameObj("Player"))->GetPos();
	bool success = false;
	int count = 0;
	while (!success && count < 100)
	{
		success = true;
		Vector2f pos = center + Utils::RandAreaPoint() * radius;
		item->SetPos(pos);
		for (auto i : itemList)
		{
			if (i->GetActive() && item->GetGlobalBounds().intersects(i->GetGlobalBounds()))
			{
				success = false;
				++count;
			}
		}
	}
	if (success)
	{
		itemList.push_back(item);
		scene->AddGameObj(item);
	}
	else
	{
		delete item;
	}
}
