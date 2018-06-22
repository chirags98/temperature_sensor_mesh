################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ..\makefile.init

RM := del 

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include libraries\SSD1306Ascii\src\subdir.mk
-include libraries\SPI\src\subdir.mk
-include libraries\RF24Network\subdir.mk
-include libraries\RF24Mesh\subdir.mk
-include libraries\RF24\subdir.mk
-include libraries\OneWire\subdir.mk
-include libraries\DallasTemperature\subdir.mk
-include core\core\subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ..\makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
AR += \
C:\Users\Chirag\Documents\sloeber-workspace\Server_Temp_Node\Release\arduino.ar \

ELF += \
Server_Temp_Node.elf \

HEX += \
Server_Temp_Node.hex \


# All Target
all: Server_Temp_Node

# Tool invocations
Server_Temp_Node: $(HEX)
	@echo 'Building target: $@'
	@echo 'Printing size:'
	"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-size" -A "C:/Users/Chirag/Documents/sloeber-workspace/Server_Temp_Node/Release/Server_Temp_Node.elf"
	@echo 'Finished building target: $@'
	@echo ' '

C:\Users\Chirag\Documents\sloeber-workspace\Server_Temp_Node\Release\arduino.ar: $(AR_OBJ)
	@echo 'Starting archiver'
	"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc-ar" rcs    C:/Users/Chirag/Documents/sloeber-workspace/Server_Temp_Node/Release/arduino.ar $(AR_OBJ)
	@echo 'Finished building: $@'
	@echo ' '

Server_Temp_Node.elf: $(LINK_OBJ) $(AR)
	@echo 'Starting combiner'
	"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -Wall -Wextra -Os -g -flto -fuse-linker-plugin -Wl,--gc-sections -mmcu=atmega328p -o "C:\Users\Chirag\Documents\sloeber-workspace\Server_Temp_Node/Release/Server_Temp_Node.elf"   $(LINK_OBJ)   C:/Users/Chirag/Documents/sloeber-workspace/Server_Temp_Node/Release/arduino.ar  "-LC:\Users\Chirag\Documents\sloeber-workspace\Server_Temp_Node/Release" -lm
	@echo 'Finished building: $@'
	@echo ' '

Server_Temp_Node.hex: $(ELF)
	@echo 'Create eeprom image'
	${A.RECIPE.OBJCOPY.EEP.PATTERN}
	${A.RECIPE.OBJCOPY.HEX.PATTERN}
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(PDE_DEPS)$(C_DEPS)$(AR)$(CC_DEPS)$(AR_OBJ)$(C++_DEPS)$(LINK_OBJ)$(CXX_DEPS)$(ASM_DEPS)$(HEX)$(INO_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(ELF)$(CPP_DEPS)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ..\makefile.targets
