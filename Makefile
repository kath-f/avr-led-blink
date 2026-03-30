#device specific settings, you might want to change it on your side
MCU = atmega328p
PROGRAMMER = arduino
BAUD_RATE = 115200
CLOCK_RATE = 16000000UL
PORT = /dev/ttyACM0

default:
	avr-gcc -mmcu=$(MCU) -DF_CPU=$(CLOCK_RATE) -Os -Wall *.c -o led_blink.elf
	avr-objcopy -O ihex led_blink.elf led_blink.hex
	avrdude -p $(MCU) -c $(PROGRAMMER) -b $(BAUD_RATE) -P $(PORT) -U flash:w:led_blink.hex:i
