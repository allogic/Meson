#pragma once

#include "Types.h"
#include "ResultCodes.h"

#include <vulkan/vulkan_core.h>

#include <cstdlib>
#include <array>
#include <vector>
#include <set>
#include <iostream>
#include <string>
#include <chrono>
#include <exception>
#include <optional>
#include <type_traits>

#define MESON_TRACE(MSG) std::cout << __FILE__ << ':' << __LINE__ << ' ' << MSG << std::endl;
#define MESON_TRACE_IF(EXPR, MSG) if (EXPR) { MESON_TRACE(MSG); }
#define MESON_TRACE_IF_RETURN(EXPR, MSG) if (EXPR) { MESON_TRACE(MSG); return; }
#define MESON_TRACE_IF_RETURN_RESULT(EXPR, MSG, RESULT) if (EXPR) { MESON_TRACE(MSG); return RESULT; }

#define MESON_MEASURE_BEGIN(NAME) auto NAME##_measure = std::chrono::high_resolution_clock::now();
#define MESON_MEASURE_END(NAME) std::cout << #NAME": " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - NAME##_measure).count() << "ms" << std::endl;

#ifdef NDEBUG
constexpr const MsBool8 IsDebugEnabled = false;

constexpr std::array<const MsChar8*, 0> ValidationLayers{};
constexpr std::array<const MsChar8*, 0> DeviceExtensions{};
#else
constexpr const MsBool8 IsDebugEnabled = true;

constexpr std::array<const MsChar8*, 1> ValidationLayers{
	"VK_LAYER_KHRONOS_validation",
};

constexpr std::array<const MsChar8*, 1> DeviceExtensions{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME,
};
#endif