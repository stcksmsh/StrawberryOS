SRC_DIR = ./src
BUILD_DIR = ./build
HEADER_DIR = ./include

# naming the image kernel8 signals RPi4 to boot into 64_bit mode
# this could be done through config.txt, but this is easier
KERNEL_ELF = kernel8.elf
KERNEL_IMG = kernel8.img

# the prefix for all the build tools
TOOL_PREFIX = aarch64-none-elf-

# the build tools themselves
AS = ${TOOL_PREFIX}as
CC = ${TOOL_PREFIX}gcc
CXX = ${TOOL_PREFIX}g++
LD = ${TOOL_PREFIX}ld
OBJCOPY = ${TOOL_PREFIX}objcopy
OBJDUMP = ${TOOL_PREFIX}objdump

# assemmbly flags
ASFLAGS =  -Wall -Werror -O2 -ffreestanding
ASFLAGS += -nostdinc -nostdlib -nostartfiles
ASFLAGS += -ggdb -fno-common -Iinclude -mgeneral-regs-only
ASFLAGS += -mtune=cortex-a72

# C flags
GCCFLAGS =  -Wall -Werror -O2 -ffreestanding 
GCCFLAGS += -nostdinc -nostdlib -nostartfiles
GCCFLAGS += -ggdb -fno-common -Iinclude -mgeneral-regs-only
GCCFLAGS += -mtune=cortex-a72

# C++ flags
CXXFLAGS =  -Wall -Werror -O2 -ffreestanding
CXXFLAGS += -nostdlib --nostdinc -nostartfiles
CXXFLAGS += -ggdb -fno-common -Iinclude  -mgeneral-regs-only 
CXXFLAGS += -std=c++11
CXXFLAGS += -mtune=cortex-a72

# linker script and linker flags
LDSCRIPT = linker.ld
LDFLAGS = -nostdlib

# clean everything and make the image
all: clean ${KERNEL_IMG}

# remove .img, .elf and all object files
clean:
	rm -f ${KERNEL_IMG} ${KERNEL_ELF}
	rm -fr ${BUILD_DIR}

# make all cpp object files
${BUILD_DIR}/%.o: ${SRC_DIR}/%.cpp makefile | ${BUILD_DIR}
	@mkdir -p $(dir ${@})
	${CXX} -c $(CXXFLAGS) -MMD -o ${@} ${<}

# make all c object files
${BUILD_DIR}/%.o: ${SRC_DIR}/%.c makefile | ${BUILD_DIR}
	@mkdir -p $(dir ${@})
	${CC} -c $(GCCFLAGS) -MMD -o ${@} ${<}

# make all asm object files
${BUILD_DIR}/%.o: ${SRC_DIR}/%.S makefile | ${BUILD_DIR}
	@mkdir -p $(dir ${@})
	${CC} -c $(ASFLAGS) -MMD -o ${@} ${<} 

# make the ./build directory if needed
${BUILD_DIR}:
	mkdir ${@}

# initialised as empty
OBJ_FILES = 

# get all sources, then add their obj files to OBJ_FILES, then vpath
SOURCES_ASM = $(shell find ./src -name "*.S" -printf "%P ") # find all *.S files
OBJ_FILES += ${addprefix ${BUILD_DIR}/,${SOURCES_ASM:.S=.o}} # add %.o for each %.S file to OBJ_FILES
vpath %.S ${sort ${dir ${SOURCES_ASM}}} # if .S is missing, look for it in all subdirectories in SOURCES_ASM, sorted lexicographically

SOURCES_C = $(shell find ./src -name "*.c" -printf "%P ")
OBJ_FILES += ${addprefix ${BUILD_DIR}/,${SOURCES_C:.c=.o}}
vpath %.c ${sort ${dir ${SOURCES_C}}}

SOURCES_CPP = $(shell find ./src -name "*.cpp" -printf "%P ")
OBJ_FILES += ${addprefix ${BUILD_DIR}/,${SOURCES_CPP:.cpp=.o}}
vpath %.cpp ${sort ${dir ${SOURCES_CPP}}}

# as I used -MMD in all the builds i can get deps like this and include them
DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

# link all obj to the .elf file with the linker script
# then copy the objects to the .img file, as the .elf is not for the right architecture
${KERNEL_IMG}: ${OBJ_FILES} ${LDSCRIPT} | ${BUILD_DIR}
	@echo "${OBJ_FILES}"
	${LD} ${LDFLAGS} -T ${LDSCRIPT} -o ${KERNEL_ELF} ${OBJ_FILES}
	${OBJCOPY} ${KERNEL_ELF} -O binary ${KERNEL_IMG}

SDCard: all
	rm -rfd /media/ziltx/bootfs/* /media/ziltx/rootfs/*
	cp kernel8.img ./SDCard
	cp ./SDCard/* /media/ziltx/bootfs/
