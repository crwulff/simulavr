#
#  $Id$
#
#

AVR_PROGS = toggle.elf loop.elf \
            left-unit.elf right-unit.elf \
            spi.elf \
            spi-waveforms.elf

AVRS = ../../src/verilog/

if USE_AVR_CROSS
if USE_FAB
if USE_VERILOG_TOOLS
EXAMPLE_TARGETS=$(AVR_PROGS) baretest.run loop.run spc.run spi.run
endif
endif
endif

example: $(EXAMPLE_TARGETS)

%.o: %.c
	$(AVR_GCC) -mmcu=attiny2313 -c -Os $^ -o $@

spi.o: spi.c
	$(AVR_GCC) -mmcu=atmega8 -c -Os $^ -o $@

spi.elf: spi.o
	$(AVR_GCC) -mmcu=atmega8 $^ -o $@

spi-waveforms.o: spi-waveforms.c
	$(AVR_GCC) -mmcu=atmega8 -c -Os $^ -o $@

spi-waveforms.elf: spi-waveforms.o
	$(AVR_GCC) -mmcu=atmega8 $^ -o $@

%.o: %.s
	$(AVR_GCC) -c -Wa,-gstabs -x assembler-with-cpp -o $@ $<

left-unit.elf: left-unit.o csinglepincomm.o

right-unit.elf: right-unit.o singlepincomm.o
	$(AVR_LD) -e _start $^ -o $@


%.elf: %.o
	$(AVR_GCC) -mmcu=attiny2313 $^ -o $@

%.vvp: %.v
	$(IVERILOG) $^ -s test -v -I. $(AVRS)/avr.v $(AVRS)/avr_ATtiny15.v $(AVRS)/avr_ATtiny2313.v $(AVRS)/avr_ATmega8.v -o $@ 

%.run: %.vvp $(AVR_PROGS)
	$(VVP) -M../../src -mavr $^

%.view: %.vcd %.sav
if USE_GTKWAVE
	$(GTKWAVE) -a $*.sav $*.vcd &
else
	@echo "gtkwave isn't found. Can't do that!"
endif

clean-local:
	rm -f *.vvp *~ *.o $(AVR_PROGS) *.vcd avr.vpi *.trace

#
# trace VPI with:
# $ export VPI_TRACE=log.txt
#