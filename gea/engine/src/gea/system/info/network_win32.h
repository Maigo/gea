#ifndef __GEA_NETWORK_WIN32_H__
#define __GEA_NETWORK_WIN32_H__

#ifdef WIN32

// STL includes
#include <vector>

// Win32 includes
#include <winsock2.h>
#include <iphlpapi.h>

namespace gea {

// ------------------------------------------------------------------------- //
// AdapterInfo                                                               //
// ------------------------------------------------------------------------- //
struct NetworkAdapter {
    // Adapter type
    static const uint32_t TYPE_OTHER     = 0x01; //  1
    static const uint32_t TYPE_ETHERNET  = 0x06; //  6
    static const uint32_t TYPE_TOKENRING = 0x09; //  9
    static const uint32_t TYPE_FDDI      = 0x0F; // 15
    static const uint32_t TYPE_PPP       = 0x17; // 23
    static const uint32_t TYPE_LOOPBACK  = 0x18; // 24
    static const uint32_t TYPE_SLIP      = 0x1C; // 28
    static const uint32_t TYPE_IEEE80211 = 0x47; // 71

    std::string name;
    std::string description;
    uint32_t    type;
};


class AdapterInfo {
public:
    AdapterInfo() {}

    void update();

    inline uint32_t size() const { return static_cast<uint32_t>(_adapters.size()); }
    inline const NetworkAdapter& adapter(uint32_t i) const { return _adapters[i]; }
    inline const NetworkAdapter& operator[](uint32_t i) const { return _adapters[i]; }

private:
    typedef std::vector<NetworkAdapter> NetworkAdapters;
    NetworkAdapters _adapters;
};

} // namespace gea //

#include "network_win32.inl"

#endif // WIN32 //

#endif // __GEA_NETWORK_WIN32_H__ //
