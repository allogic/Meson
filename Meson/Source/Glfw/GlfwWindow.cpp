#include "Glfw/GlfwWindow.h"

Meson::Glfw::CWindow::CWindow(MsUInt32 width, MsUInt32 height, const std::string& title) {
	MESON_TRACE_IF(
		glfwInit() == GLFW_FALSE,
		"Failed initialising glfw"
	);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	mpWindow = glfwCreateWindow(
		static_cast<MsInt32>(width),
		static_cast<MsInt32>(height),
		title.c_str(),
		nullptr,
		nullptr
	);

	MESON_TRACE_IF(
		mpWindow == nullptr,
		"Failed creating glfw window"
	);

	glfwMakeContextCurrent(mpWindow);
}

Meson::Glfw::CWindow::~CWindow() {
	glfwDestroyWindow(mpWindow);

	glfwTerminate();
}