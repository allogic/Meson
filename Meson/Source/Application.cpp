#include "Application.h"

Meson::CApplication::CApplication(const SApplicationInfo& appInfo)
	: mAppInfo(appInfo) {
	MESON_TRACE_IF_RETURN(
		CreateApplicationContext() != MsResult::SUCCESS,
		"Failed creating application context"
	);
}

Meson::CApplication::~CApplication() {
	delete mpVulkanDevice;
	delete mpVulkanSurface;
	delete mpVulkanInstance;

	delete mpGlfwWindow;
}

MsResult Meson::CApplication::Run() {
	if (!mRunnable) return MsResult::FAILED;

	while (!glfwWindowShouldClose(mpGlfwWindow->Window())) {
		glfwPollEvents();
	}

	return MsResult::SUCCESS;
}

MsResult Meson::CApplication::CreateApplicationContext() {
	if (mpGlfwWindow = new Glfw::CGlfwWindow(mAppInfo.width, mAppInfo.height, mAppInfo.title); !mpGlfwWindow) return MsResult::FAILED;

	if (mpVulkanInstance = new Vulkan::CVulkanInstance(*mpGlfwWindow); !mpVulkanInstance) return MsResult::FAILED;
	if (mpVulkanSurface = new Vulkan::CVulkanSurface(*mpGlfwWindow, *mpVulkanInstance); !mpVulkanSurface) return MsResult::FAILED;
	if (mpVulkanDevice = new Vulkan::CVulkanDevice(*mpVulkanInstance, *mpVulkanSurface); !mpVulkanDevice) return MsResult::FAILED;

	mRunnable = true;

	return MsResult::SUCCESS;
}