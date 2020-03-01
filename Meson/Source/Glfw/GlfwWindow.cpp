#include "Glfw/GlfwWindow.h"

Meson::Glfw::CGlfwWindow::CGlfwWindow(MsUInt32 width, MsUInt32 height, const std::string& title)
	: mWidth(width)
	, mHeight(height)
	, mTitle(title) {
	MESON_TRACE_IF_RETURN(
		CreateGlfwContext() != MsResult::SUCCESS,
		"Failed creating glfw context"
	);
}

Meson::Glfw::CGlfwWindow::~CGlfwWindow() {
	glfwDestroyWindow(mpWindow);

	glfwTerminate();
}

MsResult Meson::Glfw::CGlfwWindow::CreateGlfwContext() {
	if (glfwInit() == GLFW_FALSE) return MsResult::FAILED;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	mpWindow = glfwCreateWindow(
		static_cast<MsInt32>(mWidth),
		static_cast<MsInt32>(mHeight),
		mTitle.c_str(),
		nullptr,
		nullptr
	);

	if (!mpWindow) return MsResult::FAILED;

	glfwMakeContextCurrent(mpWindow);

	return MsResult::SUCCESS;
}