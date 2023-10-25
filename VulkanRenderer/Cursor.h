#pragma once
#include <glm/glm.hpp>

class GLFWwindow;
class Cursor
{
public:
	Cursor();
	static Cursor* Instance() { return instance; } // singleton

	glm::vec2 GetMousePosition() { return mousePosition; }
	//static void SetMousePosition(GLFWwindow* window, double x, double y);
	static void SetMousePosition(GLFWwindow* window, double x, double y)
	{
		instance->mousePosition.x = (float)x;
		instance->mousePosition.y = (float)y;
	}
protected:
	static Cursor* instance;
	glm::vec2 mousePosition;
};