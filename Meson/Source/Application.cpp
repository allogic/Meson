#include "Application.h"

#include "Vulkan/VulkanValidationLayer.h"

Meson::CApplication::CApplication(MsUInt32 width, MsUInt32 height, const std::string& title) {
	mpGlfwWindow = new Glfw::CWindow(width, height, title);
	mpVulkanInstance = new Vulkan::CInstance(title);
}

Meson::CApplication::~CApplication() {
	delete mpVulkanInstance;
	delete mpGlfwWindow;
}

MsResult Meson::CApplication::Run() {
	if (!mpGlfwWindow || !mpVulkanInstance) return MsResult::FAILED;

	while (!glfwWindowShouldClose(mpGlfwWindow->Ptr())) {
		glfwPollEvents();
	}

	return MsResult::SUCCESS;
}