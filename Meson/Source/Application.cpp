#include "Application.h"

#include "Vulkan/VulkanValidationLayer.h"

Meson::CApplication::CApplication(MsUInt32 width, MsUInt32 height, const std::string& title) {
	MESON_TRACE_IF_RETURN(
		(mpGlfwWindow = new Glfw::CGlfwWindow(width, height, title)) == nullptr,
		"Failed creating window"
	);

	MESON_TRACE_IF_RETURN(
		(mpVulkanInstance = new Vulkan::CVulkanInstance(*mpGlfwWindow)) == nullptr,
		"Failed creating instance"
	);

	MESON_TRACE_IF_RETURN(
		(mpSurface = new Vulkan::CVulkanSurface(*mpGlfwWindow, *mpVulkanInstance)) == nullptr,
		"Faile creating surface"
	);

	MESON_TRACE_IF_RETURN(
		(mpPhysicalDevice = new Vulkan::CVulkanPhysicalDevice(*mpVulkanInstance, *mpSurface)) == nullptr,
		"Faile creating physical device"
	);

	MESON_TRACE_IF_RETURN(
		(mpLogicalDevice = new Vulkan::CVulkanLogicalDevice(*mpPhysicalDevice)) == nullptr,
		"Faile creating logical device"
	);
}

Meson::CApplication::~CApplication() {
	delete mpLogicalDevice;
	delete mpPhysicalDevice;
	delete mpSurface;
	delete mpVulkanInstance;
	delete mpGlfwWindow;
}

MsResult Meson::CApplication::Run() {
	if (
		!mpGlfwWindow ||
		!mpVulkanInstance ||
		!mpSurface ||
		!mpVulkanInstance ||
		!mpPhysicalDevice ||
		!mpLogicalDevice) return MsResult::FAILED;

	while (!glfwWindowShouldClose(mpGlfwWindow->Window())) {
		glfwPollEvents();
	}

	return MsResult::SUCCESS;
}