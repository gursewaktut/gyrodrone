#ifndef WIFI_H
#define WIFI_H

#ifndef WIFI_AP_NAME
#define WIFI_AP_NAME "gyrodrone"
#define WIFI_AP_PASS "gyrodrone"
#define MAX_STAS 1
#endif

/*
 * set up wifi interface
 */
void wifi_setup();

/*
 * start the acesspoint to connect to the drone
 */
void start_ap();

/*
 * check if the wifi is connected
 */
int check_connection();

/*
 * start the dhcp server
 */
void start_dhcp_server();

/*
 * close wifi connection and deinit all the services
 */
void stop_wifi();

#endif
