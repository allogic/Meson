#include "Vulkan/VulkanInstance.h"

Meson::Vulkan::CVulkanInstance::CVulkanInstance(const Glfw::CGlfwWindow& window)
	: mWindow(window) {
	if (IsDebugEnabled) {
		MESON_TRACE_IF_RETURN(
			CheckValidationLayerSupport() != MsResult::SUCCESS,
			"Failed validation layers not supported"
		);
	}

	MESON_TRACE_IF_RETURN(
		CreateVulkanInstace() != MsResult::SUCCESS,
		"Faile creating vulkan instance"
	);

	if (IsDebugEnabled) {
		MESON_TRACE_IF(
			mValidationLayer.CreateDebugUtilsMessengerExtension(
				mInstance,
				&mDebugUtilsMessageCreateInfoExt,
				nullptr) != MsResult::SUCCESS,
			"Failed creating debug messenger"
		);
	}
}

Meson::Vulkan::CVulkanInstance::~CVulkanInstance() {
	if (IsDebugEnabled) {
		MESON_TRACE_IF(
			mValidationLayer.DestroyDebugUtilsMessengerExtension(
				mInstance,
				&mDebugUtilsMessageCreateInfoExt,
				nullptr) != MsResult::SUCCESS,
			"Failed destroying debug messenger"
		);
	}

	vkDestroyInstance(mInstance, nullptr);
}

MsResult Meson::Vulkan::CVulkanInstance::CreateVulkanInstace() {
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = mWindow.Title().c_str();
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = mWindow.Title().c_str();
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = GetRequiredExtensions();

	if (IsDebugEnabled)
		extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	createInfo.enabledExtensionCount = static_cast<MsInt32>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	if (IsDebugEnabled) {
		createInfo.enabledLayerCount = 0;
		createInfo.pNext = nullptr;
	}
	else {
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

		createInfo.enabledLayerCount = static_cast<MsUInt32>(ValidationLayers.size());
		createInfo.ppEnabledLayerNames = ValidationLayers.data();
		createInfo.pNext = &mDebugUtilsMessageCreateInfoExt;
	}

	if (vkCreateInstance(&createInfo, nullptr, &mInstance) != VkResult::VK_SUCCESS) return MsResult::FAILED;

	return MsResult::SUCCESS;
}

std::vector<const MsChar8*> Meson::Vulkan::CVulkanInstance::GetRequiredExtensions() {
	MsUInt32 glfwExtensionCount = 0;

	const MsChar8** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	return { glfwExtensions, glfwExtensions + glfwExtensionCount };
}

MsResult Meson::Vulkan::CVulkanInstance::CheckValidationLayerSupport() {
	MsUInt32 layerCount;

	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const auto* pLayerName : ValidationLayers) {
		MsBool8 layerFound = false;

		for (const auto& layerProperties : availableLayers) {
			if (std::strcmp(pLayerName, layerProperties.layerName) == 0) {
				layerFound = true;

				break;
			}
		}

		if (!layerFound) return MsResult::FAILED;
	}

	return MsResult::SUCCESS;
}