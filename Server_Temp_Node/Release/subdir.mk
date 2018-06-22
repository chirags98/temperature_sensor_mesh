################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
INO_SRCS += \
..\Server_Temp_Node.ino 

CPP_SRCS += \
..\sloeber.ino.cpp 

LINK_OBJ += \
.\sloeber.ino.cpp.o 

INO_DEPS += \
.\Server_Temp_Node.ino.d 

CPP_DEPS += \
.\sloeber.ino.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
Server_Temp_Node.o: ..\Server_Temp_Node.ino
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=8000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\cores\arduino" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\variants\eightanaloginputs" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\libraries\DallasTemperature\3.8.0" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\libraries\OneWire\2.3.4" -I"C:\Users\Chirag\Documents\Arduino\libraries\RF24" -I"C:\Users\Chirag\Documents\Arduino\libraries\RF24\utility" -I"C:\Users\Chirag\Documents\Arduino\libraries\RF24Mesh" -I"C:\Users\Chirag\Documents\Arduino\libraries\RF24Network" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\SPI" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\SPI\src" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\libraries\SSD1306Ascii\1.0.0" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\libraries\SSD1306Ascii\1.0.0\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

sloeber.ino.cpp.o: ..\sloeber.ino.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\/arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=8000000L -DARDUINO=10802 -DARDUINO_AVR_PRO -DARDUINO_ARCH_AVR   -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\cores\arduino" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\variants\eightanaloginputs" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\libraries\DallasTemperature\3.8.0" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\libraries\OneWire\2.3.4" -I"C:\Users\Chirag\Documents\Arduino\libraries\RF24" -I"C:\Users\Chirag\Documents\Arduino\libraries\RF24\utility" -I"C:\Users\Chirag\Documents\Arduino\libraries\RF24Mesh" -I"C:\Users\Chirag\Documents\Arduino\libraries\RF24Network" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\SPI" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\packages\arduino\hardware\avr\1.6.21\libraries\SPI\src" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\libraries\SSD1306Ascii\1.0.0" -I"C:\Users\Chirag\Downloads\V4.2_win64.2017-11-20_02-16-52\sloeber\arduinoPlugin\libraries\SSD1306Ascii\1.0.0\src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


