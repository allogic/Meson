#pragma once

#include "../Core.h"
#include "../Types.h"

#include "VulkanValidationLayer.h"

#include <vulkan/vulkan.h>

#include <glfw/glfw3.h>

namespace Meson::Vulkan {
	static BOOL CheckValidationLayerSupport() {
		UINT32 layerCount;

		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : CValidationLayer::ActiveLayers) {
			BOOL layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (std::strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;

					break;
				}
			}

			if (!layerFound) return false;
		}

		return true;
	}

	static auto GetRequiredExtensions() {
		UINT32 glfwExtensionCount = 0;

		const CHAR** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifndef  NDEBUG
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

		return extensions;
	}

	static auto CreateInstance(const CHAR* title) {
#ifndef NDEBUG
		MESON_TRACE_IF(
			CheckValidationLayerSupport() == false,
			"Failed validation layers not supported"
		);
#endif

		VkApplicationInfo appInfo{};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = title;
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = title;
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		auto extensions = GetRequiredExtensions();

		createInfo.enabledExtensionCount = static_cast<UINT32>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

#ifdef NDEBUG
		createInfo.enabledLayerCount = 0;

		createInfo.pNext = nullptr;
#else
		createInfo.enabledLayerCount = static_cast<UINT32>(CValidationLayer::ActiveLayers.size());
		createInfo.ppEnabledLayerNames = CValidationLayer::ActiveLayers.data();

		createInfo.pNext = &CValidationLayer::MessengerCreateInfo;
#endif

		//createInfo.enabledExtensionCount = glfwExtensionCount;
		//createInfo.ppEnabledExtensionNames = glfwExtensions;

		//createInfo.enabledLayerCount = 0;

		VkInstance instance;

		MESON_TRACE_IF(
			vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS,
			"Failed creating vulkan instance"
		);

		return instance;
	}

	static void DestroyInstance(VkInstance pInstance) {
		vkDestroyInstance(pInstance, nullptr);
	}
}