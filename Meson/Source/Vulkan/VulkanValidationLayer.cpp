#include "Vulkan/VulkanValidationLayer.h"

MsResult Meson::Vulkan::CValidationLayer::CreateDebugUtilsMessengerExtension(
	VkInstance pInstance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator
) {
	auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
		vkGetInstanceProcAddr(pInstance, "vkCreateDebugUtilsMessengerEXT")
		);

	if (!func) return MsResult::INVALID_HANDLE;

	return
		func(pInstance, pCreateInfo, pAllocator, &mpDebugMessenger) == VkResult::VK_SUCCESS
		? MsResult::SUCCESS
		: MsResult::FAILED;
}

MsResult Meson::Vulkan::CValidationLayer::DestroyDebugUtilsMessengerExtension(
	VkInstance pInstance,
	const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator
) {
	auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
		vkGetInstanceProcAddr(pInstance, "vkDestroyDebugUtilsMessengerEXT")
		);

	if (!func) return MsResult::INVALID_HANDLE;

	func(pInstance, mpDebugMessenger, pAllocator);

	return MsResult::SUCCESS;
}