#pragma once

#include "../Types.h"
#include "../Core.h"

#include "VulkanInstance.h"

#include <vulkan/vulkan.h>

namespace Meson::Vulkan {
	class CValidationLayer final {
	public:
		CValidationLayer(const CInstance& instance);

		VkResult CreateDebugUtilsMessengerExtension(
			VkInstance pInstance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger
		);

	private:
		VkDebugUtilsMessengerEXT mpDebugMessenger = nullptr;

		VkDebugUtilsMessengerCreateInfoEXT mCreateInfo;
	};
}