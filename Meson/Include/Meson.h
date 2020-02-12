#pragma once

#include "Core.h"
#include "Types.h"
#include "Application.h"

extern Meson::CApplication* Create();

#define MESON_CREATE_APP(CLASS) Meson::CApplication* Create() { return new CLASS; }

int main(INT argc, CHAR** argv) {
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