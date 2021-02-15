#include <Platform/Window.h>

Window::Window(const WindowSettings& settings)
{
    m_Settings = settings;
    
    // For RAII fans.
    if (m_Settings.AutoInitialize)
        Create();
}

Window::~Window()
{
    glfwTerminate();
}

void Window::Create()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        // If we fail to initialize GLFW nothing will work so we just abort.
        std::abort();
    }
    
    // OpenGL 4.6 - Core Profile.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // On MacOS, forward compatibility must be enabled otherwise we cannot use
    // OpenGL >= 3.3. For now we don't care about MacOS support.
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    glfwSetErrorCallback([](int code, const char* msg) {
                             std::cerr << "GLFW Error: " << code << ". " << msg << std::endl;
                         });
    
    m_Window = glfwCreateWindow(m_Settings.Width, m_Settings.Height, m_Settings.Title.c_str(), nullptr, nullptr);
    
    if (m_Window == nullptr)
    {
        std::cerr << "Failed to create a window." << std::endl;
        // No window, no triangles.
        // We need to call glfwTerminate() since glfwInit was called before.
        glfwTerminate();
        std::abort();
    }
    
    glfwMakeContextCurrent(m_Window);
    
    // Load OpenGL function pointers using GLAD.
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to load OpenGL function pointers using GLAD." << std::endl;
        glfwTerminate();
        std::abort();
    }
    
    GLWrapper::Viewport(0, 0, m_Settings.Width, m_Settings.Height);
    glfwSetFramebufferSizeCallback(m_Window, Window::OnViewportResize);
    
    if (m_Settings.OnMouseMoved)
    {
        glfwSetCursorPosCallback(m_Window, m_Settings.OnMouseMoved);
    }
    
    if (m_Settings.OnMouseScrolled)
    {
        glfwSetScrollCallback(m_Window, m_Settings.OnMouseScrolled);
    }
    
    glEnable(GL_DEPTH_TEST); // @Important: Move this line somewhere else.
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::Clear(const glm::vec4& color, const uint32_t& bufferBits)
{
    GLWrapper::ClearColor(color);
    GLWrapper::Clear(bufferBits);
}

bool Window::IsOpen()
{
    return !glfwWindowShouldClose(m_Window);
}

bool Window::IsKeyPressed(const uint32_t& key)
{
    return glfwGetKey(m_Window, key) == GLFW_PRESS;
}

glm::vec2 Window::GetViewport() const
{
    return glm::vec2(m_Settings.Width, m_Settings.Height);
}

GLFWwindow* Window::GetWindowHandle() const
{
    return m_Window;
}

void Window::OnViewportResize(GLFWwindow* window, int width, int height)
{
    GLWrapper::Viewport(0, 0, width, height);
}