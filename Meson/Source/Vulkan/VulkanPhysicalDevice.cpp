#include "Vulkan/VulkanPhysicalDevice.h"

Meson::Vulkan::CVulkanPhysicalDevice::CVulkanPhysicalDevice(const VkInstance& instance)
	: mInstance(instance) {
	MESON_TRACE_IF(
		GetPhysicalDevices() != MsResult::SUCCESS,
		"Failed getting physical devices"
	);

	MESON_TRACE_IF(
		SelectPhysicalDevice() != MsResult::SUCCESS,
		"Failed physical device capability check"
	);
}

Meson::Vulkan::SQueueFamilyIndices Meson::Vulkan::CVulkanPhysicalDevice::FindQueueFamilies(VkPhysicalDevice device) {
	SQueueFamilyIndices indices;

	MsUInt32 queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	MsUInt32 i = 0;

	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			indices.graphicsFamily = i;

		if (indices.Complete()) break;

		i++;
	}

	return indices;
}

MsResult Meson::Vulkan::CVulkanPhysicalDevice::GetPhysicalDevices() {
	MsUInt32 deviceCount;
	vkEnumeratePhysicalDevices(mInstance, &deviceCount, nullptr);

	if (deviceCount == 0) return MsResult::FAILED;

	mDevices.resize(deviceCount);
	vkEnumeratePhysicalDevices(mInstance, &deviceCount, mDevices.data());

	return MsResult::SUCCESS;
}

MsResult Meson::Vulkan::CVulkanPhysicalDevice::SelectPhysicalDevice() {
	for (const auto& device : mDevices)
		if (CheckQueueFamilies(device) == MsResult::SUCCESS) {
			mDevice = device;
			return MsResult::SUCCESS;
		}

	return MsResult::FAILED;
}

MsResult Meson::Vulkan::CVulkanPhysicalDevice::CheckQueueFamilies(VkPhysicalDevice device) {
	SQueueFamilyIndices indices = FindQueueFamilies(device);

	return indices.Complete()
		? MsResult::SUCCESS
		: MsResult::FAILED;
}