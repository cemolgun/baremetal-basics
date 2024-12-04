CC		= arm-none-eabi-gcc
CFLAGS	= -mcpu=cortex-m4 -mthumb -Wall -g $(addprefix -I, $(INCDIR))
LDFLAGS = -nostdlib -nostartfiles -T $(LINKERSCRIPT) -Wl,-Map=memory.map 

INCDIR	= ./inc ./inc/cmsis
SRCDIR	= ./src
BINDIR	= ./bin

LINKERSCRIPT = stm32f439zi.ld
SOURCES 	 = $(wildcard $(SRCDIR)/*.c)
ELF     	 = $(BINDIR)/program.elf
BIN     	 = $(BINDIR)/program.bin

all: flash

$(ELF): $(SOURCES)
	echo $(INC)
	$(CC) $(CFLAGS) $(INC) $(LDFLAGS) $^ -o $@

$(BIN): $(ELF)
	arm-none-eabi-objcopy -O binary $< $@ 

flash: $(BIN)
	st-flash --reset write $< 0x08000000

clean:
	rm *.i *.o *.s *.out *.elf *.map *.bin bin/* ; clear

compile_commands:
	bear -- make
