#include "window.h"

void Window::init()
{
	//graphics and window initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1920, 1080, "3dRender", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << '\n';
		glfwTerminate();
		throw;
	}
	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << '\n';
		throw;
	}

	glViewport(0, 0, 1920, 1080);

}

void Window::update()
{
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