#include "Application.h"

#include "Vulkan/VulkanValidationLayer.h"

Meson::CApplication::CApplication(MsUInt32 width, MsUInt32 height, const std::string& title) {
	mpGlfwWindow = std::make_unique<Glfw::CWindow>(width, height, title);
	mpVulkanInstance = std::make_unique<Vulkan::CInstance>(title);
}

void Meson::CApplication::Run() {
	if (!mpGlfwWindow || !mpVulkanInstance) return;

	while (!glfwWindowShouldClose(mpGlfwWindow->Ptr())) {
		glfwPollEvents();
	}
}