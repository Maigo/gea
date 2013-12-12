
namespace gea {

inline uint8_t SystemPowerStatus::ac_line_status() const { return _sps.ACLineStatus; }
inline uint8_t SystemPowerStatus::battery_flags()    const { return _sps.BatteryFlag; }
inline uint8_t SystemPowerStatus::battery_percent()  const { return _sps.BatteryLifePercent; }
inline int32_t SystemPowerStatus::life_time()        const { return _sps.BatteryLifeTime; }
inline int32_t SystemPowerStatus::life_time_full()   const { return _sps.BatteryFullLifeTime; }
inline   float SystemPowerStatus::life_time_percent() const {
    return (_sps.BatteryLifeTime == BATTERY_LIFE_UNKNOWN || _sps.BatteryFullLifeTime == BATTERY_LIFE_UNKNOWN) ?
        -1.0f : (100.0f * (float) _sps.BatteryLifeTime / (float) _sps.BatteryFullLifeTime);
}

} // namespace gea //
