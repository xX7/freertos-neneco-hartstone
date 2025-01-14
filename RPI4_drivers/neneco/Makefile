CROSS ?= aarch64-none-elf-
CFLAGS = -mcpu=cortex-a72 \
         -fpic \
         -static\
         -ffreestanding \
         -std=gnu99 \
         -O1 \
         -Wall \
         -Wextra \
         -DGUEST \
         -I$(INCLUDEPATH1) \
         -I$(INCLUDEPATH2) \
         -I$(INCLUDEPATH3) \
         -I$(INCLUDEPATH4) \
         -I$(INCLUDEPATH5) \
		 -I$(INCLUDEPATH6) 
BUILTIN_OPS = -fno-builtin-memset
ASMFLAGS = -mcpu=cortex-a72

INCLUDEPATH1 ?= ./src
INCLUDEPATH2 ?= ../musl_libc
INCLUDEPATH3 ?= ../mmu
INCLUDEPATH4 ?= ../../FreeRTOS_port/include
INCLUDEPATH5 ?= ../../FreeRTOS_port/portable/GCC/ARM_CA72_64_BIT
INCLUDEPATH6 ?= ../../hartstone/inc

BUILDPATH := ./build

# From ./src
OBJS = build/startup.o
OBJS +=build/FreeRTOS_asm_vector.o
OBJS +=build/FreeRTOS_tick_config.o
OBJS +=build/interrupt.o
OBJS +=build/main.o
OBJS +=build/mmu_cfg.o
OBJS +=build/uart.o
OBJS +=build/hartstone.o
OBJS +=build/whetstone.o
OBJS +=build/xprintf.o
OBJS +=build/spi.o
OBJS +=build/gpio.o
OBJS +=build/pwm.o
OBJS +=build/gpioclock.o
OBJS +=build/i2c.o
OBJS +=build/AD1115.o
OBJS +=build/LN298.o
OBJS +=build/ELM327.o


# From ../mmu
OBJS +=build/mmu.o

# From ../cache
OBJS +=build/cache.o

# From ../musl_libc
OBJS +=build/memset.o
OBJS +=build/memcpy.o

# From ../../FreeRTOS_port/portable/GCC/ARM_CA72_64_BIT
OBJS +=build/port.o
OBJS +=build/portASM.o

OBJS +=build/list.o
OBJS +=build/queue.o
OBJS +=build/tasks.o
OBJS +=build/timers.o

OBJS +=build/heap_4.o

all: neneco.elf

neneco.elf: src/raspberrypi4.ld $(OBJS)
	$(CROSS)gcc -Wl,--build-id=none -fcommon -std=gnu99 -O1 -T src/raspberrypi4.ld -o $@ -ffreestanding -nostdlib --specs=nosys.specs $(BUILTIN_OPS) $(OBJS)
	$(CROSS)objdump -d neneco.elf > neneco.list

$(OBJS): | $(BUILDPATH)

$(BUILDPATH): 
	mkdir -p $(BUILDPATH)

build/%.o : src/%.S
	$(CROSS)as $(ASMFLAGS) -c -o $@ $<
	
build/%.o : src/%.c
	$(CROSS)gcc $(CFLAGS) -fcommon -c -o $@ $<

build/%.o : ../mmu/%.c
	$(CROSS)gcc $(CFLAGS) -fcommon -c -o $@ $<

build/%.o : ../cache/%.S
	$(CROSS)gcc $(CFLAGS) -fcommon -c -o $@ $<

build/%.o : ../musl_libc/%.c
	$(CROSS)gcc $(CFLAGS) -fcommon -c -o $@ $<

build/%.o : ../../FreeRTOS_port/%.c
	$(CROSS)gcc $(CFLAGS) -fcommon -c -o $@ $<

build/%.o : ../../FreeRTOS_port/portable/GCC/ARM_CA72_64_BIT/%.c
	$(CROSS)gcc $(CFLAGS) -fcommon -c -o $@ $<

build/%.o : ../../FreeRTOS_port/portable/GCC/ARM_CA72_64_BIT/%.S
	$(CROSS)as $(ASMFLAGS) -c -o $@ $<

build/%.o : ../../FreeRTOS_port/portable/MemMang/%.c
	$(CROSS)gcc $(CFLAGS) -fcommon -c -o $@ $<

build/%.o : ../../hartstone/%.c
	$(CROSS)gcc $(CFLAGS) -fcommon -c -o $@ $<

clean :
	rm -f build/*.o
	rm -f *.elf
	rm -f *.list

.PHONY: all clean
