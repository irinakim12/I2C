###############################################################################
# Makefile for the project at24c02_avrstudio
###############################################################################

## General Flags
PROJECT = at24c02_avrstudio
MCU = atmega128
TARGET = at24c02_avrstudio.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99       -DF_CPU=7372800UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=at24c02_avrstudio.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"D:\svn\atmega\rabbit\sw\examples\basic\at24c02_avrstudio\..\lib" 

## Objects that must be built in order to link
OBJECTS = at24c02_avrstudio.o util.o at24c02.o queue.o uart.o iic.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) at24c02_avrstudio.hex at24c02_avrstudio.eep at24c02_avrstudio.lss size

## Compile
at24c02_avrstudio.o: ../at24c02_avrstudio.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

util.o: ../../lib/util.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

at24c02.o: ../../lib/at24c02.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

queue.o: ../../lib/queue.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uart.o: ../../lib/uart.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

iic.o: ../../lib/iic.c
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

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) at24c02_avrstudio.elf dep/* at24c02_avrstudio.hex at24c02_avrstudio.eep at24c02_avrstudio.lss at24c02_avrstudio.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

