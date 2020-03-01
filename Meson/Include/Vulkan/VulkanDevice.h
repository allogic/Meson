#pragma once

#include "../Types.h"
#include "../Core.h"
#include "../ResultCodes.h"

#include "VulkanInstance.h"
#include "VulkanSurface.h"
#include "VulkanQueueFamilies.h"

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
		CVulkanQueueFamilies GetQueueFamilies(const VkPhysicalDevice& device);

	private:
		const CVulkanInstance& mInstance;
		const CVulkanSurface& mSurface;

		std::vector<VkPhysicalDevice> mPhysicalDevices;

		CVulkanQueueFamilies mQueueFamilies;
		VkPhysicalDevice mPhysicalDevice;

		VkDevice mDevice;
		VkQueue mQueue;
	};
}