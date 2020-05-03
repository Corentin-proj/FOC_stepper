#******************************************************************************
#
# Makefile - Rules for building the FOC_toolchain project.
#
#For the TM4C123GXL
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=TM4C123GH6PM

#
# The base directory for TivaWare.
#
ROOT=tivaware

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
VPATH=${ROOT}/utils

#
# Where to find header files that do not live in the source directory.
#
IPATH=${ROOT}

#
# The default rule, which causes the FOC_toolchain project to be built.
#
all: ${COMPILER}
all: ${COMPILER}/FOC_toolchain.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the FOC_toolchain project.
#
${COMPILER}/FOC_toolchain.axf: ${COMPILER}/spwm.o
${COMPILER}/FOC_toolchain.axf: ${COMPILER}/encoder.o
${COMPILER}/FOC_toolchain.axf: ${COMPILER}/trigo.o
${COMPILER}/FOC_toolchain.axf: ${COMPILER}/FOC_toolchain.o
${COMPILER}/FOC_toolchain.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/FOC_toolchain.axf: ${COMPILER}/uartstdio.o
${COMPILER}/FOC_toolchain.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/FOC_toolchain.axf: linker.ld
SCATTERgcc_FOC_toolchain=linker.ld
ENTRY_FOC_toolchain=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C123_RB1

#
# Rules for flashing the code in the TM4C123GXL
#
flash:
	@./lm4flash gcc/FOC_toolchain.bin

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
