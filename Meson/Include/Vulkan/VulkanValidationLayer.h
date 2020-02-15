#pragma once

#include "../Types.h"
#include "../Core.h"
#include "../Utils.h"

#include <vulkan/vulkan.h>

namespace Meson::Vulkan {
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messeageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData
	) {
		MESON_TRACE(pCallbackData->pMessage);

		return VK_FALSE;
	}

	class CValidationLayer final {
	public:
		constexpr static const std::array<const char*, 1> ActiveLayers{
			"VK_LAYER_KHRONOS_validation",
		};

	public:
		CValidationLayer(const VkInstance pInstance);

	public:
		constexpr static const auto MessengerCreateInfo = Utils::Declare([] {
			VkDebugUtilsMessengerCreateInfoEXT createInfo{};

			createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			createInfo.messageSeverity =
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			createInfo.messageType =
				VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			createInfo.pfnUserCallback = DebugCallback;

			return createInfo;
			});

	private:
		void LinkDebugMessenger(const VkInstance pInstance);

		VkResult CreateDebugUtilsMessengerExtension(
			VkInstance pInstance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger
		);

	private:
		VkDebugUtilsMessengerEXT mpDebugMessenger = nullptr;
	};
}