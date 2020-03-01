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
		mQueueFamily = GetQueueFamilies(device);

		if (mQueueFamily.Complete()) {
			mPhysicalDevice = device;

			return MsResult::SUCCESS;
		}
	}

	return MsResult::FAILED;
}

Meson::Vulkan::CVulkanQueueFamily Meson::Vulkan::CVulkanDevice::GetQueueFamilies(const VkPhysicalDevice& device) {
	CVulkanQueueFamily queueFamily;

	MsUInt32 familyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, nullptr);

	std::vector<VkQueueFamilyProperties> families(familyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, families.data());

	MsUInt32 i = 0;

	for (const auto& family : families) {
		if (family.queueFlags & VK_QUEUE_GRAPHICS_BIT) queueFamily.GraphicsFamily(i);

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, mSurface.Surface(), &presentSupport);

		if (presentSupport) queueFamily.PresentationFamily(i);

		if (queueFamily.Complete()) break;

		i++;
	}

	return queueFamily;
}

MsBool8 Meson::Vulkan::CVulkanDevice::GetExtensionSupport(const VkPhysicalDevice& device) {
	MsUInt32 extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, extensions.data());

	std::set<std::string> requiredExtensions(DeviceExtensions.begin(), DeviceExtensions.end());

	for (const auto& extension : extensions)
		requiredExtensions.erase(extension.extensionName);

	return requiredExtensions.empty();
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
	queueCreateInfo.queueFamilyIndex = mQueueFamily.GraphicsFamily();
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

	vkGetDeviceQueue(mDevice, mQueueFamily.GraphicsFamily(), 0, &mQueue);

	return MsResult::SUCCESS;
}