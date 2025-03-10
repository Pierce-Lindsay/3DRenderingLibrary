#include "window.h"

void Window::init()
{
	//graphics and window initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_VSYNC, GLFW_FALSE);

	window = glfwCreateWindow(width, height, "3dRender", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		throw;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << '\n';
		throw;
	}

	glViewport(0, 0, 1920, 1080);

}

void Window::update()
{
	//update window height and width
	glfwGetWindowSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSwapBuffers(window);
	glfwPollEvents();
}

bool Window::isOpen()
{
	return !glfwWindowShouldClose(window);
}
void Window::terminate()
{
	glfwTerminate();
}

GLFWwindow* Window::getWindow()
{
	return window;
}

float Window::getAspectRatio()
{
	//avoid divide by zero when window closed
	if (height == 0)
		return 0;
	return float(width) / float(height);
}