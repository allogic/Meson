#pragma once

#include <Meson.h>

using namespace Meson;

class CSandbox : public CApplication {
public:
	CSandbox() : CApplication({ 1280, 720, "Sandbox" }) {}
};

MESON_CREATE_APP(CSandbox);