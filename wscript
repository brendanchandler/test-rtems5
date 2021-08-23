#include <rtems/bsd/bsd.h>

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

    bld(features = 'c cprogram',
        target = 'hello',
        includes = '',
	cflags = '-g',
        source = ['hello.c', 'init.c'],
        lib = ['bsd', 'm'])

    bld(rule='powerpc-rtems5-objcopy -O binary ${SRC} ${TGT}', source='hello', target='hello.bin')
    bld(rule='gzip -9 -f -c ${SRC} > ${TGT}', source='hello.bin', target="hello.bin.gz")
    bld(rule='mkimage.py -A ppc -O linux -T kernel -a 0x4000 -e 0x4000 -n RTEMS -d ${SRC} ${TGT}',
        source="hello.bin.gz", target="hello.img")

