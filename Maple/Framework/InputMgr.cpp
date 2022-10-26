#include "InputMgr.h"
#include <iostream>
#include <algorithm>
#include "Framework.h"

map<Axis, AxisInfo> InputMgr::axisInfoMap;

list<Keyboard::Key> InputMgr::downList;
list<Keyboard::Key> InputMgr::ingList;
list<Keyboard::Key> InputMgr::upList;

list<Mouse::Button> InputMgr::mousedownList;
list<Mouse::Button> InputMgr::mouseingList;
list<Mouse::Button> InputMgr::mouseupList;

Vector2f InputMgr::mousePos;

void InputMgr::Init()
{
	// Horizontal
	AxisInfo infoH;
	infoH.axis = Axis::Horizontal;
	infoH.positives.push_back(Keyboard::Key::D);
	infoH.positives.push_back(Keyboard::Key::Right);

	infoH.negatives.push_back(Keyboard::Key::A);
	infoH.negatives.push_back(Keyboard::Key::Left);

	infoH.sensi = 5.0f;
	infoH.value = 0.f;

	axisInfoMap.insert({ infoH.axis, infoH });

	// Vertical
	AxisInfo infoV;
	infoV.axis = Axis::Vertical;

	infoV.positives.push_back(Keyboard::Key::S);
	infoV.positives.push_back(Keyboard::Key::Down);

	infoV.negatives.push_back(Keyboard::Key::W);
	infoV.negatives.push_back(Keyboard::Key::Up);


	infoV.sensi = 5.0f;
	infoV.value = 0.f;

	axisInfoMap.insert({ infoV.axis, infoV });
}

void InputMgr::Update(float dt)
{
	downList.clear();
	upList.clear();
	mousedownList.clear();
	mouseupList.clear();

	for (auto& it : axisInfoMap)
	{
		AxisInfo& axis = it.second;
		float raw = GetAxisRaw(axis.axis);

		if (raw == 0.f && axis.value != 0.f)
		{
			raw = axis.value > 0.f ? -1.f : 1.f;
		}
		axis.value += raw * axis.sensi * dt;

		if (axis.value > 1.0)
			axis.value = 1.f;
		if (axis.value < -1.0)
			axis.value = -1.f;
		if (abs(axis.value) < 0.001f)
			axis.value = 0.f;
	}
	mousePos = (Vector2f)Mouse::getPosition(FRAMEWORK->GetWindow());
}

void InputMgr::ProcessInput(Event& ev)
{
	switch (ev.type)
	{
	case Event::EventType::MouseButtonPressed:
		if (find(mouseingList.begin(), mouseingList.end(), ev.mouseButton.button) == mouseingList.end())
		{
			mousedownList.push_back(ev.mouseButton.button);
			mouseingList.push_back(ev.mouseButton.button);
		}
		break;
	case Event::EventType::MouseButtonReleased:
		mouseingList.remove(ev.mouseButton.button);
		mouseupList.push_back(ev.mouseButton.button);
		break;
	case Event::EventType::KeyPressed:
		if (find(ingList.begin(), ingList.end(), ev.key.code) == ingList.end())
		{
			downList.push_back(ev.key.code);
			ingList.push_back(ev.key.code);
		}
		break;
	case Event::EventType::KeyReleased:
		ingList.remove(ev.key.code);
		upList.push_back(ev.key.code);
		break;
	}
}

bool InputMgr::GetKeyDown(Keyboard::Key key)
{
	return find(downList.begin(), downList.end(), key) != downList.end();
}

bool InputMgr::GetKey(Keyboard::Key key)
{
	return find(ingList.begin(), ingList.end(), key) != ingList.end();
}

bool InputMgr::GetKeyUp(Keyboard::Key key)
{
	return find(upList.begin(), upList.end(), key) != upList.end();
}

bool InputMgr::GetMouseDown(Mouse::Button key)
{
	return find(mousedownList.begin(), mousedownList.end(), key) != mousedownList.end();
}

bool InputMgr::GetMouse(Mouse::Button key)
{
	return find(mouseingList.begin(), mouseingList.end(), key) != mouseingList.end();
}

bool InputMgr::GetMouseUp(Mouse::Button key)
{
	return find(mouseupList.begin(), mouseupList.end(), key) != mouseupList.end();
}

float InputMgr::GetAxis(Axis axis)
{
	return axisInfoMap[axis].value;
}

float InputMgr::GetAxisRaw(Axis axis)
{
	const AxisInfo& info = axisInfoMap[axis];

	auto it = ingList.rbegin();
	while (it != ingList.rend())
	{
		Keyboard::Key key = *it;
		if (find(info.negatives.begin(), info.negatives.end(), key) !=
			info.negatives.end())
		{
			return -1.f;
		}
		if (find(info.positives.begin(), info.positives.end(), key) !=
			info.positives.end())
		{
			return 1.f;
		}
		++it;
	}
	return 0.f;

}

const Vector2f& InputMgr::GetMousePos()
{
	return mousePos;
}
