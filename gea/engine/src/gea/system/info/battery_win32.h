#ifndef __GEA_BATTERY_WIN32_H__
#define __GEA_BATTERY_WIN32_H__

#ifdef WIN32

// Win32 includes
#include <windows.h>

namespace gea {

class SystemPowerStatus {
public:
    // AC Line Status
    static const uint8_t AC_LINE_STATUS__OFFLINE      = 0x00;
    static const uint8_t AC_LINE_STATUS__ONLINE       = 0x01;
    static const uint8_t AC_LINE_STATUS__BACKUP_POWER = 0x02;
    static const uint8_t AC_LINE_STATUS__UNKNOWN      = 0xFF;

    // Battery Status
    static const uint8_t BATTERY_FLAG__HIGH           = 0x01;
    static const uint8_t BATTERY_FLAG__LOW            = 0x02;
    static const uint8_t BATTERY_FLAG__CRITICAL       = 0x04;
    static const uint8_t BATTERY_FLAG__CHARGING       = 0x08;
    static const uint8_t BATTERY_FLAG__NO_BATTERY     = 0x80;
    static const uint8_t BATTERY_FLAG__UNKNOWN        = 0xFF;

    // Battery Life Percent
    static const uint8_t BATTERY_PERCENT__UNKNOWN     = 0xFF;

    // Battery (Full) Life Time
    static const int32_t BATTERY_LIFE_TIME__UNKNOWN   = 0xFFFFFFFF;

    SystemPowerStatus();
    ~SystemPowerStatus() {}

    void update() {
        if ( !GetSystemPowerStatus(&_sps) )
            /* do something */
            return;
    }

    // member access
    inline uint8_t ac_line_status() const;
    inline uint8_t battery_flags() const;
    inline uint8_t battery_percent() const;
    inline int32_t life_time() const;
    inline int32_t life_time_full() const;
    inline float life_time_percent() const;

private:
    SYSTEM_POWER_STATUS _sps;
};

} // namespace gea //

#include "battery_win32.inl"

#endif // WIN32 //

#endif // __GEA_BATTERY_WIN32_H__ //
