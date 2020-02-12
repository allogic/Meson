#include "Application.h"

Meson::CApplication::CApplication(INT width, INT height, const CHAR* title) {
	mWindow = CreateWindow(width, height, title);
}

Meson::CApplication::~CApplication() {
	DestroyWindow(mWindow);
}

void Meson::CApplication::Run() {
	while (!glfwWindowShouldClose(mWindow)) {
		glfwPollEvents();
	}
}