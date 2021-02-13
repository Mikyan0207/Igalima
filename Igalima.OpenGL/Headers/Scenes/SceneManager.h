#pragma once

#include <vector>
#include <iostream>
#include <Scenes/IScene.h>

class SceneManager
{
public:
	SceneManager() = default;
	SceneManager(const SceneManager&) = default;
	SceneManager(SceneManager&&) noexcept = default;
	~SceneManager() = default;

public:
	SceneManager& operator=(const SceneManager&) = default;
	SceneManager& operator=(SceneManager&&) noexcept = default;

public:
	void AddScene(IScene* scene);
	void RemoveScene(IScene* scene);
	void Clear();
	void DrawScene();
	void LoadScene(const std::string& name);

private:
	IScene* m_CurrentScene = nullptr;
	std::vector<IScene*> m_Scenes;
};