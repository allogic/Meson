#pragma once

#include "../Types.h"
#include "../Core.h"
#include "../ResultCodes.h"

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

#include <glfw/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>

namespace Meson::Vulkan {
	class CVulkanSurface final {
	public:
		CVulkanSurface(GLFWwindow* window, const VkInstance& instance);
		~CVulkanSurface();

	public:
		inline const VkSurfaceKHR& Surface() const { return mSurface; }

	private:
		const VkInstance& mInstance;

		VkSurfaceKHR mSurface;
	};
}