#pragma once

#include "Glfw/GlfwWindow.h"

#include "Vulkan/VulkanInstance.h"
#include "Vulkan/VulkanValidationLayer.h"

#include <vulkan/vulkan.h>

#include <glfw/glfw3.h>

int main(INT argc, CHAR** argv);

namespace Meson {
	class CApplication {
		friend int ::main(INT argc, CHAR** argv);

	public:
		CApplication(INT width, INT height, const CHAR* title);

		virtual ~CApplication();

	public:
		void Run();

	private:
		GLFWwindow* mpGlfwWindow = nullptr;
		VkInstance mpVulkanInstance = nullptr;
	};
}