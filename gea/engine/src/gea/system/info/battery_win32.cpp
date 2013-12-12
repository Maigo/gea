#include "battery_win32.h"

#ifdef WIN32

namespace gea {

SystemPowerStatus::SystemPowerStatus() {
    // Wish there was a better way...
    _sps.ACLineStatus        = AC_LINE_STATUS__UNKNOWN;
    _sps.BatteryFlag         = BATTERY_FLAG__UNKNOWN;
    _sps.BatteryLifePercent  = BATTERY_PERCENT__UNKNOWN;
    _sps.BatteryLifeTime     = BATTERY_LIFE_TIME__UNKNOWN;
    _sps.BatteryFullLifeTime = BATTERY_LIFE_TIME__UNKNOWN;
}

} // namespace gea //

#endif // WIN32 //
