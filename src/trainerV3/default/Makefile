###############################################################################
# Makefile for the project lab7
###############################################################################

## General Flags
PROJECT = lab7
MCU = atmega8535
TARGET = lab7.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99           -DF_CPU=4000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=lab7.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"C:\Users\Professional\Desktop\BmstuMkCourseWork\src\trainerV3\..\..\..\..\..\..\..\WinAVR-20100110" 

## Objects that must be built in order to link
OBJECTS = main.o keyboard.o uart.o display.o leds.o buzzer.o timers.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) lab7.hex lab7.eep lab7.lss## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

keyboard.o: ../keyboard.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

display.o: ../display.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

leds.o: ../leds.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

buzzer.o: ../buzzer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timers.o: ../timers.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) lab7.elf dep/* lab7.hex lab7.eep lab7.lss lab7.map


## Other dependencies
-include $(shell mkdir dep 2>NUL) $(wildcard dep/*)

