#pragma once
#include "Scene.h"
#include <list>
#include "../Framework/ObjectPool.h"
#include "../GameObject/SpriteObj.h"
#include "../GameObject/Floor.h"

class Player;
class PlayScene : public Scene
{
protected:
	SpriteObj* background;
	Player* player;
	vector<Floor*> floor;
public:
	PlayScene();
	virtual ~PlayScene();

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;
};

