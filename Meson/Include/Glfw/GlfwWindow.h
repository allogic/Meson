#pragma once

#include "../Core.h"

#include <glfw/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <glfw/glfw3native.h>

namespace Meson::Glfw {
	class CGlfwWindow final {
	public:
		CGlfwWindow(MsUInt32 width, MsUInt32 height, const std::string& title);
		~CGlfwWindow();

	public:
		inline GLFWwindow* Window() const { return mpWindow; }
		inline const MsUInt32 Width() const { return mWidth; }
		inline const MsUInt32 Height() const { return mWidth; }
		inline const std::string& Title() const { return mTitle; }

	private:
		MsResult CreateGlfwContext();

	private:
		GLFWwindow* mpWindow;

		MsUInt32 mWidth;
		MsUInt32 mHeight;

		const std::string mTitle;
	};
}