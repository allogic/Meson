#pragma once

#include "../Core.h"
#include "../Types.h"

#ifndef NDEBUG
#include "VulkanValidationLayer.h"
#include "VulkanCallback.h"
#endif

#include <vulkan/vulkan.h>

#include <glfw/glfw3.h>

namespace Meson::Vulkan {
	class CInstance final {
	public:
		constexpr static const std::array<const MsChar8*, 1> ActiveValidationLayers = {
			"VK_LAYER_KHRONOS_validation",
		};

	public:
		CInstance(const std::string& title);
		~CInstance();

	public:
		inline auto* Ptr() const { return mpInstance; }

	public:
		static auto CheckValidationLayerSupport() {
			MsUInt32 layerCount;

			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			std::vector<VkLayerProperties> availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

			for (const auto* layerName : ActiveValidationLayers) {
				MsBool8 layerFound = false;

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
			MsUInt32 glfwExtensionCount = 0;

			const MsChar8** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

			std::vector<const MsChar8*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifndef NDEBUG
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

			return extensions;
		}

	private:
		VkApplicationInfo mAppInfo;
		VkInstanceCreateInfo mCreateInfo;

		VkInstance mpInstance;

#ifndef DEBUG
	public:
		static auto& LinkDebugMessenger(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
			createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			createInfo.messageSeverity =
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			createInfo.messageType =
				VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
				VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			createInfo.pfnUserCallback = MsVkDebugCallback;

			return createInfo;
		}

	private:
		void MapDebugMessenger(
			CValidationLayer& validationLayer,
			const VkInstance pInstance,
			VkDebugUtilsMessengerCreateInfoEXT& createInfo
		) {
			MESON_TRACE_IF(
				mValidationLayer.CreateDebugUtilsMessengerExtension(
					pInstance,
					&LinkDebugMessenger(createInfo),
					nullptr,
					&mValidationLayer.GetDebugMessenger()) != VK_SUCCESS,
				"Failed mapping debug messenger"
			);

			validationLayer.CreateDebugUtilsMessengerExtension(
				pInstance,
				&LinkDebugMessenger(createInfo),
				nullptr,
				&validationLayer.GetDebugMessengerPtr());
		}

	private:
		CValidationLayer mValidationLayer;
#endif
	};
}