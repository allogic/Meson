#pragma once

#include <cstdlib>
#include <array>
#include <vector>
#include <iostream>
#include <string>
#include <chrono>
#include <exception>
#include <optional>

#define MESON_TRACE(MSG) std::cout << __FILE__ << ':' << __LINE__ << ' ' << MSG << std::endl;
#define MESON_TRACE_IF(EXPR, MSG) if (EXPR) { MESON_TRACE(MSG); }
#define MESON_TRACE_IF_RETURN(EXPR, MSG, RESULT_CODE) { if (EXPR) { MESON_TRACE(MSG); return RESULT_CODE; } }

#define MESON_MEASURE_BEGIN(NAME) auto NAME##_measure = std::chrono::high_resolution_clock::now();
#define MESON_MEASURE_END(NAME) std::cout << #NAME": " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - NAME##_measure).count() << "ms" << std::endl;