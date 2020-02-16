#include "Vulkan/VulkanInstance.h"

#include "Vulkan/VulkanValidationLayers.h"

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
	mCreateInfo.enabledLayerCount = static_cast<MsInt32>(MsVkValidationLayers.size());
	mCreateInfo.ppEnabledLayerNames = MsVkValidationLayers.data();
	mCreateInfo.pNext = &CValidationLayer::CreateMessageCreateInfo();
#endif

	MESON_TRACE_IF(
		vkCreateInstance(&createInfo, nullptr, &mpInstance) != VK_SUCCESS,
		"Failed creating vulkan instance"
	);
}

Meson::Vulkan::CInstance::~CInstance() {
	vkDestroyInstance(mpInstance, nullptr);
}