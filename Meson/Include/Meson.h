#pragma once

/*
* TODO:
* further improvement VulkanValidationLayer.h -> auto dynamic linking process
*/

#include "Core.h"

#include <vulkan/vulkan.h>

#include "Glfw/GlfwWindow.h"

#include "Application.h"

extern Meson::CApplication* Create();

#define MESON_CREATE_APP(CLASS) Meson::CApplication* Create() { return new CLASS; }

int main(MsInt32 argc, MsChar8** argv) {
	try {
		auto* app = Create();

		if (app) app->Run();

		delete app;
	}
	catch (const std::exception & ex) {
		MESON_TRACE(ex.what());

		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}