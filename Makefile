AVRMCU = atmega8
F_CPU = 16000000
ISPPORT = /dev/ttyUSB0

SRC = main.c include/spi.c include/animation.c include/rgbhsv.c
TARGET = firmware-$(AVRMCU)
OBJDIR = bin/$(AVRMCU)

CC = avr-gcc
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size -C --mcu=$(AVRMCU)


OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

CFLAGS = -Os -Wall -Wstrict-prototypes 
CFLAGS += -fshort-enums -fpack-struct -funsigned-char -funsigned-bitfields
CFLAGS += -mmcu=$(AVRMCU) -DF_CPU=$(F_CPU)UL


all: start $(OBJDIR)/$(TARGET).hex size
	@echo "Done !"
	
start:
	@echo ":: Building for $(AVRMCU)"
	@echo ":: MCU operating frequency is $(F_CPU)Hz"
	
$(OBJDIR)/%.o : %.c
	@mkdir -p $$(dirname $@)
	$(CC) $(CFLAGS) -c $< -o $@

	
$(OBJDIR)/$(TARGET).elf : $(OBJ)
	$(CC) $(CFLAGS) $+ -o $@
	
$(OBJDIR)/$(TARGET).hex : $(OBJDIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $@


size : $(OBJDIR)/$(TARGET).elf
	@echo
	@$(SIZE) $(OBJDIR)/$(TARGET).elf
	@echo
	
clean :
	@rm -rf $(OBJDIR)
	
	
flash : all
	avrdude -c arduino \
		-p $(AVRMCU) -P $(ISPPORT) \
        -U flash:w:$(OBJDIR)/$(TARGET).hex 
