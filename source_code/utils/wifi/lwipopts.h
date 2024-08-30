#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

// Generally you would define your own explicit list of lwIP options
// (see https://www.nongnu.org/lwip/2_1_x/group__lwip__opts.html)
//
// This example uses a common include to avoid repetition
#include "lwipopts_examples_common.h"

//#define LWIP_DHCP                   0   // turn off dhcp

//#define CYW43_DEFAULT_IP_STA_ADDRESS LWIP_MAKEU32(192,168,1,2)   // set static ip 
//#define CYW43_DEFAULT_IP_STA_GATEWAY LWIP_MAKEU32(192,168,1,1)  // set static gateway

//#define CYW43_DEFAULT_IP_AP_ADDRESS LWIP_MAKEU32(192,168,1,2)   // set static ip in access point mode
//#define CYW43_DEFAULT_IP_AP_GATEWAY LWIP_MAKEU32(192,168,1,1)  // set static gateway in access point mode

#endif
