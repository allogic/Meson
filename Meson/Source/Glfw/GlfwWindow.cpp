#include "Glfw/GlfwWindow.h"

Meson::Glfw::CGlfwWindow::CGlfwWindow(MsUInt32 width, MsUInt32 height, const std::string& title)
	: mWidth(width)
	, mHeight(height)
	, mTitle(title) {
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

	glfwMakeContextCurrent(mpWindow);
}

Meson::Glfw::CGlfwWindow::~CGlfwWindow() {
	glfwDestroyWindow(mpWindow);

	glfwTerminate();
}