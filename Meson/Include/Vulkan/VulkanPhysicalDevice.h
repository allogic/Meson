#pragma once

#include "../Types.h"
#include "../Core.h"
#include "../ResultCodes.h"

#include <vulkan/vulkan.h>

namespace Meson::Vulkan {
	struct SQueueFamilyIndices {
		std::optional<MsUInt32> graphicsFamily;

		inline bool Complete() const { return graphicsFamily.has_value(); }
	};

	class CVulkanPhysicalDevice final {
	public:
		CVulkanPhysicalDevice(const VkInstance& instance);

	public:
		inline const VkPhysicalDevice& Device() const { return mDevice; }

	public:
		static SQueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	private:
		MsResult GetPhysicalDevices();
		MsResult SelectPhysicalDevice();
		MsResult CheckQueueFamilies(VkPhysicalDevice device);

	private:
		const VkInstance& mInstance;

		std::vector<VkPhysicalDevice> mDevices;

		VkPhysicalDevice mDevice;
	};
}