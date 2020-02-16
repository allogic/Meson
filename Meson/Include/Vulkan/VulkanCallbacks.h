#pragma once

#include "../Core.h"

#include <vulkan/vulkan.h>

#ifndef NDEBUG
VKAPI_ATTR VkBool32 VKAPI_CALL MsVkDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messeageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) {
	MESON_TRACE(pCallbackData->pMessage);

	return VK_FALSE;
}
#endif