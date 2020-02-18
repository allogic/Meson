#pragma once

#include "../Types.h"
#include "../Core.h"
#include "../ResultCodes.h"

#include <vulkan/vulkan.h>

namespace Meson::Vulkan {
	class CInstance;

	class CValidationLayer final {
	public:
		CValidationLayer() = default;

	public:
		MsResult CreateDebugUtilsMessengerExtension(
			VkInstance pInstance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator
		);
		MsResult DestroyDebugUtilsMessengerExtension(
			VkInstance pInstance,
			const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
			const VkAllocationCallbacks* pAllocator
		);

		inline VkDebugUtilsMessengerEXT& GetDebugUtilsMessengerPtr() { return mpDebugMessenger; }

	private:
		VkDebugUtilsMessengerEXT mpDebugMessenger = nullptr;
	};
}