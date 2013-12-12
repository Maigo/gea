#ifndef __GEA_INPUT_WIN32_H__
#define __GEA_INPUT_WIN32_H__

#include <gea/engine/system/platform.h>
#include <gea/engine/system/window.h>

#include <gea/engine/core/idstring.h>

#include <map>
#include <string>

namespace gea {

// low level device system to enable support for multiple inpud devices

class HIDDevice {
public:
    inline const std::string& getName() const { return m_name; }
    inline const idstring& getID() const { return m_id; }

    inline bool active() const { return m_active; }
    inline void activate(bool active) { m_active = active; }

private:
    const std::string  m_name;
    const idstring m_id;

    bool m_active;

    // win32 specific
    HANDLE m_hdev;
};

class HIDDeviceManager : public message_extension {
public:
    virtual ~HIDDeviceManager() {}
    virtual LRESULT interpret_message(LPMSG msg) {
        return wndproc( msg->hwnd, msg->message, msg->wParam, msg->lParam );
    }

    void init();
    bool updateDeviceList();

private:
    bool registerDevices();


    LRESULT wndproc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam);

private:

    typedef std::map<idstring, HIDDevice*> Devices;
    Devices m_devices;
};

class HIDKeyboard : public HIDDevice {
public:
    static inline const RAWINPUTDEVICE& rawInputDevice() { return s_rid; }
private:
    static const RAWINPUTDEVICE s_rid;
};

class HIDMouse : public HIDDevice {
public:
    static inline const RAWINPUTDEVICE& rawInputDevice() { return s_rid; }
private:
    static const RAWINPUTDEVICE s_rid;
};

} // namespace gea //

#endif // __GEA_INPUT_WIN32_H__ //
