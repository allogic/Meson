#include "Vulkan/VulkanInstance.h"

Meson::Vulkan::CInstance::CInstance(const std::string& title) {
#ifndef NDEBUG
	MESON_TRACE_IF(
		CheckValidationLayerSupport() == MsResult::FAILED,
		"Failed validation layers not supported"
	);
#endif

	mAppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	mAppInfo.pApplicationName = title.c_str();
	mAppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	mAppInfo.pEngineName = title.c_str();
	mAppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	mAppInfo.apiVersion = VK_API_VERSION_1_0;

	mCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	mCreateInfo.pApplicationInfo = &mAppInfo;

	auto extensions = GetRequiredExtensions();

#ifndef NDEBUG
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

	mCreateInfo.enabledExtensionCount = static_cast<MsInt32>(extensions.size());
	mCreateInfo.ppEnabledExtensionNames = extensions.data();

#ifdef NDEBUG
	mCreateInfo.enabledLayerCount = 0;
	mCreateInfo.pNext = nullptr;
#else
	mDebugUtilsMessageCreateInfoExt.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	mDebugUtilsMessageCreateInfoExt.messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	mDebugUtilsMessageCreateInfoExt.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	mDebugUtilsMessageCreateInfoExt.pfnUserCallback = MsVkDebugCallback;

	mCreateInfo.enabledLayerCount = static_cast<MsUInt32>(ActiveValidationLayers.size());
	mCreateInfo.ppEnabledLayerNames = ActiveValidationLayers.data();
	mCreateInfo.pNext = &mDebugUtilsMessageCreateInfoExt;
#endif

	MESON_TRACE_IF(
		vkCreateInstance(&mCreateInfo, nullptr, &mInstance) != VkResult::VK_SUCCESS,
		"Failed creating vulkan instance"
	);

#ifndef NDEBUG
	MESON_TRACE_IF(
		mValidationLayer.CreateDebugUtilsMessengerExtension(
			mInstance,
			&mDebugUtilsMessageCreateInfoExt,
			nullptr) != MsResult::SUCCESS,
		"Failed mapping debug messenger"
	);
#endif

	mpPhysicalDevice = new CVulkanPhysicalDevice(mInstance);
	mpLogicalDevice = new CVulkanLogicalDevice(mpPhysicalDevice->Device());
}

Meson::Vulkan::CInstance::~CInstance() {
	delete mpLogicalDevice;
	delete mpPhysicalDevice;

#ifndef NDEBUG
	MESON_TRACE_IF(
		mValidationLayer.DestroyDebugUtilsMessengerExtension(
			mInstance,
			&mDebugUtilsMessageCreateInfoExt,
			nullptr) != MsResult::SUCCESS,
		"Failed mapping debug messenger"
	);
#endif

	vkDestroyInstance(mInstance, nullptr);
}

std::vector<const MsChar8*> Meson::Vulkan::CInstance::GetRequiredExtensions() {
	MsUInt32 glfwExtensionCount = 0;

	const MsChar8** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	return { glfwExtensions, glfwExtensions + glfwExtensionCount };
}

MsResult Meson::Vulkan::CInstance::CheckValidationLayerSupport() {
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

		if (!layerFound) return MsResult::FAILED;
	}

	return MsResult::SUCCESS;
}
