#pragma once

#include "Core.h"
#include "Types.h"

#include <glfw/glfw3.h>

namespace Meson {
	static auto* CreateWindow(INT width, INT height, const CHAR* title) {
		if (!glfwInit()) throw std::runtime_error("Failed initialising glfw");

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		auto* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		if (!window) throw std::runtime_error("Failed creating window");

		glfwMakeContextCurrent(window);

		return window;
	}

	static void DestroyWindow(GLFWwindow* window) {
		glfwDestroyWindow(window);

		glfwTerminate();
	}
}