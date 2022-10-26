#include "Floor.h"

Floor::Floor()
{
}

Floor::~Floor()
{
}

void Floor::Init()
{
}

void Floor::SetPos(const Vector2f& pos)
{
	position = pos;
	hitbox.setPosition(position);
}

void Floor::SetSize(Vector2f size)
{
	hitbox.setSize(size);
}

const Vector2f& Floor::GetPos() const
{
	return position;
}

void Floor::Update(float dt)
{
	Object::Update(dt);
}

void Floor::Draw(RenderWindow& window)
{
	Object::Draw(window);
}

void Floor::SetHitBox(FloatRect rect)
{
	hitbox.setSize({ rect.width,rect.height });
	hitbox.setFillColor(Color(255, 0, 0, 255));
	SetPos({ rect.left,rect.top });
}

FloatRect Floor::GetGlobalBounds() const
{
	return hitbox.getGlobalBounds();
}

FloatRect Floor::GetLocalBounds() const
{
	return hitbox.getLocalBounds();
}

FloatRect Floor::GetHitBounds() const
{
	return hitbox.getGlobalBounds();
}
