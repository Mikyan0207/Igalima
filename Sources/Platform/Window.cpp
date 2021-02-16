#include <Platform/Window.h>

// NOTE(Mikyan): Maybe later we'll replace GLFW with the Windows API.

Window::Window(WindowSettings settings)
{
    Settings = settings;
    
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
    
    // Set Window hints.
    // Profile will be set to Core for now. Maybe later we'll let the user choose.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Settings.OpenGL_MajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Settings.OpenGL_MinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // On MacOS, forward compatibility must be enabled if we want to use OpenGL >= 3.3
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Maybe we want to ignore Settings.Width & Settings.Height when FullScreen is enabled?
    if (Settings.FullScreen)
    {
        m_Window = glfwCreateWindow(Settings.Width, Settings.Height, Settings.Title, glfwGetPrimaryMonitor(), nullptr);
    }
    else
    {
        m_Window = glfwCreateWindow(Settings.Width, Settings.Height, Settings.Title, nullptr, nullptr);
    }
    
    if (m_Window == nullptr)
    {
        std::cerr << "Failed to create a window" << std::endl;
        
        // No window, no triangles.
        // We need to call glfwTerminate() since glfwInit was called.
        glfwTerminate();
        std::abort();
    }
    
    glfwMakeContextCurrent(m_Window);
    
    // Load OpenGL functions using GLAD.
    // If we cannot load any function, we can stop the program and report an error
    // since none of the OpenGL function call will work.
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::cerr << "Failed to load OpenGL functions using GLAD." << std::endl;
        glfwTerminate();
        std::abort();
    }
}