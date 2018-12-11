#include <system.h>

const char* SOUND_ON_MESSAGE = "Press S to play.";

void main()
{
	gdt_install();
    	idt_install();
	isrs_install();
	irq_install();
	init_video();
	timer_install();
	keyboard_install();
	show_message(SOUND_ON_MESSAGE);
    	asm volatile("sti");


	
	for (;;);
}
