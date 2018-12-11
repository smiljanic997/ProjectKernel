#include <system.h>

unsigned short *textmemptr;
int attrib = 0x0F; //color
int csr_x = 0, csr_y = 1;


void scroll(void)
{
	unsigned blank, temp;

	blank = 0x20 | (attrib << 8); //space, sa background color

	if(csr_y >= 25)
	{
		//pomjeri trenutni tekst unazad
		temp = csr_y - 25 + 1;
	        memcpy (textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

		//setuj zadnju liniju na blank
	        memsetw (textmemptr + (25 - temp) * 80, blank, 80);
	        csr_y = 25 - 1;
	}
}

void move_csr(void)
{
	unsigned temp;

	temp = csr_y * 80 + csr_x;

	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}

void set_csr_at_index(int row, int column)
{
	csr_x = column;
	csr_y = row;
	move_csr();
}
void get_csr_index(int *row, int *column)
{
	*column = csr_x;
	*row = csr_y;
}

void cls()
{
	unsigned blank;
	int i;

	blank = 0x20 | (attrib << 8);

	//setuje sve na blank u trenutnoj boji
	for(i = 0; i < 25; i++)
	        memsetw (textmemptr + i * 80, blank, 80);

	csr_x = 0;
	csr_y = 1;
	move_csr();
}


void putch(unsigned char c)
{
	unsigned short *where;
	unsigned att = attrib << 8;

	if(c == 0x08)
	{
	        if(csr_x != 0) csr_x--;
	}
	else if(c == 0x09)
	{
	        csr_x = (csr_x + 8) & ~(8 - 1);
	}
	else if(c == '\r')
	{
	        csr_x = 0;
	}

	else if(c == '\n')
	{
	        csr_x = 0;
	        csr_y++;
	}
    	else if(c >= ' ')
    	{
        	where = textmemptr + (csr_y * 80 + csr_x);
        	*where = c | att;	/* Character AND attributes: color */
        	csr_x++;
	}

	if(csr_x >= 80) //new line
	{
	        csr_x = 0;
	        csr_y++;
	}

	scroll();
	move_csr();
}

void putint(int n)
{
	char num[100];
	int i = 0;
	if(n == 0)
		num[i++] = '0';
	while(n)
	{
		num[i++] = n % 10 + 48;
		n /= 10;
	}
	for(int j=0; j<i/2;++j)
	{
		char tmp = num[j];
		num[j] = num[i-j-1];
		num[i-j-1] = tmp;
	}
	num[i] = '\0';
	puts(num);
}


void puts(unsigned char *text)
{
	int i;

	for (i = 0; i < strlen(text); i++)
 	       putch(text[i]);
}


void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
	attrib = (backcolor << 4) | (forecolor & 0x0F); //gornja 4 background
}


void init_video(void)
{
	textmemptr = (unsigned short *)0xB8000;
	cls();
}
