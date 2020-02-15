#include "Application.h"

Meson::CApplication::CApplication(INT width, INT height, const CHAR* title) {
	mpGlfwWindow = Glfw::CreateWindow(width, height, title);
	mpVulkanInstance = Vulkan::CreateInstance(title);
}

Meson::CApplication::~CApplication() {
	Vulkan::DestroyInstance(mpVulkanInstance);
	Glfw::DestroyWindow(mpGlfwWindow);
}

void Meson::CApplication::Run() {
	if (!mpGlfwWindow || !mpVulkanInstance) return;

#ifndef NDEBUG
	Vulkan::CValidationLayer mValidationLayer(mpVulkanInstance);
#endif

	while (!glfwWindowShouldClose(mpGlfwWindow)) {
		glfwPollEvents();
	}
}