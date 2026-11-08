# --------------------------------------------------
# Toolchain
# --------------------------------------------------

PREFIX = arm-none-eabi-

CC      = $(PREFIX)gcc
CXX     = $(PREFIX)g++
AS      = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
SIZE    = $(PREFIX)size

# --------------------------------------------------
# Project
# --------------------------------------------------

TARGET = Project

BUILD_DIR = build

SRC_DIR = src
INC_DIR = inc

# Cesta ke STM32CubeF0 – uprav podle umístění
STM32CUBE = $(HOME)/STM32/STM32CubeF0

CMSIS_INC = $(STM32CUBE)/Drivers/CMSIS/Include
DEVICE_INC = $(STM32CUBE)/Drivers/CMSIS/Device/ST/STM32F0xx/Include
LL_INC = $(STM32CUBE)/Drivers/STM32F0xx_HAL_Driver/Inc

STARTUP = $(STM32CUBE)/Drivers/CMSIS/Device/ST/STM32F0xx/Source/Templates/gcc/startup_stm32f051x8.s

SYSTEM = $(STM32CUBE)/Drivers/CMSIS/Device/ST/STM32F0xx/Source/Templates/system_stm32f0xx.c

LDSCRIPT = stm32f051r8.ld

# --------------------------------------------------
# MCU
# --------------------------------------------------

CPU = -mcpu=cortex-m0 -mthumb

DEFINES = -DSTM32F051x8

# --------------------------------------------------
# Compiler flags
# --------------------------------------------------

CFLAGS = $(CPU) \
         -std=c11 \
         -Os -g3 \
         -Wall -Wextra \
         -ffunction-sections \
         -fdata-sections \
         $(DEFINES)

CXXFLAGS = $(CPU) \
           -std=c++17 \
           -Os -g3 \
           -Wall -Wextra \
           -ffunction-sections \
           -fdata-sections \
           -fno-exceptions \
           -fno-rtti \
           $(DEFINES)

ASFLAGS = $(CPU) -g3 $(DEFINES)

INCLUDES = -Iinc \
           -I$(CMSIS_INC) \
           -I$(DEVICE_INC) \
           -I$(LL_INC)

# --------------------------------------------------
# Linker
# --------------------------------------------------

LDFLAGS = $(CPU) \
          -T$(LDSCRIPT) \
          -Wl,--gc-sections \
          -Wl,-Map=$(BUILD_DIR)/$(TARGET).map \
          --specs=nano.specs \
          --specs=nosys.specs

LDLIBS = -lm

# --------------------------------------------------
# Sources
# --------------------------------------------------

CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

C_SOURCES = $(SYSTEM)

ASM_SOURCES = $(STARTUP)

CPP_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_SOURCES))

C_OBJECTS = $(BUILD_DIR)/system_stm32f0xx.o

ASM_OBJECTS = $(BUILD_DIR)/startup_stm32f051x8.o

OBJECTS = $(CPP_OBJECTS) $(C_OBJECTS) $(ASM_OBJECTS)

# --------------------------------------------------
# Build
# --------------------------------------------------

all: $(BUILD_DIR)/$(TARGET).elf \
     $(BUILD_DIR)/$(TARGET).bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/system_stm32f0xx.o: $(SYSTEM) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/startup_stm32f051x8.o: $(STARTUP) | $(BUILD_DIR)
	$(AS) $(ASFLAGS) -x assembler-with-cpp -c $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(SIZE) $@

$(BUILD_DIR)/$(TARGET).bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

# --------------------------------------------------
# Flash
# --------------------------------------------------

flash: $(BUILD_DIR)/$(TARGET).elf
	openocd -f interface/stlink.cfg \
	        -f target/stm32f0x.cfg \
	        -c "program $< verify reset exit"

# --------------------------------------------------
# Clean
# --------------------------------------------------

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all flash clean
