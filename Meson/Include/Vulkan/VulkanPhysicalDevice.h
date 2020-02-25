#pragma once

#include "../Types.h"
#include "../Core.h"
#include "../ResultCodes.h"

#include <vulkan/vulkan.h>

namespace Meson::Vulkan {
	struct SQueueFamilyIndices {
		std::optional<MsUInt32> graphicsFamily;
		std::optional<MsUInt32> presentFamily;

		inline bool Complete() const {
			return
				graphicsFamily.has_value() &&
				presentFamily.has_value();
		}
	};

	class CVulkanPhysicalDevice final {
	public:
		CVulkanPhysicalDevice(const VkInstance& instance, const VkSurfaceKHR& surface);

	public:
		inline const VkPhysicalDevice& Device() const { return mDevice; }

	public:
		SQueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

	private:
		MsResult GetPhysicalDevices();
		MsResult SelectPhysicalDevice();
		MsResult CheckQueueFamilies(VkPhysicalDevice device);

	private:
		const VkInstance& mInstance;
		const VkSurfaceKHR& mSurface;

		std::vector<VkPhysicalDevice> mDevices;

		VkPhysicalDevice mDevice;
	};
}