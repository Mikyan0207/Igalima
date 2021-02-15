#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>

#include <Platform/Window.h>
#include <Scenes/SceneManager.h>
#include <Graphics/Textures/Skybox.h>
#include <Camera.h>

/// ----- Demos Files -----
#include <ProceduralTerrainGeneration/PTG_Scene.h>
#include <ImageViewer/ImageViewer_Scene.h>

#include <OpenGL/GLFramebuffer.h>
#include <OpenGL/GLVertexArray.h>
#include <OpenGL/GLVertexBuffer.h>
#include <OpenGL/GLShader.h>
#include <OpenGL/GLWrapper.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// Camera & Mouse.
static Camera* GlobalCamera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
static float LastX = 400;
static float LastY = 300;
static bool FirstMouse = true;
static bool CursorMode = false;

// Delta Time.
// Move this in Time class or Window class
static float DeltaTime = 0.0f;
static float LastFrame = 0.0f;

void OnMouseMoved(GLFWwindow* window, double xpos, double ypos)
{
	if (CursorMode)
		return;
    
	const float fxpos = static_cast<float>(xpos);
	const float fypos = static_cast<float>(ypos);
    
	if (FirstMouse)
	{
		LastX = fxpos;
		LastY = fypos;
		FirstMouse = false;
	}
    
	float xoffset = fxpos - LastX;
	float yoffset = LastY - fypos;
	LastX = fxpos;
	LastY = fypos;
    
	GlobalCamera->ProcessMouseEvents(xoffset, yoffset);
}

void OnMouseScrolled(GLFWwindow* window, double xoffset, double yoffset)
{
	GlobalCamera->ProcessScrollEvents(static_cast<float>(yoffset));
}

void ProcessKeyboardInputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
    
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		CursorMode = true;
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		CursorMode = false;
	}
    
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		GlobalCamera->ProcessKeyboardEvents(CameraDirection::FORWARD, DeltaTime);
    
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		GlobalCamera->ProcessKeyboardEvents(CameraDirection::BACKWARD, DeltaTime);
    
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		GlobalCamera->ProcessKeyboardEvents(CameraDirection::LEFT, DeltaTime);
    
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		GlobalCamera->ProcessKeyboardEvents(CameraDirection::RIGHT, DeltaTime);
}

void ImGuiWindow()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
    
	ImGui::Begin("Statistics");
	ImGui::Text("Application average %.3f ms/frame (%.2f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
    
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int main()
{
	Window window(WindowSettings {
                      1280, 720,
                      "Igalima.OpenGL",
                      &OnMouseMoved,
                      &OnMouseScrolled,
                      true // AutoInit -> RAII.
                  });
    
	SceneManager sceneManager;
	ImageViewer_Scene ivScene(GlobalCamera);
    
    sceneManager.AddScene(&ivScene);
    sceneManager.LoadScene("IV_Scene");
    
#pragma region ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
    
    const char* glsl_version = "#version 330";
	ImGui_ImplGlfw_InitForOpenGL(window.GetWindowHandle(), true);
	ImGui_ImplOpenGL3_Init(glsl_version);
#pragma endregion
    
	while (window.IsOpen())
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		DeltaTime = currentFrame - LastFrame;
		LastFrame = currentFrame;
        
		ProcessKeyboardInputs(window.GetWindowHandle());
		window.Clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f), GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
		sceneManager.DrawScene();
        
		ImGuiWindow();
		window.SwapBuffers();
		window.PollEvents();
	}
    
	delete GlobalCamera;
	return 0;
}
