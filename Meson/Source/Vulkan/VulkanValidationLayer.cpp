#include "Vulkan/VulkanValidationLayer.h"

VkResult Meson::Vulkan::CValidationLayer::CreateDebugUtilsMessengerExtension(
	VkInstance pInstance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugUtilsMessengerEXT* pDebugMessenger
) {
	auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
		vkGetInstanceProcAddr(pInstance, "vkCreateDebugUtilsMessengerEXT")
		);

	if (func) return func(pInstance, pCreateInfo, pAllocator, pDebugMessenger);
	else return VK_ERROR_EXTENSION_NOT_PRESENT;
}