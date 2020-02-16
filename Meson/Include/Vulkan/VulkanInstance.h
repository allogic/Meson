#pragma once

#include "../Core.h"
#include "../Types.h"

#include <vulkan/vulkan.h>

#include <glfw/glfw3.h>

namespace Meson::Vulkan {
	class CInstance final {
	public:
		CInstance(const std::string& title);

		~CInstance();

	public:
		inline auto* Ptr() const { return mpInstance; }

	private:
		VkApplicationInfo mAppInfo;
		VkInstanceCreateInfo mCreateInfo;

		VkInstance mpInstance;
	};
}