#include "network_win32.h"

#ifdef WIN32

namespace gea {

// ------------------------------------------------------------------------- //
// AdapterInfo                                                               //
// ------------------------------------------------------------------------- //

void AdapterInfo::update() {
    DWORD dwRetVal = NO_ERROR;

    // get required buffer size
    ULONG outBufLen = 0u;

    dwRetVal = GetAdaptersInfo( NULL, &outBufLen );
    if ( dwRetVal != ERROR_BUFFER_OVERFLOW)
        /* do something */
        return;
    // allocate adapter info buffer
    PIP_ADAPTER_INFO pAdapterInfo = (PIP_ADAPTER_INFO) new byte[ outBufLen ]; //FIX: mem new

    // get info and process
    dwRetVal = GetAdaptersInfo( pAdapterInfo, &outBufLen );
    if( dwRetVal == ERROR_SUCCESS ) {

        PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
        struct tm newtime;
        char buffer[32];
        errno_t error;

        while (pAdapter != NULL) {
            NetworkAdapter adapter;

            printf("\tComboIndex: \t%d\n", pAdapter->ComboIndex);
            /* no need */
            adapter.name = std::string(pAdapter->AdapterName);
            printf("\tAdapter Name: \t%s\n", pAdapter->AdapterName);
            adapter.description = std::string(pAdapter->Description);
            printf("\tAdapter Desc: \t%s\n", pAdapter->Description);
            printf("\tAdapter Addr: \t");
            for (UINT i = 0; i < pAdapter->AddressLength; i++) {
                if (i == (pAdapter->AddressLength - 1))
                    printf("%.2X\n", (int) pAdapter->Address[i]);
                else
                    printf("%.2X-", (int) pAdapter->Address[i]);
            }
            printf("\tIndex: \t%d\n", pAdapter->Index);
            adapter.type = pAdapter->Type;
            printf("\tType: \t");
            switch (pAdapter->Type) {
            case MIB_IF_TYPE_OTHER:
                printf("Other\n");
                break;
            case MIB_IF_TYPE_ETHERNET:
                printf("Ethernet\n");
                break;
            case MIB_IF_TYPE_TOKENRING:
                printf("Token Ring\n");
                break;
            case MIB_IF_TYPE_FDDI:
                printf("FDDI\n");
                break;
            case MIB_IF_TYPE_PPP:
                printf("PPP\n");
                break;
            case MIB_IF_TYPE_LOOPBACK:
                printf("Lookback\n");
                break;
            case MIB_IF_TYPE_SLIP:
                printf("Slip\n");
                break;
            default:
                printf("Unknown type %ld\n", pAdapter->Type);
                break;
            }

            printf("\tIP Address: \t%s\n",
                pAdapter->IpAddressList.IpAddress.String);
            printf("\tIP Mask: \t%s\n", pAdapter->IpAddressList.IpMask.String);

            printf("\tGateway: \t%s\n", pAdapter->GatewayList.IpAddress.String);
            printf("\t***\n");

            if (pAdapter->DhcpEnabled) {
                printf("\tDHCP Enabled: Yes\n");
                printf("\t  DHCP Server: \t%s\n",
                    pAdapter->DhcpServer.IpAddress.String);

                printf("\t  Lease Obtained: ");
                /* Display local time */
                error = _localtime32_s(&newtime, (__time32_t*) &pAdapter->LeaseObtained);
                if (error)
                    printf("Invalid Argument to _localtime32_s\n");
                else {
                    // Convert to an ASCII representation 
                    error = asctime_s(buffer, 32, &newtime);
                    if (error)
                        printf("Invalid Argument to asctime_s\n");
                    else
                        /* asctime_s returns the string terminated by \n\0 */
                        printf("%s", buffer);
                }

                printf("\t  Lease Expires:  ");
                error = _localtime32_s(&newtime, (__time32_t*) &pAdapter->LeaseExpires);
                if (error)
                    printf("Invalid Argument to _localtime32_s\n");
                else {
                    // Convert to an ASCII representation 
                    error = asctime_s(buffer, 32, &newtime);
                    if (error)
                        printf("Invalid Argument to asctime_s\n");
                    else
                        /* asctime_s returns the string terminated by \n\0 */
                        printf("%s", buffer);
                }
            } else
                printf("\tDHCP Enabled: No\n");

            if (pAdapter->HaveWins) {
                printf("\tHave Wins: Yes\n");
                printf("\t  Primary Wins Server:    %s\n",
                    pAdapter->PrimaryWinsServer.IpAddress.String);
                printf("\t  Secondary Wins Server:  %s\n",
                    pAdapter->SecondaryWinsServer.IpAddress.String);
            } else
                printf("\tHave Wins: No\n");
            pAdapter = pAdapter->Next;
            printf("\n");
        }
    }
    // local tear down
    delete[] pAdapterInfo; //FIX: mem delete[]
}

} // namespace gea /

#endif // WIN32 //
