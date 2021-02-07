OPENOCD_DIR	= C:/Program Files (x86)/openocd
OPENOCD_IFACE = stlink-v2.cfg
OPENOCD_TARGET = stm32f1x_stlink.cfg

OPENCM3_DIR = lib/libopencm3

LDSCRIPT = ./lib/libopencm3/lib/stm32/f1/stm32f103x8.ld

BINARY = scanner

OBJS = $(addprefix lib/scpi-parser/libscpi/src/, error.o fifo.o ieee488.o minimal.o parser.o units.o utils.o lexer.o expression.o )

OBJS += \
	src/main.o \
	src/commands.o \
	src/switching.o \
	src/timing.o \
	src/serial.o \
	src/utils.o

LDFLAGS += \
	 -Xlinker -Map=scanner.map

CFLAGS = -std=c11 -Os
CPPFLAGS = \
	-fdiagnostics-color=always \
	-Ilib/scpi-parser/libscpi/inc

include Makefile.include

all: bin
	$(PREFIX)-size $(BINARY).elf

openocd:
	"`wslpath '$(OPENOCD_DIR)/bin/openocd.exe'`" -f "$(OPENOCD_DIR)/share/openocd/scripts/interface/$(OPENOCD_IFACE)" -f "$(OPENOCD_DIR)/share/openocd/scripts/target/$(OPENOCD_TARGET)"

program:
	"`wslpath '$(OPENOCD_DIR)/bin/openocd.exe'`" -f "$(OPENOCD_DIR)/share/openocd/scripts/interface/$(OPENOCD_IFACE)" -f "$(OPENOCD_DIR)/share/openocd/scripts/target/$(OPENOCD_TARGET)" -c "program $(BINARY).elf verify reset exit"

