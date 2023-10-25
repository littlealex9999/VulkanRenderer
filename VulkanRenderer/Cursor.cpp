#include "Cursor.h"
#include <stdexcept>
#include <GLFW/glfw3.h>

Cursor* Cursor::instance = nullptr;

Cursor::Cursor()
{
	if (instance == nullptr) {
		instance = this;
	} else if (instance != this) {
		throw std::invalid_argument("Cannot construct more than one 'Cursor'");
	}
}

//void Cursor::SetMousePosition(GLFWwindow* window, double x, double y)
//{
//	instance->mousePosition.x = (float)x;
//	instance->mousePosition.y = (float)y;
//}