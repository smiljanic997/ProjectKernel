#include <system.h>


int timer_ticks = 0;

unsigned int second;
unsigned int minute;
unsigned int hour;

char* s_second[3], s_minute[3], s_hour[3];



void timer_handler(struct regs *r)
{
    	timer_ticks++;
    	if (timer_ticks % 18 == 0 || timer_ticks == 1)
    	{
		int x, y;
		get_csr_index(&x,&y);
		set_csr_at_index(0,0);
 		second = get_second();
            	minute = get_minute();
            	hour = get_hour();

	 	second = (second & 0x0F) + ((second / 16) * 10);
            	minute = (minute & 0x0F) + ((minute / 16) * 10);
            	hour = ( (hour & 0x0F) + (((hour & 0x70) / 16) * 10) ) | (hour & 0x80);
		itoa(second, s_second, 10); len_check(s_second);
		itoa(minute, s_minute, 10); len_check(s_minute);
		itoa(hour+2, s_hour, 10); len_check(s_hour);

		settextcolor('3', '0');
		puts(s_hour);putch(':');puts(s_minute);putch(':');puts(s_second);
		set_csr_at_index(x,y);
	}
}

void timer_wait(unsigned int ticks)
{
	unsigned int count, elapsed;

	elapsed = 0;
 
        while (elapsed < ticks)
        {
                count = timer_ticks;
 
		asm("sti"); // omogucuje prekide
		asm("hlt"); // zaustavit' do sledeceg interapta
 			
                elapsed += (timer_ticks - count)*1000;  // /f
        }

}


/*void timer_wait(int ticks)
{
	int start_timer = timer_ticks;
	while(timer_ticks < start_timer+ticks);

}*/

unsigned int time_at_start;
void stopwatch_start()
{
	time_at_start = timer_ticks;
}

unsigned int stopwatch_stop()
{
	unsigned int seconds_elapsed;
	return (seconds_elapsed = (timer_ticks - time_at_start) / 18);
}

void timer_install()
{
	irq_install_handler(0, timer_handler);
}
