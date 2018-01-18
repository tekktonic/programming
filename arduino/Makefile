CFLAGS = -mmcu=atmega328p

hello: hello.c
	avr-gcc $(CFLAGS) hello.c -o hello.elf
	avr-objcopy -O ihex hello.elf hello.hex

flash:
	sudo avrdude -c arduino -p atmega328p -P /dev/ttyACM1 -U flash:w:hello.hex
