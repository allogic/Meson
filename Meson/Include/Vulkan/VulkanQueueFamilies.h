#pragma once

#include "../Types.h"
#include "../Core.h"
#include "../ResultCodes.h"

namespace Meson::Vulkan {
	class CVulkanQueueFamilies final {
	public:
		CVulkanQueueFamilies() = default;

	public:
		inline MsBool8 Complete() const {
			return
				mGraphicsFamily.has_value() &&
				mPresentationFamily.has_value();
		}

		inline void GraphicsFamily(MsUInt32 family) { mGraphicsFamily = family; }
		inline MsUInt32 GraphicsFamily() const { return mGraphicsFamily.value(); }

		inline void PresentationFamily(MsUInt32 family) { mPresentationFamily = family; }
		inline MsUInt32 PresentationFamily() const { return mPresentationFamily.value(); }

	private:
		std::optional<MsUInt32> mGraphicsFamily;
		std::optional<MsUInt32> mPresentationFamily;
	};
}