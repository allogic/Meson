#pragma once

#include "../Core.h"

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#include "../Glfw/GlfwWindow.h"

#include "VulkanInstance.h"

namespace Meson::Vulkan {
	class CVulkanSurface final {
	public:
		CVulkanSurface(const Glfw::CGlfwWindow& window, const CVulkanInstance& instance);
		~CVulkanSurface();

	public:
		inline const VkSurfaceKHR& Surface() const { return mSurface; }

	private:
		const CVulkanInstance& mInstance;

		VkSurfaceKHR mSurface;
	};
}