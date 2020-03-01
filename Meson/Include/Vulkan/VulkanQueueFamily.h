#pragma once

#include "../Core.h"

namespace Meson::Vulkan {
	class CVulkanQueueFamily final {
	public:
		CVulkanQueueFamily() = default;

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