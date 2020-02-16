#include "Application.h"

#include "Vulkan/VulkanValidationLayer.h"
#include "Vulkan/VulkanValidationLayers.h"

static auto CheckValidationLayerSupport() {
	MsUInt32 layerCount;

	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const auto* layerName : MsVkValidationLayers) {
		MsBool8 layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (std::strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;

				break;
			}
		}

		if (!layerFound) return false;
	}

	return true;
}

static auto GetRequiredExtensions() {
	MsUInt32 glfwExtensionCount = 0;

	const MsChar8** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const MsChar8*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifndef NDEBUG
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

	return extensions;
}

Meson::CApplication::CApplication(MsUInt32 width, MsUInt32 height, const std::string& title) {
	mpGlfwWindow = std::make_unique<Glfw::CWindow>(width, height, title);
	mpVulkanInstance = std::make_unique<Vulkan::CInstance>(title);

#ifndef NDEBUG
	Vulkan::CValidationLayer mValidationLayer(*mpVulkanInstance);
#endif
}

void Meson::CApplication::Run() {
	if (!mpGlfwWindow || !mpVulkanInstance) return;

	while (!glfwWindowShouldClose(mpGlfwWindow->Ptr())) {
		glfwPollEvents();
	}
}