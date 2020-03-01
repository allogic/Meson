#pragma once

#include "Types.h"
#include "Core.h"
#include "ResultCodes.h"

#include "Glfw/GlfwWindow.h"

#include "Vulkan/VulkanInstance.h"
#include "Vulkan/VulkanSurface.h"
#include "Vulkan/VulkanDevice.h"

int main(MsInt32 argc, MsChar8** argv);

namespace Meson {
	struct SApplicationInfo {
		MsUInt32 width;
		MsUInt32 height;
		std::string title;
	};

	class CApplication {
	public:
		CApplication(const SApplicationInfo& appInfo);
		~CApplication();

	public:
		MsResult Run();

	private:
		MsResult CreateApplicationContext();

	private:
		SApplicationInfo mAppInfo;

		Glfw::CGlfwWindow* mpGlfwWindow = nullptr;

		Vulkan::CVulkanInstance* mpVulkanInstance = nullptr;
		Vulkan::CVulkanSurface* mpVulkanSurface = nullptr;
		Vulkan::CVulkanDevice* mpVulkanDevice = nullptr;

		bool mRunnable = false;
	};
}