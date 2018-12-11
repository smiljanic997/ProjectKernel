#include <system.h>

const char* BUTTON_PRESSED_MESSAGE = "Play button pressed.";

int notes[66] = {440, 440, 440, 349, 523, 440, 349, 523, 440, 659, 659, 659, 698, 523, 415, 349, 523, 440, 880, 440, 440, 880, 830, 784, 740, 698, 740, 455, 622, 587, 554, 523, 466, 523, 349, 415, 349, 440, 523, 440, 523, 659, 880, 440, 440, 880, 830, 784, 740, 698, 740, 455, 622, 587, 554, 523, 466, 523, 349,415, 349,  523, 440, 349, 261, 440};
int delay[66] = {5000, 5000, 5000, 3500, 1500, 5000, 3500, 1500, 10000, 5000, 5000, 5000, 3500, 1500, 5000, 3500, 1500, 10000, 5000, 3500, 1500, 5000, 2500, 2500, 1250, 1250, 2500, 2500, 5000, 2500, 2500, 1250, 1250, 2500, 1250, 5000, 3750, 1250, 5000, 3750, 1250, 10000, 5000, 3500, 1500, 5000, 2500, 2500, 1250, 1250, 2500 , 2500, 5000, 2500 ,2500, 1250, 1250, 2500, 2500, 5000, 3750, 1250, 5000, 3750, 1250, 10000};

void set_sound()
{
	int counter;
	outportb(0x61, inportb(0x61) | 3); // enable speaker
	outportb(0x43, 0xb6);
	// program PIT
	for (int i=0; i<65; i++) 
	{
		counter = (0x1234DD / notes[i]); // calculate frequency 
		outportb(0x42, counter && 0xff); // LSB
		outportb(0x42, counter >> 8); // MSB
		timer_wait(delay[i]);
	}
	turn_off();	
}

void turn_off()
{
	outportb(0x61, 0);
}

void play(char c)
{
	unsigned int seconds_elapsed;
	if(c == 's')
	{
		show_message(BUTTON_PRESSED_MESSAGE);
		stopwatch_start();
		set_sound();
		seconds_elapsed = stopwatch_stop();
		puts("Track ended. Duration: "); putint(seconds_elapsed);puts(" seconds."); putch('\n');
	}
}


