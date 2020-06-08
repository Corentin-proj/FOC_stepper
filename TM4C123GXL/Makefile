#******************************************************************************
#
# Makefile - Rules for building the project.
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
# The default rule, which causes the project to be built.
#
all: ${COMPILER}
all: ${COMPILER}/main.axf

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
# Rules for building the project.
#
${COMPILER}/main.axf: ${COMPILER}/encoder.o
${COMPILER}/main.axf: ${COMPILER}/serial.o
${COMPILER}/main.axf: ${COMPILER}/stepper.o
${COMPILER}/main.axf: ${COMPILER}/FOC.o
${COMPILER}/main.axf: ${COMPILER}/main.o
${COMPILER}/main.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/main.axf: ${COMPILER}/uartstdio.o
${COMPILER}/main.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/main.axf: linker.ld
SCATTERgcc_main=linker.ld
ENTRY_main=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C123_RB1

#
# Rules for flashing the code in the TM4C123GXL
#
flash:
	@lm4flash gcc/main.bin

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
