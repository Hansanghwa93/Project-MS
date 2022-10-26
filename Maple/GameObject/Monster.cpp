#include "Monster.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/InputMgr.h"
#include "Floor.h"
#include "../Scene/SceneMgr.h"


void Monster::Init()
{
	SetPos({ 200, 800 });
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("monStandRight"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("monStandLeft"));

	SetState(States::Stand);
	Object::Init();
}

void Monster::SetState(States newState)
{
	if (currState == newState)
		return;

	currState = newState;
	switch (currState)
	{
	case Monster::States::Stand:
		animator.Play((lastDirection.x > 0.f) ? "monStandRight" : "monStandLeft");
		break;
	case Monster::States::Run:
		//if (direction.x)
		//{
		//	animator.Play((direction.x > 0.f) ? "RunSideRight" : "RunSideLeft");
		//}
		break;
	case Monster::States::Attack:
		//animator.Play((lastDirection.x > 0.f) ? "AttackSideRight" : "AttackSideLeft");
		break;
	}
}

void Monster::SetBackgound(SpriteObj* bk)
{
	background = bk;
}

void Monster::Update(float dt)
{
	Translate(direction * dt * speed);

	switch (currState)
	{
	case Monster::States::Stand:
		UpdateStand(dt);
		break;
	case Monster::States::Run:
		UpdateRun(dt);
		break;
	case Monster::States::Attack:
		UpdateAttack(dt);
		break;
	}
	animator.Update(dt);

	if (!EqualFloat(direction.x, 0.f))
	{
		lastDirection = direction;
	}
	FloatRect wallBound = background->GetGlobalBounds();

	Vector2f pos;
	float border = 10.f;
	pos.x = Utils::Clamp(position.x, wallBound.left + border, wallBound.left + wallBound.width - border);
	pos.y = Utils::Clamp(position.y, wallBound.top + border, wallBound.top + wallBound.height - border);
	SetPos(pos);
}

void Monster::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Monster::SetFloor(vector<Floor*> floor)
{
	this->floor = floor;
}

void Monster::UpdateStand(float dt)
{
	if (!EqualFloat(direction.x, 0.f))
	{
		SetState(States::Run);
		return;
	}
}

void Monster::UpdateRun(float dt)
{
	if (EqualFloat(direction.x, 0.f))
	{
		SetState(States::Stand);
		return;
	}
	if (!EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "monRunSideRight" : "monRunSideLeft");
	}
}

void Monster::UpdateAttack(float dt)
{
}

bool Monster::EqualFloat(float a, float b)
{
	return fabs(a - b) < numeric_limits<float>::epsilon();
}
