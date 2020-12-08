###############################################################################
#                                                                             #
#       Copyright (c) 2018 Infineon Technologies AG. All rights reserved.     #
#                                                                             #
#                                                                             #
#                              IMPORTANT NOTICE                               #
#                                                                             #
#                                                                             #
# Infineon Technologies AG (Infineon) is supplying this file for use          #
# exclusively with Infineon’s microcontroller products. This file can be      #
# freely distributed within development tools that are supporting such        #
# microcontroller products.                                                   #
#                                                                             #
# THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED #
# OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF          #
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.#
# INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,#
# OR CONSEQUENTIAL DAMAGES, FOR	ANY REASON WHATSOEVER.                        #
#                                                                             #
###############################################################################

B_TASKING_TRICORE_PATH= C:\Program Files\TASKING\TriCore v6.3r1

B_TASKING_TRICORE_CC_OPTIONS= --core=tc1.6.2 --iso=99 --optimize=2 -g --misrac-version=2012 -N0 -Z0 -Y0

B_TASKING_TRICORE_ASM_OPTIONS= --list-format=L1 --optimize=gs

B_TASKING_TRICORE_LD_OPTIONS= -OtcxyL --core=mpe:vtc

#Include path for library directories. Add each path with following format as shown below.
#Each path prefixed with -L and separated by a space.
#B_TASKING_TRICORE_LIB_INC=-L<path>[ -L<path>][..]
B_TASKING_TRICORE_LIB_INC=
LIB_DIR = "$(B_TASKING_TRICORE_PATH)/ctc/lib/tc162"

#Libraries to include shall be listed with option -l, with following format.
#B_GNUC_TRICORE_LIBS=-l<lib name>[ -l<lib name>][..]
#B_TASKING_TRICORE_LIBS= -lrt -lcs_fpu -lfp_fpu
B_TASKING_TRICORE_LIBS= $(LIB_DIR)/librt.a $(LIB_DIR)/libc_fpu.a $(LIB_DIR)/libfp_fpu.a

