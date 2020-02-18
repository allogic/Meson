#pragma once

#include "../Core.h"
#include "../Types.h"
#include "../ResultCodes.h"

#ifndef NDEBUG
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
		constexpr static const std::array<const MsChar8*, 1> ActiveValidationLayers = {
			"VK_LAYER_KHRONOS_validation",
		};

	public:
		CInstance(const std::string& title);
		~CInstance();

	public:
		inline auto* Ptr() const { return mpInstance; }

	private:
		std::vector<const MsChar8*> GetRequiredExtensions();
		MsResult GetPhysicalDevice();
		MsResult CheckPhysicalDeviceCapability(VkPhysicalDevice device);
		MsResult CheckQueueFamilies(VkPhysicalDevice device);

	private:
		VkApplicationInfo mAppInfo;
		VkInstanceCreateInfo mCreateInfo;
		VkInstance mpInstance;
		VkPhysicalDevice mPhysicalDevice;

#ifndef NDEBUG
	private:
		MsResult CheckValidationLayerSupport();

	private:
		VkDebugUtilsMessengerCreateInfoEXT mDebugUtilsMessageCreateInfoExt;
		CValidationLayer mValidationLayer;
#endif
	};
}