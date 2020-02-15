#pragma once

#include "Types.h"
#include "Core.h"

namespace Meson::Utils {
	template<typename TFunc>
	constexpr static auto Declare(TFunc&& func) { return func(); }
}