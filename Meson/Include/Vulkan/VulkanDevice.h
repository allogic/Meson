#pragma once

#include "../Core.h"

#include "VulkanInstance.h"
#include "VulkanSurface.h"
#include "VulkanQueueFamily.h"

#include <vulkan/vulkan.h>

namespace Meson::Vulkan {
	class CVulkanDevice final {
	public:
		CVulkanDevice(const CVulkanInstance& instance, const CVulkanSurface& surface);
		~CVulkanDevice();

	private:
		MsResult GetPhysicalDevices();
		MsResult SelectPhysicalDevice();
		MsResult CreateLogicalDevice();

	private:
		CVulkanQueueFamily GetQueueFamilies(const VkPhysicalDevice& device);
		MsBool8 GetExtensionSupport(const VkPhysicalDevice& device);

	private:
		const CVulkanInstance& mInstance;
		const CVulkanSurface& mSurface;

		std::vector<VkPhysicalDevice> mPhysicalDevices;

		CVulkanQueueFamily mQueueFamily;
		VkPhysicalDevice mPhysicalDevice;

		VkDevice mDevice;
		VkQueue mQueue;
	};
}