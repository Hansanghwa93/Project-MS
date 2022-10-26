#pragma once
#include "../Animator/Animator.h"
#include "../Framework/Utils.h"

class Monster
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
	Sprite sprite;
	Animator animator;

	States currState;

	float speed;
	Vector2f direction;
	Vector2f lastDirection;
	Vector2f velocity;
public:
	Monster() : currState(States::None), speed(200.f), direction(1.f, 0.f), lastDirection(1.f, 0.f) {}
	void Init();

	void SetState(States newState);

	void UpdateInput(Event ev);
	void Update(float dt);
	void Draw(RenderWindow& window);

	void OnCompleteJump();

	void UpdateStand(float dt);
	void UpdateRun(float dt);
	void UpdateAttack(float dt);

	bool EqualFloat(float a, float b);
};

