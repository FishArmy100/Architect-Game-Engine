#pragma once

// ------------------ Registration Friend ------------------
static void rttr_auto_register_reflection_function_();
#define REFLIB_FRIEND friend void ::rttr_auto_register_reflection_function_();