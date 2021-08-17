#include <rtems.h>
#include <bsp.h>
#include <rtems/bsd/bsd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <machine/rtems-bsd-commands.h>
#include <sysexits.h>
#include <rtems/shell.h>

rtems_task Init(rtems_task_argument ignored)
{
    
    int exit_code;
    char const * ip = "164.54.8.169";
    char const * gateway = "164.54.8.1";
    char const * ifname = "tsec2";
    char const * netmask = "255.255.252.0";

    int sc = rtems_bsd_initialize();
    assert(sc == RTEMS_SUCCESSFUL);

#if 0
    printf("ipaddr = %s\n", bsp_uboot_getenv("ipaddr"));
    printf("gatewayip = %s\n", bsp_uboot_getenv("gatewayip"));
    printf("netmask = %s\n", bsp_uboot_getenv("netmask"));
#endif

    rtems_bsd_setlogpriority("debug");

    rtems_bsd_ifconfig_lo0();
    
    char const * ifcfg[] = {
	"ifconfig", ifname,
	"inet", ip,
	"netmask", netmask,
	NULL
    };
    exit_code = rtems_bsd_ifconfig(ifname, ip, netmask, gateway);
    if (exit_code != EX_OK) {
	perror("rtems_bsd_command_ifconfig() failed to set up network.");
    }

#if 0
    char const * dflt_route[] = {
	"route", "add",
	"-host", gateway,
	"-iface", ifname,
	NULL
    };


    char const * dflt_route2[] = {
	"route", "add", "default", gateway, NULL
    };

    exit_code = rtems_bsd_command_route(RTEMS_BSD_ARGC(dflt_route), dflt_route);
    if (exit_code != EX_OK) {
	perror("rtems_bsd_command_route failed to set up static route to gw.");
    }
	
    exit_code = rtems_bsd_command_route(RTEMS_BSD_ARGC(dflt_route2), dflt_route2);
    if (exit_code != EX_OK) {
	perror("rtems_bsd_command_route failed to set up default route.");
    }
#endif
    
    const char* ifconfg_args[] = {
	"ifconfig", NULL
    };
    const char* netstat_args[] = {
	"netstat", "-rn", NULL
    };

    
    printf("-------------- IFCONFIG -----------------\n");
    rtems_bsd_command_ifconfig(1, (char**) ifconfg_args);
    printf("-------------- NETSTAT ------------------\n");
    rtems_bsd_command_netstat(2, (char**) netstat_args);
    
    // Start an rtems shell before main, for debugging RTEMS system issues
    rtems_shell_init("SHLL", RTEMS_MINIMUM_STACK_SIZE * 4,
                     100, "/dev/console",
                     false, true,
                     NULL);
    exit(0);
}
