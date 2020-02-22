#pragma once

#include "../Core.h"
#include "../Types.h"
#include "../ResultCodes.h"

#include "VulkanPhysicalDevice.h"
#include "VulkanLogicalDevice.h"

#ifndef NDEBUG
#include "VulkanValidationLayers.h"
#include "VulkanValidationLayer.h"

static VkBool32 VKAPI_CALL MsVkDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messeageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {
	MESON_TRACE(pCallbackData->pMessage);

	return VK_FALSE;
}
#endif

#include <vulkan/vulkan.h>

#include <glfw/glfw3.h>

namespace Meson::Vulkan {
	class CInstance final {
	public:
		CInstance(const std::string& title);
		~CInstance();

	private:
		std::vector<const MsChar8*> GetRequiredExtensions();

	private:
		VkApplicationInfo mAppInfo;
		VkInstanceCreateInfo mCreateInfo;

		VkInstance mInstance;

		CVulkanPhysicalDevice* mpPhysicalDevice;
		CVulkanLogicalDevice* mpLogicalDevice;

#ifndef NDEBUG
	private:
		MsResult CheckValidationLayerSupport();

	private:
		VkDebugUtilsMessengerCreateInfoEXT mDebugUtilsMessageCreateInfoExt;
		CValidationLayer mValidationLayer;
#endif
	};
}