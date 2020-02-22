#include "Vulkan/VulkanLogicalDevice.h"

Meson::Vulkan::CVulkanLogicalDevice::CVulkanLogicalDevice(const VkPhysicalDevice& physicalDevice)
	: mPhysicalDevice(physicalDevice) {
	MESON_TRACE_IF(
		CreateLogicalDevice() != MsResult::SUCCESS,
		"Failed creating logical device"
	);
}

Meson::Vulkan::CVulkanLogicalDevice::~CVulkanLogicalDevice() {
	vkDestroyDevice(mDevice, nullptr);
}

MsResult Meson::Vulkan::CVulkanLogicalDevice::CreateLogicalDevice() {
	SQueueFamilyIndices indices = CVulkanPhysicalDevice::FindQueueFamilies(mPhysicalDevice);

	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
	queueCreateInfo.queueCount = 1;

	MsFloat32 queuePriority = 1.f;
	queueCreateInfo.pQueuePriorities = &queuePriority;

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo deviceCreateInfo{};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
	deviceCreateInfo.enabledExtensionCount = 0;

#ifdef NDEBUG
	deviceCreateInfo.enabledLayerCount = 0;
#else
	deviceCreateInfo.enabledLayerCount = static_cast<MsUInt32>(ActiveValidationLayers.size());
	deviceCreateInfo.ppEnabledLayerNames = ActiveValidationLayers.data();
#endif

	MESON_TRACE_IF_RETURN(
		vkCreateDevice(mPhysicalDevice, &deviceCreateInfo, nullptr, &mDevice) != VkResult::VK_SUCCESS,
		"Failed creating logical device",
		MsResult::FAILED
	);

	vkGetDeviceQueue(mDevice, indices.graphicsFamily.value(), 0, &mQueue);

	return MsResult::SUCCESS;
}