#include "Vulkan/VulkanValidationLayer.h"

#include "Vulkan/VulkanCallbacks.h"

Meson::Vulkan::CValidationLayer::CValidationLayer(const CInstance& pInstance) {
	mCreateInfo = {};

	mCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	mCreateInfo.messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	mCreateInfo.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	mCreateInfo.pfnUserCallback = MsVkDebugCallback;

	MESON_TRACE_IF(
		CreateDebugUtilsMessengerExtension(
			pInstance.Ptr(),
			&mCreateInfo,
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