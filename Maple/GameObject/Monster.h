#pragma once
#include "../Animator/Animator.h"
#include "../Framework/Utils.h"
#include "Object.h"
#include "SpriteObj.h"

class Scene;
class Floor;
class Monster : public SpriteObj
{
public:
	enum class States
	{
		None = -1,
		Attack,
		Run,
		Stand,
	};
protected:
	Animator animator;

	States currState;

	float speed;
	Vector2f direction;
	Vector2f lastDirection;
	Vector2f velocity;

	SpriteObj* background;
	vector<Floor*> floor;
public:
	Monster() : currState(States::None), speed(200.f), direction(1.f, 0.f), lastDirection(1.f, 0.f), velocity(0.f, -1000.f) {}
	void Init();

	void SetState(States newState);
	void SetBackgound(SpriteObj* bk);

	void Update(float dt);
	void Draw(RenderWindow& window);

	void SetFloor(vector<Floor*> floor);

	void UpdateStand(float dt);
	void UpdateRun(float dt);
	void UpdateAttack(float dt);

	bool EqualFloat(float a, float b);
};

