#pragma once

#include "Types.h"
#include "Core.h"
#include "ResultCodes.h"

#include "Glfw/GlfwWindow.h"

#include "Vulkan/VulkanInstance.h"
#include "Vulkan/VulkanSurface.h"
#include "Vulkan/VulkanPhysicalDevice.h"
#include "Vulkan/VulkanLogicalDevice.h"

int main(MsInt32 argc, MsChar8** argv);

namespace Meson {
	class CApplication {
	public:
		CApplication(MsUInt32 width, MsUInt32 height, const std::string& title);
		~CApplication();

	public:
		MsResult Run();

	private:
		Glfw::CGlfwWindow* mpGlfwWindow = nullptr;

		Vulkan::CVulkanInstance* mpVulkanInstance = nullptr;
		Vulkan::CVulkanSurface* mpSurface = nullptr;
		Vulkan::CVulkanPhysicalDevice* mpPhysicalDevice = nullptr;
		Vulkan::CVulkanLogicalDevice* mpLogicalDevice = nullptr;
	};
}