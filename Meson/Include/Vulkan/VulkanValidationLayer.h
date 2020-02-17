#pragma once

#include "../Types.h"
#include "../Core.h"

#include <vulkan/vulkan.h>

namespace Meson::Vulkan {
	class CInstance;

	class CValidationLayer final {
	public:
		CValidationLayer() = default;

	public:
		VkResult CreateDebugUtilsMessengerExtension(
			VkInstance pInstance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator,
			VkDebugUtilsMessengerEXT* pDebugMessenger
		);
		inline VkDebugUtilsMessengerEXT GetDebugMessengerPtr() { return mpDebugMessenger; }

	private:
		VkDebugUtilsMessengerEXT mpDebugMessenger = nullptr;

		VkDebugUtilsMessengerCreateInfoEXT mCreateInfo;
	};
}