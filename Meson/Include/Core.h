#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <chrono>
#include <exception>

#define MESON_TRACE(MSG) std::cout << __FILE__ << ':' << __LINE__ << ' ' << MSG << std::endl;

#define MESON_MEASURE_BEGIN(NAME) auto NAME##_measure = std::chrono::high_resolution_clock::now();
#define MESON_MEASURE_END(NAME) std::cout << #NAME": " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - NAME##_measure).count() << "ms" << std::endl;