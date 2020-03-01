#pragma once

#include "../Core.h"

#include "../Glfw/GlfwWindow.h"

#include "VulkanValidationLayer.h"

#include <vulkan/vulkan.h>

#include <glfw/glfw3.h>

static VkBool32 VKAPI_CALL MsVkDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messeageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {
	MESON_TRACE(pCallbackData->pMessage);

	return VK_FALSE;
}

namespace Meson::Vulkan {
	class CVulkanInstance final {
	public:
		CVulkanInstance(const Glfw::CGlfwWindow& window);
		~CVulkanInstance();

	public:
		inline const VkInstance& Instance() const { return mInstance; }

	private:
		MsResult CheckValidationLayerSupport();
		MsResult CreateVulkanInstace();
		std::vector<const MsChar8*> GetRequiredExtensions();

	private:
		const Glfw::CGlfwWindow& mWindow;

		VkInstance mInstance;

		VkDebugUtilsMessengerCreateInfoEXT mDebugUtilsMessageCreateInfoExt;
		CValidationLayer mValidationLayer;
	};
}