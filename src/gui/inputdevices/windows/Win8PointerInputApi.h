//
// Created by Georg Friedrich on 10/18/2019.
//
#pragma once

#ifdef WIN32



#include <windows.h>
#include <iostream>
#include <glib/gmessages.h>

class Win8PointerInputApi
{
#define WIN8_POINTER_INPUT_API_LIST(FUNC) \
    /* Pointer Input Functions */ \
    FUNC(GetPointerPenInfo) \
    FUNC(GetPointerPenInfoHistory) \
    FUNC(GetPointerType) \
    /* Pointer Device Functions */ \
    FUNC(GetPointerDevices) \
    /*FUNC(GetPointerDeviceProperties)*/ \
    FUNC(GetPointerDevice) \
    FUNC(GetPointerDeviceRects) \
    /*FUNC(RegisterPointerDeviceNotifications)*/ \
    /* end */

    bool m_loaded;

public:

#define DEFINE_FP_FROM_WINAPI(func) \
    public: using p ## func ## _t = std::add_pointer<decltype(func)>::type; \
    private: p ## func ## _t m_p ## func = nullptr; \
    public: const p ## func ## _t &func = m_p ## func; // const fp ref to member

WIN8_POINTER_INPUT_API_LIST(DEFINE_FP_FROM_WINAPI)

#undef DEFINE_FP_FROM_WINAPI

public:
    Win8PointerInputApi()
            : m_loaded(false)
    {
    }

    bool init() {
        if (m_loaded) {
            return true;
        }

        HINSTANCE user32 = LoadLibrary("user32");


        if (!user32)
        {
            std::cerr << "Failed to load user32.dll! This really should not happen.";
            return false;
        }

#define LOAD_AND_CHECK_FP_FROM_WINAPI(func) \
    m_p ## func = reinterpret_cast<p ## func ## _t>(GetProcAddress(user32, #func)); \
    if (!m_p ## func) { \
        g_message("Failed to load function " #func " from user32.dll"); \
        return false; \
    }

        WIN8_POINTER_INPUT_API_LIST(LOAD_AND_CHECK_FP_FROM_WINAPI)

#undef LOAD_AND_CHECK_FP_FROM_WINAPI

        g_message("Loaded Windows 8 Pointer Input API functions");
        m_loaded = true;
        return true;
    }

    bool isLoaded() {
        return m_loaded;
    }

#undef WIN8_POINTER_INPUT_API_LIST
}; // class Win8PointerInputApi


#endif