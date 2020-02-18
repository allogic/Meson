#include "Application.h"

#include "Vulkan/VulkanValidationLayer.h"

Meson::CApplication::CApplication(MsUInt32 width, MsUInt32 height, const std::string& title) {
	mpGlfwWindow = std::make_unique<Glfw::CWindow>(width, height, title);
	mpVulkanInstance = std::make_unique<Vulkan::CInstance>(title);
}

MsResult Meson::CApplication::Run() {
	if (!mpGlfwWindow || !mpVulkanInstance) return MsResult::FAILED;

	while (!glfwWindowShouldClose(mpGlfwWindow->Ptr())) {
		glfwPollEvents();
	}

	return MsResult::SUCCESS;
}