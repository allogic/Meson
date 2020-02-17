#include "Vulkan/VulkanInstance.h"

//#include "Vulkan/VulkanCallback.h"

Meson::Vulkan::CInstance::CInstance(const std::string& title) {
#ifndef NDEBUG
	MESON_TRACE_IF(
		CheckValidationLayerSupport() == false,
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

	mCreateInfo.enabledExtensionCount = static_cast<MsInt32>(extensions.size());
	mCreateInfo.ppEnabledExtensionNames = extensions.data();

#ifdef NDEBUG
	mCreateInfo.enabledLayerCount = 0;
	mCreateInfo.pNext = nullptr;
#else
	VkDebugUtilsMessengerCreateInfoEXT debugMessageCreateInfoExt;

	mCreateInfo.enabledLayerCount = static_cast<MsInt32>(ActiveValidationLayers.size());
	mCreateInfo.ppEnabledLayerNames = ActiveValidationLayers.data();
	mCreateInfo.pNext = &LinkDebugMessenger(debugMessageCreateInfoExt);
#endif

	MESON_TRACE_IF(
		vkCreateInstance(&mCreateInfo, nullptr, &mpInstance) != VK_SUCCESS,
		"Failed creating vulkan instance"
	);

#ifndef NDEBUG
	mValidationLayer.MapDebugUtilsMessengerCreateInfo(*this);
#endif
}

Meson::Vulkan::CInstance::~CInstance() {
	vkDestroyInstance(mpInstance, nullptr);
}