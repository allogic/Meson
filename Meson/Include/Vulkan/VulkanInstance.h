#pragma once

#include "../Core.h"
#include "../Types.h"
#include "../ResultCodes.h"

#include "../Glfw/GlfwWindow.h"

#ifndef NDEBUG
#include "VulkanValidationLayers.h"
#include "VulkanValidationLayer.h"

static VkBool32 VKAPI_CALL MsVkDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messeageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pserData) {
	MESON_TRACE(pCallbackData->pMessage);

	return VK_FALSE;
}
#endif

#include <vulkan/vulkan.h>

#include <glfw/glfw3.h>

namespace Meson::Vulkan {
	class CVulkanInstance final {
	public:
		CVulkanInstance(const Glfw::CGlfwWindow& window);
		~CVulkanInstance();

	public:
		inline const VkInstance& Instance() const { return mInstance; }

	private:
		std::vector<const MsChar8*> GetRequiredExtensions();

	private:
		VkInstance mInstance;

#ifndef NDEBUG
	private:
		MsResult CheckValidationLayerSupport();

	private:
		VkDebugUtilsMessengerCreateInfoEXT mDebugUtilsMessageCreateInfoExt;
		CValidationLayer mValidationLayer;
#endif
	};
}