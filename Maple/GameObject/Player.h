#pragma once
#include "../Animator/Animator.h"
#include "../Framework/Utils.h"
#include "Object.h"
#include "SpriteObj.h"

class Scene;
class Floor;
class Player : public SpriteObj
{
public:
	enum class States
	{
		None = -1,
		Down,
		Attack,
		Run,
		Stand,
		Jump,
		DoubleJump,
		Skill,
	};
protected:
	Animator animator;

	States currState;

	float speed;
	Vector2f direction;
	Vector2f lastDirection;
	Vector2f velocity;
	Vector2f* viewPos;
	Vector2f gravity;
	SpriteObj* background;
	vector<Floor*> floor;
	Floor* nowfloor;
	float height;

	int keypresscnt;
public:
	Player() : currState(States::None), speed(350.f), direction(1.f, 0.f), lastDirection(1.f, 0.f), velocity(0.f, -1000.f), gravity(0.f, 3000.f), keypresscnt(0) {}
	void Init();

	void SetState(States newState);
	void SetBackgound(SpriteObj* bk);

	void UpdateInput();
	void Update(float dt);
	void Draw(RenderWindow& window);

	void OnCompleteAttack();
	void SetFloor(vector<Floor*> floor);

	void UpdateStand(float dt);
	void UpdateRun(float dt);
	void UpdateAttack(float dt);
	void UpdateJump(float dt);
	void UpdateDown(float dt);

	bool EqualFloat(float a, float b);

	bool IsBottomHit();
};

