#include "Player.h"
#include "../Framework/ResourceMgr.h"
#include "../Framework/InputMgr.h"
#include "Floor.h"
#include "../Scene/SceneMgr.h"

void Player::Init()
{
	//Texture* texture = RESOURCE_MGR->GetTexture("graphics/charStand1.png");
	//Vector2f origin(47.5f, 46);
	//Texture* texture2 = RESOURCE_MGR->GetTexture("graphics/walk1.png");
	//Vector2f origin2(20, 37.5f);
	//Texture* texture3 = RESOURCE_MGR->GetTexture("graphics/attack.png");
	//Vector2f origin3(128, 100);


	SetPos({ 200, 800 });
	animator.SetTarget(&sprite);

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("StandRight"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("StandLeft"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("RunSideLeft"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("RunSideRight"));

	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("JumpLeft"));
	animator.AddClip(*RESOURCE_MGR->GetAnimationClip("JumpRight"));

	{
		AnimationEvent ev;
		ev.clipId = "AttackBottomLeft";
		ev.frame = 6;
		ev.onEvent = bind(&Player::OnCompleteJump, this);
		animator.AddEvent(ev);
	}

	SetState(States::Stand);
	Object::Init();
}

void Player::SetState(States newState)
{
	if (currState == newState)
		return;

	currState = newState;
	switch (currState)
	{
	case Player::States::Stand:
		animator.Play((lastDirection.x > 0.f) ? "StandRight" : "StandLeft");
		break;
	case Player::States::Run:
		if (direction.x)
		{
			animator.Play((direction.x > 0.f) ? "RunSideRight" : "RunSideLeft");
		}
		break;
	case Player::States::Attack:
		//animator.Play("Attack");
	case Player::States::Jump:
		//animator.Play((lastDirection.x > 0.f) ? "JumpRight" : "JumpLeft");
		break;
	}
	height = sprite.getGlobalBounds().height;
}

void Player::SetBackgound(SpriteObj* bk)
{
	background = bk;
}

void Player::UpdateInput()
{
	if (InputMgr::GetKeyDown(Keyboard::Space))
	{
		SetState(States::Jump);
		velocity = Vector2f(0.f, -1000.f);
		gravity = Vector2f(0.f, 3000.f);
	}
	else if (InputMgr::GetKey(Keyboard::Space))
	{
		SetState(States::Jump);
	}
}

void Player::Update(float dt)
{
	UpdateInput();
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		exit(-1);
	direction.x = 0.f;
	direction.x += Keyboard::isKeyPressed(Keyboard::Right) ? 1 : 0;
	direction.x += Keyboard::isKeyPressed(Keyboard::Left) ? -1 : 0;

	if (Utils::Magnitude(velocity) > speed)
	{
		//velocity = Utils::Normalize(velocity) * speed;
	}


	Translate(direction*dt*speed);

	switch (currState)
	{
	case Player::States::Stand:
		UpdateStand(dt);
		break;
	case Player::States::Run:
		UpdateRun(dt);
		break;
	case Player::States::Attack:
		UpdateAttack(dt);
		break;
	case Player::States::Jump:
 		UpdateJump(dt);
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

void Player::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Player::OnCompleteJump()
{
	SetState(States::Stand);
}

void Player::SetFloor(vector<Floor*> floor)
{
	this->floor = floor;
}

void Player::UpdateStand(float dt)
{
	if (!EqualFloat(direction.x, 0.f))
	{
		SetState(States::Run);
		return;
	}
}

void Player::UpdateRun(float dt)
{
	if (EqualFloat(direction.x, 0.f))
	{
		SetState(States::Stand);
		return;
	}
	if (!EqualFloat(direction.x, lastDirection.x))
	{
		animator.Play((direction.x > 0.f) ? "RunSideRight" : "RunSideLeft");
	}
}

void Player::UpdateAttack(float dt)
{

}

void Player::UpdateJump(float dt)
{
	velocity += gravity * dt ;
	Vector2f delta = velocity * dt;
	Translate(delta);

	if (velocity.y > 0 && IsBottomHit())
	{
		if (abs(GetGlobalBounds().top + GetGlobalBounds().height - nowfloor->GetHitBounds().top) < 10)
		{
			SetState(States::Run);
			velocity = Vector2f(0.f, -1000.f);
			gravity = Vector2f(0.f, 3000.f);
		}
	}
}

bool Player::EqualFloat(float a, float b)
{
	return fabs(a - b) < numeric_limits<float>::epsilon();
}

bool Player::IsBottomHit()
{
	for (auto& botm : floor)
	{  
		for(int i = 0; i < 9; ++i)
		{
			if (GetGlobalBounds().intersects(floor[i]->GetHitBounds()))
			{
				cout << floor[i]->GetHitBounds().top << endl;

				nowfloor = floor[i];
				return true;
			}
		}
	}
	return false;
}
