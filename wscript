# Hello World WAF Script

from __future__ import print_function
rtems_version = "5"

try:
    import rtems_waf.rtems as rtems
except:
    print("error: no rtems_waf submodule")
    import sys
    sys.exit(1)

def init(ctx):
    rtems.init(ctx, version = rtems_version, long_commands = True)

def bsp_configure(conf, arch_bsp):
    # add bsp specific config tasks
    pass

def options(opt):
    rtems.options(opt)

def configure(conf):
    rtems.configure(conf, bsp_configure = bsp_configure)

def build(bld):
    rtems.build(bld)

    bld(features = "c program",
        target = "hello.exe",
        cflags = "-g -O2",
        source = ["hello.c", "init.c"]
 
