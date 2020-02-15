#include "Vulkan/VulkanValidationLayer.h"

Meson::Vulkan::CValidationLayer::CValidationLayer(const VkInstance pInstance) {
	LinkDebugMessenger(pInstance);
}

void Meson::Vulkan::CValidationLayer::LinkDebugMessenger(const VkInstance pInstance) {
	MESON_TRACE_IF(
		CreateDebugUtilsMessengerExtension(
			pInstance,
			&MessengerCreateInfo,
			nullptr,
			&mpDebugMessenger) != VK_SUCCESS,
		"Failed setting up debug messenger"
	);
}

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