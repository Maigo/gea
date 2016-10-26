
namespace gea {

// ------------------------------------------------------------------------- //
// Platform time functions                                                   //
// ------------------------------------------------------------------------- //
// resolution scope
inline time_res_scope::time_res_scope() {
    timeGetDevCaps(&_tc, sizeof(_tc));
    timeBeginPeriod(_tc.wPeriodMin);
}
inline time_res_scope::~time_res_scope() {
    timeEndPeriod(_tc.wPeriodMin);
}

inline timestamp64_t get_system_timestamp() {
    LARGE_INTEGER timestamp;

    //HANDLE hCurThread = GetCurrentThread();
    //DWORD_PTR dwOldMask = SetThreadAffinityMask(hCurThread, 1);

    QueryPerformanceCounter(&timestamp);

    //SetThreadAffinityMask(hCurThread, dwOldMask);

    return timestamp.QuadPart;
}

inline timestamp64_t get_system_frequency() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    return frequency.QuadPart;
}

inline void system_sleep_seconds(const time32_t& t, bool interupt) {
    time_res_scope();
	SleepEx(static_cast<DWORD>(t * 1000), interupt);
}

// ------------------------------------------------------------------------- //
// Platform system functions                                                 //
// ------------------------------------------------------------------------- //
inline void system_break() {
    i_system_break();
}

} // namespace gea //
