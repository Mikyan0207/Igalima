#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>

#include <Graphics/Shapes/Sphere.h>
#include <Graphics/Textures/Texture.h>
#include <Graphics/Textures/Skybox.h>
#include <Camera.h>
#include <Graphics/Model.h>

#include <OpenGL/GLVertexArray.h>
#include <OpenGL/GLVertexBuffer.h>
#include <OpenGL/GLShader.h>

#include <Graphics/Noise.h>
#include <Graphics/Shapes/Terrain.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// Camera & Mouse.
static Camera GlobalCamera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 400, lastY = 300;
bool firstMouse = true;
bool CursorMode = false;

#pragma region Terrain
#pragma endregion

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (CursorMode)
		return;
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	GlobalCamera.ProcessMouseEvents(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	GlobalCamera.ProcessScrollEvents(yoffset);
}

void Process_Keyboard_Inputs(GLFWwindow* window)
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
		GlobalCamera.ProcessKeyboardEvents(CameraDirection::FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		GlobalCamera.ProcessKeyboardEvents(CameraDirection::BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		GlobalCamera.ProcessKeyboardEvents(CameraDirection::LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		GlobalCamera.ProcessKeyboardEvents(CameraDirection::RIGHT, deltaTime);
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
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW." << std::endl;
		std::abort();
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwSetErrorCallback([](int errorCode, const char* description) -> void
		{
			std::cerr << "GLFW Error: " << errorCode << ". " << description << std::endl;
		});

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Igalima.OpenGL", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW Window." << std::endl;
		glfwTerminate();
		std::abort();
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		std::abort();
	}

#pragma region ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	const char* glsl_version = "#version 330";
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
#pragma endregion

	//stbi_set_flip_vertically_on_load(true);

	glViewport(0, 0, 1280, 720);
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Shaders
	GLShader skyboxShader("Resources/Shaders/Skybox.vs", "Resources/Shaders/Skybox.fs");

	Noise noise;
	Terrain terrain(100);
	Skybox skybox({
		"Resources/skybox/right.jpg",
		"Resources/skybox/left.jpg",
		"Resources/skybox/top.jpg",
		"Resources/skybox/bottom.jpg",
		"Resources/skybox/front.jpg",
		"Resources/skybox/back.jpg",
	});

	skyboxShader.Use();
	skyboxShader.SetInt("skybox", 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Testing classes
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		Process_Keyboard_Inputs(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// GOING 3D
		glm::mat4 projection = glm::perspective(glm::radians(GlobalCamera.FOV), 1280.0f / 720.0f, 0.1f, 100.0f);
		glm::mat4 view = GlobalCamera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(.005f, .005f, .005f));
		//shader.Use();
		//shader.SetMat4("view", view);
		//shader.SetMat4("projection", projection);
		//shader.SetMat4("model", model);

		//noise.Draw();
		terrain.SetMVP(model, view, projection);
		terrain.Draw();

		//backpack.Draw(shader);

		skyboxShader.Use();
		view = glm::mat4(glm::mat3(GlobalCamera.GetViewMatrix())); // Remove translation from view matrix.
		skyboxShader.SetMat4("view", view);
		skyboxShader.SetMat4("projection", projection);

		skybox.Draw(skyboxShader);

		ImGuiWindow();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
