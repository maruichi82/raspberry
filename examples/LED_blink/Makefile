CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

CFLAGS =  -mfloat-abi=soft -mlittle-endian
CFLAGS += -nostdinc -fno-builtin
CFLAGS += -O2

STARTUP= startup.o
OBJS= main.o

all: kernel.img

kernel.elf: $(STARTUP) $(OBJS)
	$(LD) -static -nostdlib -T kernel.lds $^ `$(CC) -print-libgcc-file-name` -o $@

.SUFFIXES: .elf .img

.elf.img:
	$(OBJCOPY) -O binary $< $@
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
.S.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -f *.o *.img *.elf