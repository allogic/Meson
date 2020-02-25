#pragma once

#include "Types.h"
#include "Core.h"
#include "ResultCodes.h"

#include "Glfw/GlfwWindow.h"
#include "Vulkan/VulkanInstance.h"

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
	};
}