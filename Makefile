BUILD_DIR = build
INIT_DIR = init
LIB_DIR = lib
INCLUDE_DIR = include
KERNEL_DIR = kernel
ARMSTUB_DIR = armstub
MM_DIR = mm

KERNEL = ${BUILD_DIR}/strawberry
KERNEL_ELF = ${KERNEL}.elf
KERNEL_LST = ${KERNEL}.lst
KERNEL_IMG = ${KERNEL}.img
KERNEL_READELF = ${KERNEL}.readelf

ARMSTUB = ${ARMSTUB_DIR}/armstub8
ARMSTUB_SRC = ${ARMSTUB}.S
ARMSTUB_OBJ = ${BUILD_DIR}/${ARMSTUB}.o
ARMSTUB_ELF = ${ARMSTUB}.elf
ARMSTUB_LST = ${ARMSTUB}.lst
ARMSTUB_BIN = ${ARMSTUB}.bin

PREFIX = /usr/local/cross
TOOL_PREFIX = ${PREFIX}/bin/aarch64-elf-

CC = ${TOOL_PREFIX}gcc
AS = ${CC}
CXX = ${TOOL_PREFIX}g++
LD = ${TOOL_PREFIX}ld
OBJCOPY = ${TOOL_PREFIX}objcopy
OBJDUMP = ${TOOL_PREFIX}objdump
READELF = ${TOOL_PREFIX}readelf

# C flags
GCCFLAGS =  -Wall -Werror -O2 -nostdlib -c
GCCFLAGS += -ffreestanding -nostartfiles
GCCFLAGS += -ggdb -fno-common -mgeneral-regs-only
GCCFLAGS += -mtune=cortex-a72 -fstack-protector
GCCFLAGS += -isystem include -isystem arch/asm/include

# # C flags
# GCCFLAGS =  -Wall -Werror -O2 -nostdlib -c
# GCCFLAGS += -ffreestanding  -fno-common -g -mcpu=cortex-a72
# GCCFLAGS += -isystem ${HEADER_DIR}


# C++ flags
CXXFLAGS =  ${GCCFLAGS} -std=c++11 -fno-exceptions -fno-rtti
CXXFLAGS += -nostdinc++


# AS FLAGS
ASFLAGS = ${GCCFLAGS}

# linker script and linker flags
LDSCRIPT = linker.ld
LDFLAGS = -nostdlib -T ${LDSCRIPT}  -O2
# LDFLAGS = -T ${LDSCRIPT} -ffreestanding -O2 -nostdlib  -lgcc

CRT_PREFIX = ${PREFIX}/lib/gcc/aarch64-elf/13.2.0
CRTI = ${CRT_PREFIX}/crti.o
CRTN = ${CRT_PREFIX}/crtn.o

LINK_LIST = ${CRTI} ${OBJ_FILES} ${CRTN}

# make the image
all: clean kernel armstub
	@echo "Successfully built kernel and armstub!"

help:
	@echo "Building: 'ARCH=(arch) make... ' where (arch) is one the desired architecture, if not provided, defaults to arm64"

archlink: 
	@rm -f arch/asm
	@if [ -n "${ARCH}" ]; then \
		echo "Linking arch/asm to arch/${ARCH}/"; \
		realpath arch/${ARCH} | xargs -I{} ln -s {} arch/asm; \
		else \
		echo "ARCH is empty, defaulting to 'arm64', if this was not intended, please run 'make help'"; \
		realpath arch/arm64 | xargs -I{} ln -s {} arch/asm; \
	fi
#default target exists for testing purposes

kernel: archlink ${KERNEL_IMG}
	@echo "Kernel created successfully!"

armstub: ${ARMSTUB_BIN}
	@echo "ARMStub created successfully!"

# remove .img, .elf and all object files
clean:
	@echo "Cleaning..."find ${KERNEL_DIR} ${LIB_DIR} -name "*.S"
	@rm -fr ${BUILD_DIR}

# make all cpp object files
${BUILD_DIR}/%.o: %.cpp Makefile | ${BUILD_DIR}
	@mkdir -p $(dir ${@})
	@echo "CXX ${<}..."
	@${CXX} $(CXXFLAGS) -MMD -o ${@} ${<}

