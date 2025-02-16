ASM = as
BIND = ld

template: template.o
	$(BIND) -brmode=any -V -eTEMPLATE -o $@ $^ > $*.bind.lst

template.o: template.s
	$(ASM) -mrent -a=$*.asm.lst -I. -o $@ $^
