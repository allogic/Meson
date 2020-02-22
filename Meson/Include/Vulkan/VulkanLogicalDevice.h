#pragma once

#include "../Types.h"
#include "../Core.h"
#include "../ResultCodes.h"

#include "VulkanPhysicalDevice.h"

#ifndef NDEBUG
#include "VulkanValidationLayers.h"
#endif

#include <vulkan/vulkan.h>

namespace Meson::Vulkan {
	class CVulkanLogicalDevice final {
	public:
		CVulkanLogicalDevice(const VkPhysicalDevice& physicalDevice);
		~CVulkanLogicalDevice();

	private:
		MsResult CreateLogicalDevice();

	private:
		const VkPhysicalDevice& mPhysicalDevice;

		VkDevice mDevice;
		VkQueue mQueue;
	};
}