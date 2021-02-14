#include "PTG_Scene.h"
#include <Platform/CycleCounter.h>

// NOTE: Maybe we should pass a pointer to the window if we want to access viewport data?
// For now we don't care about inputs since we'll be using XInput in the future instead
// of GLFW because at some point we'll just remove GLFW and use the Windows API.
PTG_Scene::PTG_Scene(Camera* camera)
{
    m_Name = "PTG_Scene";
    m_Camera = camera;
    m_Skybox = new Skybox({
        "Resources/Shaders/Skybox.vs",
        "Resources/Shaders/Skybox.fs",
        {
            "Resources/skybox/right.jpg",
            "Resources/skybox/left.jpg",
            "Resources/skybox/top.jpg",
            "Resources/skybox/bottom.jpg",
            "Resources/skybox/front.jpg",
            "Resources/skybox/back.jpg"
        }
    });
    m_Noise = new Noise();
    m_Framebuffer = new GLFramebuffer(200, 200, 1280, 720);
    
    // ????
    {
        m_Framebuffer->Bind();
        GLWrapper::Clear(GL_DEPTH_BUFFER_BIT);
        m_Noise->Draw();
        m_Framebuffer->Unbind();
    }
    m_Terrain = new Terrain(200, m_Framebuffer->GetColorAttachmentId());
}

PTG_Scene::~PTG_Scene()
{
	delete m_Terrain;
	delete m_Skybox;
	delete m_Noise;
    
	m_Camera = nullptr;
}

void PTG_Scene::Draw()
{
#if _DEBUG
    CycleCounter::BeginCounter();
#endif
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = m_Camera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(m_Camera->FOV), 1280.0f / 720.0f, 0.01f, 100000.0f);
    
	//model = glm::scale(model, glm::vec3(0.5f));
    
	m_Terrain->SetMVP(model, view, projection);
	m_Terrain->Draw();
    
	// Remove translation from view matrix.
	view = glm::mat4(glm::mat3(m_Camera->GetViewMatrix()));
	m_Skybox->Draw(view, projection);
    
#if _DEBUG
	CycleCounter::EndCounter();
	std::cout << "MegaCycles/Frame: " << CycleCounter::MegaCyclesPerFrame << std::endl;
#endif
}

const std::string& PTG_Scene::GetName() const
{
	return m_Name;
}