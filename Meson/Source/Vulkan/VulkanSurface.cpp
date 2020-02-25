#include "Vulkan/VulkanSurface.h"

Meson::Vulkan::CVulkanSurface::CVulkanSurface(GLFWwindow* pWindow, const VkInstance& instance)
	: mInstance(instance) {
	VkWin32SurfaceCreateInfoKHR surfaceCreateInfo{};
	surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	surfaceCreateInfo.hwnd = glfwGetWin32Window(pWindow);
	surfaceCreateInfo.hinstance = GetModuleHandle(nullptr);

	MESON_TRACE_IF(
		vkCreateWin32SurfaceKHR(
			instance,
			&surfaceCreateInfo,
			nullptr,
			&mSurface) != VkResult::VK_SUCCESS,
		"Failed creating window surface"
	);
}

Meson::Vulkan::CVulkanSurface::~CVulkanSurface() {
	vkDestroySurfaceKHR(mInstance, mSurface, nullptr);
}