#pragma once

#include <Scenes/IScene.h>
#include <Camera.h>
#include <Graphics/Shapes/Terrain.h>
#include <Graphics/Textures/Skybox.h>
#include <Graphics/Noise.h>
#include <OpenGL/GLFramebuffer.h>

class PTG_Scene : public IScene
{
public:
	PTG_Scene(Camera* camera);
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
	Camera* m_Camera;
	Terrain* m_Terrain;
	Skybox* m_Skybox;
	Noise* m_Noise;
	GLFramebuffer* m_Framebuffer;
};