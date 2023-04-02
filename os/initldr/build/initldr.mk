##################################
##
##################################

MAKEFLAGS = -s
HEADFILE_PATH = ../include/
KRNLBOOT_PATH = ../src/
CCBUILDPATH	= $(KRNLBOOT_PATH)
include krnl_build_cmd.mh
include ldrobjs.mh

.PHONY : all everything  build_kernel
all: build_kernel

build_kernel:everything

everything : $(INITLDRIMH_OBJS) $(INITLDRKRL_OBJS) $(INITLDRSVE_OBJS)

include krnl_build_rule.mh
