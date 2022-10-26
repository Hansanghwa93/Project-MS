#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <map>

using namespace sf;
using namespace std;

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;
	list<Keyboard::Key> positives;
	list<Keyboard::Key> negatives;

	float sensi;
	float value;
};

// ����ƽ �Լ��� �̿��ؼ� Ű���� �� ���콺 �Է��� �˻��� �� �ִ� Ŭ����

class InputMgr
{
private:
	static map<Axis, AxisInfo> axisInfoMap;

	static list<Keyboard::Key> downList; // 
	static list<Keyboard::Key> ingList;	 // 
	static list<Keyboard::Key> upList;	 // 
	
	static list<Mouse::Button> mousedownList; // 
	static list<Mouse::Button> mouseingList;	 // 
	static list<Mouse::Button> mouseupList;	 // 

	static Vector2f mousePos;

public:
	static void Init();
	static void Update(float dt);
	static void ProcessInput(Event& ev);

	static bool GetKeyDown(Keyboard::Key key);
	static bool GetKey(Keyboard::Key key);
	static bool GetKeyUp(Keyboard::Key key);
	static bool GetMouseDown(Mouse::Button key);
	static bool GetMouse(Mouse::Button key);
	static bool GetMouseUp(Mouse::Button key);

	static float GetAxis(Axis axis);
	static float GetAxisRaw(Axis axis);

	static const Vector2f& GetMousePos();
};