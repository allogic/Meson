#pragma once

#include "../Types.h"
#include "../Core.h"
#include "../ResultCodes.h"

#include "VulkanInstance.h"
#include "VulkanSurface.h"

#include <vulkan/vulkan.h>

namespace Meson::Vulkan {
	struct SQueueFamilyIndices {
		std::optional<MsUInt32> graphicsFamily;
		std::optional<MsUInt32> presentFamily;

		inline MsBool8 Complete() const {
			return
				graphicsFamily.has_value() &&
				presentFamily.has_value();
		}
	};

	class CVulkanPhysicalDevice final {
	public:
		CVulkanPhysicalDevice(const CVulkanInstance& instance, const CVulkanSurface& surface);

	public:
		inline const VkPhysicalDevice& Device() const { return mDevice; }

	public:
		SQueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	private:
		MsResult GetPhysicalDevices();
		MsResult SelectPhysicalDevice();
		MsResult CheckQueueFamilies(VkPhysicalDevice device);

	private:
		const CVulkanInstance& mInstance;
		const CVulkanSurface& mSurface;

		std::vector<VkPhysicalDevice> mDevices;

		VkPhysicalDevice mDevice;
	};
}