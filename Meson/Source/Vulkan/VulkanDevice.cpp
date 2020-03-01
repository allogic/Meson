#include "Vulkan/VulkanDevice.h"

Meson::Vulkan::CVulkanDevice::CVulkanDevice(
	const CVulkanInstance& instance,
	const CVulkanSurface& surface)
	: mInstance(instance)
	, mSurface(surface) {
	MESON_TRACE_IF_RETURN(
		GetPhysicalDevices() != MsResult::SUCCESS,
		"Failed getting physical devices"
	);

	MESON_TRACE_IF_RETURN(
		SelectPhysicalDevice() != MsResult::SUCCESS,
		"Failed selecting physical device"
	);

	MESON_TRACE_IF_RETURN(
		CreateLogicalDevice() != MsResult::SUCCESS,
		"Faile creating logical device"
	);
}

Meson::Vulkan::CVulkanDevice::~CVulkanDevice() {
	vkDestroyDevice(mDevice, nullptr);
}

MsResult Meson::Vulkan::CVulkanDevice::SelectPhysicalDevice() {
	for (const auto& device : mPhysicalDevices) {
		mQueueFamilies = GetQueueFamilies(device);

		if (mQueueFamilies.Complete()) {
			mPhysicalDevice = device;

			return MsResult::SUCCESS;
		}
	}

	return MsResult::FAILED;
}

Meson::Vulkan::CVulkanQueueFamilies Meson::Vulkan::CVulkanDevice::GetQueueFamilies(const VkPhysicalDevice& device) {
	CVulkanQueueFamilies queueFamilies;

	MsUInt32 familyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, nullptr);

	std::vector<VkQueueFamilyProperties> families(familyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, families.data());

	MsUInt32 i = 0;

	for (const auto& family : families) {
		if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) queueFamilies.GraphicsFamily(i);

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, mSurface.Surface(), &presentSupport);

		if (presentSupport) queueFamilies.PresentationFamily(i);

		if (queueFamilies.Complete()) break;

		i++;
	}

	return queueFamilies;
}

MsResult Meson::Vulkan::CVulkanDevice::GetPhysicalDevices() {
	MsUInt32 deviceCount;
	vkEnumeratePhysicalDevices(mInstance.Instance(), &deviceCount, nullptr);

	if (deviceCount == 0) return MsResult::FAILED;

	mPhysicalDevices.resize(deviceCount);
	vkEnumeratePhysicalDevices(mInstance.Instance(), &deviceCount, mPhysicalDevices.data());

	return MsResult::SUCCESS;
}

MsResult Meson::Vulkan::CVulkanDevice::CreateLogicalDevice() {
	VkDeviceQueueCreateInfo queueCreateInfo{};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = mQueueFamilies.GraphicsFamily();
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

	if (IsDebugEnabled) {
		deviceCreateInfo.enabledLayerCount = 0;
	}
	else {
		deviceCreateInfo.enabledLayerCount = static_cast<MsUInt32>(ValidationLayers.size());
		deviceCreateInfo.ppEnabledLayerNames = ValidationLayers.data();
	}

	if (vkCreateDevice(
		mPhysicalDevice,
		&deviceCreateInfo,
		nullptr,
		&mDevice) != VkResult::VK_SUCCESS) {
		return MsResult::FAILED;
	}

	vkGetDeviceQueue(mDevice, mQueueFamilies.GraphicsFamily(), 0, &mQueue);

	return MsResult::SUCCESS;
}