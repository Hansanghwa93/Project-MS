#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>

using namespace std;
using namespace sf;

enum class LoopTypes
{
	Single,
	Loop,
};

struct AnimationFrame
{
	//string textureId;
	Texture* texture;
	IntRect coord;
	Vector2f origin;
	bool flipX;
	bool flipY;

	AnimationFrame(const vector<string>& row);
};


struct AnimationClip
{
	string id;
	LoopTypes loopType;
	int fps;
	vector<AnimationFrame> frames;
};

struct AnimationEvent
{
	string clipId;
	int frame;	//이벤트를 발생시키고 싶은 프레임
	function<void()> onEvent;	//함수를 참조할 수 있는 객체 function<void(int,int)> 이렇게도 사용 가능
};