#pragma once

#include "../Core.h"
#include "../Types.h"

#include <glfw/glfw3.h>

namespace Meson::Glfw {
	static auto* CreateWindow(INT width, INT height, const CHAR* title) {
		MESON_TRACE_IF(
			glfwInit() == GLFW_FALSE,
			"Failed initialising glfw"
		);

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		auto* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		MESON_TRACE_IF(
			window == nullptr,
			"Failed creating glfw window"
		);

		glfwMakeContextCurrent(window);

		return window;
	}

	static void DestroyWindow(GLFWwindow* window) {
		glfwDestroyWindow(window);

		glfwTerminate();
	}
}