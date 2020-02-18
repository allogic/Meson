#pragma once

#include "Types.h"
#include "Core.h"
#include "ResultCodes.h"

#include "Glfw/GlfwWindow.h"
#include "Vulkan/VulkanInstance.h"

int main(MsInt32 argc, MsChar8** argv);

namespace Meson {
	class CApplication {
		friend int ::main(MsInt32 argc, MsChar8** argv);

	public:
		CApplication(MsUInt32 width, MsUInt32 height, const std::string& title);

	public:
		MsResult Run();

	private:
		std::unique_ptr<Glfw::CWindow> mpGlfwWindow = nullptr;
		std::unique_ptr<Vulkan::CInstance> mpVulkanInstance = nullptr;
	};
}