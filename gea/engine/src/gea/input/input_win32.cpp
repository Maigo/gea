
#include "input_win32.h"

namespace gea {

void HIDDeviceManager::init() {

    updateDeviceList();

    if (!registerDevices() ) {
        // handle
        return;
    }
}

bool addRawHIDDevice(HANDLE hdev) {

    TCHAR* buffer = NULL;
    UINT size = 0, err = 0;

    GetRawInputDeviceInfo(hdev, RIDI_DEVICENAME, NULL, &size);
    buffer = new TCHAR[size];
    GetRawInputDeviceInfo(hdev, RIDI_DEVICENAME, buffer, &size);

//    idstring id(buffer);
    delete[] buffer;

    RID_DEVICE_INFO di;
    size = sizeof(RID_DEVICE_INFO);
    err = GetRawInputDeviceInfo(hdev, RIDI_DEVICEINFO, &di, &size);

    if (err == -1) {
        // handle
        return false;
    }

    return true;
}

bool HIDDeviceManager::updateDeviceList() {

    UINT num = 0, err = 0;

    err = GetRawInputDeviceList( NULL, &num, sizeof(RAWINPUTDEVICELIST) );
    if (err == 0) {
        // handle
        return false;
    }

    RAWINPUTDEVICELIST* devicelist = new RAWINPUTDEVICELIST[num];

    err = GetRawInputDeviceList( devicelist, &num, sizeof(RAWINPUTDEVICELIST) );
    if (err != num) {
        // handle
        delete[] devicelist;
        return false;
    }

    for (UINT i=0; i<num; ++i) {
        addRawHIDDevice(devicelist[i].hDevice);
    }

    return true;
}

bool HIDDeviceManager::registerDevices() {

    RAWINPUTDEVICE rid[2];
    rid[0] = HIDKeyboard::rawInputDevice();
    rid[1] = HIDMouse::rawInputDevice();

    return RegisterRawInputDevices( rid, 2, sizeof(RAWINPUTDEVICE) ) != 0;
};


LRESULT HIDDeviceManager::wndproc(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam) {
    switch (umsg) {
    case WM_INPUT: {

    
        break; }
    case WM_INPUT_DEVICE_CHANGE: {


        break; }
    default:
        return TRUE; // fall through to default
        break;
    }

	return FALSE;                       
}


const RAWINPUTDEVICE HIDKeyboard::s_rid = { 0x01, 0x06 , RIDEV_INPUTSINK | RIDEV_DEVNOTIFY, NULL};

const RAWINPUTDEVICE HIDMouse::s_rid = { 0x01, 0x02 , RIDEV_INPUTSINK | RIDEV_DEVNOTIFY, NULL};

} // namespace gea //
