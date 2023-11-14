BUILD_DIR = ./build
BOOT_DIR = ./boot
HEADER_DIR = ./include

# naming the image kernel8 signals RPi4 to boot into 64_bit mode
# this could be done through config.txt, but this is easier
KERNEL_ELF = kernel8.elf
KERNEL_LST = kernel8.lst
KERNEL_IMG = kernel8.img

ARMSTUB_S = ${BOOT_DIR}/armstub8.S
ARMSTUB_BIN = ${BOOT_DIR}/armstu8.bin

# the prefix for all the build tools
TOOL_PREFIX = /usr/local/cross/bin/aarch64-elf-

# the build tools themselves
CC = ${TOOL_PREFIX}gcc
AS = ${CC}
CXX = ${TOOL_PREFIX}g++
LD = ${TOOL_PREFIX}ld
OBJCOPY = ${TOOL_PREFIX}objcopy
OBJDUMP = ${TOOL_PREFIX}objdump

# # C flags
GCCFLAGS =  -Wall -Werror -O2 -ffreestanding 
GCCFLAGS += -nostdinc -nostdlib -nostartfiles
GCCFLAGS += -ggdb -fno-common -mgeneral-regs-only
GCCFLAGS += -mtune=cortex-a72
GCCFLAGS += -isystem include

# C++ flags
CXXFLAGS =  -Wall -Werror -O2 -ffreestanding
# CXXFLAGS += -nostdlib -ggdb -fno-common 
CXXFLAGS += -std=c++11 -mtune=cortex-a72
CXXFLAGS += -isystem include

# linker script and linker flags
LDSCRIPT = boot/linker.ld
LDFLAGS = -nostdlib -entry=start -T ${LDSCRIPT}

# clean everything and make the image
all: clean ${KERNEL_IMG} ${ARMSTUB_BIN}
	@echo "Image created successfully!"
# remove .img, .elf and all object files
clean:
	@echo "Cleaning..."
	@rm -f ${KERNEL_IMG} ${KERNEL_ELF} ${KERNEL_LST}
	@rm -fr ${BUILD_DIR}

# make all cpp object files
${BUILD_DIR}/%.o: %.cpp makefile | ${BUILD_DIR}
	@mkdir -p $(dir ${@})
	@echo "CXX ${<}..."
	@${CXX} -c $(CXXFLAGS) -MMD -o ${@} ${<}

# make all c object files
${BUILD_DIR}/%.o: m%.c makefile | ${BUILD_DIR}
	@mkdir -p $(dir ${@})
	@echo "CC ${<}..."
	@${CC} -c $(GCCFLAGS) -MMD -o ${@} ${<}

# make all asm object files
${BUILD_DIR}/%.o: %.S makefile | ${BUILD_DIR}
	@mkdir -p $(dir ${@})
	@echo "AS ${<}..."
	@${AS} -c $(ASFLAGS) -MMD -o ${@} ${<} 

# make the ./build directory if needed
${BUILD_DIR}:
	@echo "Creating build directory..."
	@mkdir ${@}

# initialised as empty
OBJ_FILES = 

# get all sources, then add their obj files to OBJ_FILES, then vpath
SOURCES_ASM = $(wildcard boot/boot.S kernel/*.S lib/*.S) # find all *.S files
OBJ_FILES += ${addprefix ${BUILD_DIR}/,${SOURCES_ASM:.S=.o}} # add %.o for each %.S file to OBJ_FILES
vpath %.S ${sort ${dir ${SOURCES_ASM}}} # if .S is missing, look for it in all subdirectories in SOURCES_ASM, sorted lexicographically

SOURCES_C = $(wildcard boot/*.c kernel/*.c lib/*.c)
OBJ_FILES += ${addprefix ${BUILD_DIR}/,${SOURCES_C:.c=.o}}
vpath %.c ${sort ${dir ${SOURCES_C}}}

SOURCES_CPP = $(wildcard boot/*.cpp kernel/*.cpp lib/*.cpp)
OBJ_FILES += ${addprefix ${BUILD_DIR}/,${SOURCES_CPP:.cpp=.o}}
vpath %.cpp ${sort ${dir ${SOURCES_CPP}}}

# as I used -MMD in all the builds i can get deps like this and include them
DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

${ARMSTUB_BIN}: ${ARMSTUB_S}
	@echo "AS ${<}..."
	@${AS} ${ASFLAGS} -o ${ARMSTUB_BIN} ${ARMSTUB_S}

# link all obj to the .elf file with the linker script
# then copy the objects to the .img file, as the .elf is not for the right architecture
${KERNEL_IMG}: ${OBJ_FILES} ${LDSCRIPT} | ${BUILD_DIR}
	@echo "LD ${<}..."
	@${LD} ${LDFLAGS} -o ${KERNEL_ELF} ${OBJ_FILES}
	@${OBJDUMP} -D ${KERNEL_ELF} > ${KERNEL_LST}
	@${OBJCOPY} ${KERNEL_ELF} -O binary ${KERNEL_IMG}

SDCard: all
	@echo "Copying to directory SDCard..."
	@cp boot/config.txt ./SDCard
	@cp boot/armsutb8.bin ./SDCard
	@cp kernel8.img ./SDCard
	@echo "Copying contents of SDCard to /media/ziltx/bootfs..."
	@rm -rfd /media/ziltx/bootfs/*
	@cp ./SDCard/* /media/ziltx/bootfs/
	@echo "Unmounting /media/ziltx/bootfs and /media/ziltx/rootfs..."
	@umount /media/ziltx/bootfs && umount /media/ziltx/rootfs
	@echo "SDCard ready to be used!"