# make all c object files
${BUILD_DIR}/%.o: m%.c Makefile | ${BUILD_DIR}
	@mkdir -p $(dir ${@})
	@echo "CC ${<}..."
	@${CC} $(GCCFLAGS) -MMD -o ${@} ${<}

# make all asm object files
${BUILD_DIR}/%.o: %.S Makefile | ${BUILD_DIR}
	@mkdir -p $(dir ${@})
	@echo "AS ${<}..."
	@${AS} $(ASFLAGS) -MMD -o ${@} ${<} 

# make the ./build directory if needed
${BUILD_DIR}:
	@echo "Creating build directory..."
	@mkdir ${@}

# initialised as empty
OBJ_FILES = 

SOURCE_DIRS := ${KERNEL_DIR} ${LIB_DIR} ${MM_DIR} ${INIT_DIR}

# get all sources, then add their obj files to OBJ_FILES, then vpath
SOURCES_ASM = $(shell find ${SOURCE_DIRS} -name "*.S") # find all *.S files
OBJ_FILES += ${addprefix ${BUILD_DIR}/,${SOURCES_ASM:.S=.o}} # add %.o for each %.S file to OBJ_FILES
vpath %.S ${sort ${dir ${SOURCES_ASM}}} # if .S is missing, look for it in all subdirectories in SOURCES_ASM, sorted lexicographically

SOURCES_C = $(shell find ${SOURCE_DIRS} -name "*.c") # find all *.S files
OBJ_FILES += ${addprefix ${BUILD_DIR}/,${SOURCES_C:.c=.o}}
vpath %.c ${sort ${dir ${SOURCES_C}}}

SOURCES_CPP = $(shell find ${SOURCE_DIRS} -name "*.cpp") # find all *.S files
OBJ_FILES += ${addprefix ${BUILD_DIR}/,${SOURCES_CPP:.cpp=.o}}
vpath %.cpp ${sort ${dir ${SOURCES_CPP}}}

# as I used -MMD in all the builds i can get deps like this and include them
DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

# link all obj to the .elf file with the linker script
# then copy the objects to the .img file, as the .elf is not for the right architecture
${KERNEL_ELF}: ${OBJ_FILES} ${LDSCRIPT}
	@echo "LD ${@}..."
	@${LD} ${LDFLAGS} -o ${KERNEL_ELF} ${LINK_LIST}
	@${OBJDUMP} -D ${KERNEL_ELF} > ${KERNEL_LST}

${KERNEL_IMG}: ${KERNEL_ELF}
	@echo "OBJCOPY ${<}..."
	@${OBJCOPY} ${KERNEL_ELF} -O binary ${KERNEL_IMG}

readelf: ${KERNEL_ELF}
	@echo "READELF ${<}..."
	@${READELF} -a ${KERNEL_ELF} > ${KERNEL_READELF}
 
SDCard: all
	@echo "Copying to directory SDCard..."
	@cp ${ARMSTUB_BIN} ./SDCard
	@cp ${KERNEL_IMG} ./SDCard
	@echo "Done! You can now copy the contents of SDCard to your SD Card's bootfs partition."


${ARMSTUB_BIN}: ${ARMSTUB_ELF}
	@echo "OBJCOPY ${<}..."
	@${OBJCOPY} ${ARMSTUB_ELF} -O binary ${ARMSTUB_BIN}

${ARMSTUB_ELF}: ${ARMSTUB_OBJ}
	@echo "LD ${@}..."
	@${LD} -o ${ARMSTUB_ELF} ${ARMSTUB_OBJ}
	@${OBJDUMP} -D ${ARMSTUB_ELF} > ${ARMSTUB_LST}

${ARMSTUB_OBJ}: ${ARMSTUB_SRC} | ${BUILD_DIR}/${ARMSTUB_DIR}
	@echo "AS ${<}..."
	@${CC} ${GCCFLAGS} -o ${ARMSTUB_OBJ} ${ARMSTUB_SRC}

${BUILD_DIR}/${ARMSTUB_DIR}: ${BUILD_DIR}
	@mkdir -p ${@}

include local.mk

.PHONY: all clean kernel armstub archlink SDCard readelf