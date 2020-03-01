#pragma once

/*
* TODO:
*  further improvement VulkanValidationLayer.h -> auto dynamic linking process
*  remove `p` from all vulkan member/arg variable names
*  refactor result codes -> like Types.h
*  refactor CVulkanInstance -> C++14/11
*  write custom allocator for vulkan like types and or internals
*/

#include "Core.h"
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