#pragma once

#include "../Core.h"
#include "../Types.h"

#include <glfw/glfw3.h>

namespace Meson::Glfw {
	class CWindow final {
	public:
		CWindow(MsUInt32 width, MsUInt32 height, const std::string& title);
		~CWindow();

	public:
		inline auto* Ptr() const { return mpWindow; }

	private:
		GLFWwindow* mpWindow;
	};
}