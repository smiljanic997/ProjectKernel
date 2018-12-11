#include <system.h>
#define NULL 0


char* strcpy(char *d, char *s)
{
	char *saved = d;
	while ((*d++ = *s++) != '\0');
	return saved;
}

char* itoa (int value, char *result, int base)
{
	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	int tmp_value;

	do
	{
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    	} while (value);

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while (ptr1 < ptr) 
	{
        	tmp_char = *ptr;
        	*ptr--= *ptr1;
        	*ptr1++ = tmp_char;
	}
	return result;
}

void len_check(char* to_check)
{
	if(strlen(to_check) == 1)
		prepend(to_check, "0");
}

void *memmove(void *dest, void const *src, int n)
{
	register char *dp = dest;
	register char const *sp = src;
	if(dp < sp) 
	{
		while(n-- > 0)
			*dp++ = *sp++;
	} 
	else 
	{
		dp += n;
		sp += n;
		while(n-- > 0)
			*--dp = *--sp;
	}

	return dest;
}

void prepend(char* s, const char* t)
{
	int len = strlen(t);
	int i;
	memmove(s + len, s, strlen(s) + 1);

	for (i = 0; i < len; ++i)
        s[i] = t[i];
}

void *memcpy(void *dest, const void *src, size_t count)
{
    const char *sp = (const char *)src;
    char *dp = (char *)dest;
    for(; count != 0; count--) *dp++ = *sp++;
    return dest;
}

void *memset(void *dest, char val, size_t count)
{
    char *temp = (char *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, size_t count)
{
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

size_t strlen(const char *str)
{
    size_t retval;
    for(retval = 0; *str != '\0'; str++) retval++;
    return retval;
}

void show_message(char* message)
{
	puts(message);
	putch('\n');
}


unsigned char inportb (unsigned short _port)
{
    unsigned char rv;
    asm volatile("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (unsigned short _port, unsigned char _data)
{
    asm volatile("outb %1, %0" : : "dN" (_port), "a" (_data));
}
