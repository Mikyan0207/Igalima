#include <Scenes/SceneManager.h>

void SceneManager::AddScene(IScene* scene)
{
	m_Scenes.emplace_back(scene);
}

void SceneManager::RemoveScene(IScene* scene)
{
	// @Speed: Don't use std::find_if
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&scene] (const auto& sc)
                           {
                               return scene->GetName() == sc->GetName();
                           });
    
	if (it != m_Scenes.end())
		m_Scenes.erase(it);
}

void SceneManager::Clear()
{
	m_Scenes.clear();
}

void SceneManager::DrawScene()
{
	m_CurrentScene->Draw();
}

void SceneManager::LoadScene(const std::string& name)
{
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [&name](const auto& sc)
                           {
                               return name == sc->GetName();
                           });
    
	if (it == m_Scenes.end())
	{
		std::cerr << "Scene " << name << " not found" << std::endl;
		return;
	}

	m_CurrentScene = *it;
}