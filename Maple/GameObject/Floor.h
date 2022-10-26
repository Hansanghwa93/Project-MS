#pragma once
#include "Object.h"
#include "../Framework/Utils.h"

class Floor : public Object
{
protected:
	
public:
	Floor();
	~Floor();

	void Init();
		
	virtual void SetPos(const Vector2f& pos);
	void SetSize(Vector2f size);
	virtual const Vector2f& GetPos() const;

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual void SetHitBox(const FloatRect rect);

	FloatRect GetGlobalBounds() const;
	FloatRect GetLocalBounds() const;
	FloatRect GetHitBounds() const;
};

