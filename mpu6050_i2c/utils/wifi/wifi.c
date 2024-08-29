#include "pico/cyw43_arch.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "wifi.h"
#include "dhcpserver.h"

static int connected_devices = 0;
dhcp_server_t dhcp_server;

/*
 * set up wifi interface
 */
void wifi_setup() {
    if (cyw43_arch_init()) {
        printf("Failed to initialize Wi-Fi module.\n");
        return;
    }

}
/*
 * start the acesspoint to connect to the drone
 */
void start_ap() {

    // Enable Access Point mode
    cyw43_arch_enable_ap_mode(WIFI_AP_NAME, WIFI_AP_PASS, CYW43_AUTH_WPA2_AES_PSK);

    start_dhcp_server();

    while (true) {
        cyw43_arch_poll();  // Keep the network stack responsive
        sleep_ms(1000);
    }

}

/* 
 * start the dhcp server
 */ 
void start_dhcp_server() {
    // DHCP Server Start (if not started in wifi_setup)
    ip4_addr_t ipaddr, netmask, gw;
    IP4_ADDR(ip_2_ip4(&ipaddr), 192, 168, 4, 1);
    IP4_ADDR(ip_2_ip4(&netmask), 255, 255, 255, 0);
    IP4_ADDR(ip_2_ip4(&gw), 192, 168, 4, 1);
    dhcp_server_init(&dhcp_server, &ipaddr, &netmask);
}

/*
 * check if the wifi is connected
 */
int check_connection() {
    // to check the no of devices connected to the ap 
    // void cyw43_wifi_ap_get_stas (cyw43_t * self, int * num_stas, uint8_t * macs)
    return 0;
}

/*
 * close wifi connection and deinit
 */
void stop_wifi() {

    dhcp_server_deinit(&dhcp_server);
    cyw43_arch_deinit();
}
