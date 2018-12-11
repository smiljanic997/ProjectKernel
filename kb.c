#include <system.h>


unsigned char keys[128] = { 0, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 's', 0, 0, 0, 0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


void keyboard_handler(struct regs *r)
{
	unsigned char scancode;

	scancode = inportb(0x60);
	if (scancode & 0x80) //ako je prvi bit setovan, tada je dugme just been released
	{
	}
	else
	{
        	play(keys[scancode]);
    	}
}


void keyboard_install()
{
	irq_install_handler(1, keyboard_handler);
}
