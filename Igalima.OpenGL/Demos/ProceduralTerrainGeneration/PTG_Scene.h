#pragma once

#include <Scenes/IScene.h>

class PTG_Scene : IScene
{
public:
	PTG_Scene();
	PTG_Scene(const PTG_Scene&) = delete;
	PTG_Scene(PTG_Scene&&) noexcept = delete;
	~PTG_Scene() final;

public:
	PTG_Scene& operator=(const PTG_Scene&) = delete;
	PTG_Scene& operator=(PTG_Scene&&) noexcept = delete;

public:
	void Draw() final;

public:
	const std::string& GetName() const final;

private:
	std::string m_Name;
};