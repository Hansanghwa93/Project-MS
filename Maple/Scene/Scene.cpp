#include "Scene.h"
#include "../Framework/Framework.h"
#include "../Framework/ResourceMgr.h"

Scene::Scene(Scenes type)
	: type(type)
{
}

Scene::~Scene()
{
	Release();
	
}

void Scene::Release()
{
	for (const auto& obj : objList)
	{
		obj->Release();
		delete obj;
	}
	objList.clear();
}

void Scene::Update(float dt)
{
	for (const auto& obj : objList)
	{
		if (obj->GetActive())
		{
			obj->Update(dt);
		}
	}
}

void Scene::Draw(RenderWindow& window)
{
	window.setView(worldView);
	for (auto& obj : objList)
	{
		if (obj->GetActive())
		{
			obj->Draw(window);
		}
	}
}

Texture* Scene::GetTexture(const string id)
{
	return RESOURCE_MGR->GetTexture(id);
}

Vector2f Scene::ScreenToWorldPos(Vector2i screenPos)
{
	RenderWindow& window = FRAMEWORK->GetWindow();
	return window.mapPixelToCoords(screenPos, worldView);
}
//
//Vector2f Scene::ScreenToUiPos(Vector2i screenPos)
//{
//	RenderWindow& window = FRAMEWORK->GetWindow();
//	return window.mapPixelToCoords(screenPos, uiView);
//}

Object* Scene::FindGameObj(String name)
{
	for (auto obj : objList)
	{
		if (obj->GetName() == name)
		{
			return obj;
		}
	}
	return nullptr;
}

void Scene::AddGameObj(Object* obj)
{
	objList.push_back(obj);
}