CC		= arm-none-eabi-gcc
CFLAGS	= -mcpu=cortex-m4 -mthumb -Wall
LDFLAGS = -nostdlib -T stm32f439zi.ld -Wl,-Map=memory.map 

SOURCES = program.c 
ELF     = program.elf
BIN     = program.bin

all: flash

$(ELF): $(SOURCES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

temps: $(SOURCES)
	$(CC) $(CFLAGS) -save-temps $(LDFLAGS) $^ -o $@ ; rm temps

$(BIN): $(ELF)
	arm-none-eabi-objcopy -O binary $< $@ 

flash: $(BIN)
	st-flash --reset write $< 0x08000000

clean:
	rm *.i *.o *.s *.out *.elf *.map *.bin ; clear
