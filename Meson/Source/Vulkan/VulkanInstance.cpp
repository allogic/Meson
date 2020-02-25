#include "Vulkan/VulkanInstance.h"

Meson::Vulkan::CVulkanInstance::CVulkanInstance(GLFWwindow* pWindow, const std::string& title) {
#ifndef NDEBUG
	MESON_TRACE_IF(
		CheckValidationLayerSupport() == MsResult::FAILED,
		"Failed validation layers not supported"
	);
#endif

	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = title.c_str();
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = title.c_str();
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = GetRequiredExtensions();

#ifndef NDEBUG
	extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

	createInfo.enabledExtensionCount = static_cast<MsInt32>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

#ifdef NDEBUG
	createInfo.enabledLayerCount = 0;
	createInfo.pNext = nullptr;
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

	createInfo.enabledLayerCount = static_cast<MsUInt32>(ActiveValidationLayers.size());
	createInfo.ppEnabledLayerNames = ActiveValidationLayers.data();
	createInfo.pNext = &mDebugUtilsMessageCreateInfoExt;
#endif

	MESON_TRACE_IF(
		vkCreateInstance(&createInfo, nullptr, &mInstance) != VkResult::VK_SUCCESS,
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

	mpSurface = new CVulkanSurface(pWindow, mInstance); // dont use raw vulkan types.. wrap them!
	mpPhysicalDevice = new CVulkanPhysicalDevice(mInstance, mpSurface->Surface()); // dont use raw vulkan types.. wrap them!
	mpLogicalDevice = new CVulkanLogicalDevice(mpPhysicalDevice->Device()); // dont use raw vulkan types.. wrap them!
}

Meson::Vulkan::CVulkanInstance::~CVulkanInstance() {
	delete mpLogicalDevice;
	delete mpPhysicalDevice;
	delete mpSurface;

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

	for (const auto* pLayerName : ActiveValidationLayers) {
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
