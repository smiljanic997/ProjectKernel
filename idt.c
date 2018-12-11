#include <system.h>

//IDT entry
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

//deklaracija IDT sa 256 unosa (max 2KB); prvih 32 se koristi
struct idt_entry idt[256];
struct idt_ptr idtp;

extern void idt_load(); //u start.asm, loaduje IDT

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;

	idt[num].sel = sel; //segment koji 'entry' koristi
	idt[num].always0 = 0;
	idt[num].flags = flags; //access flag
}

void idt_install()
{
	//setuje idt pointer
	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	idtp.base = &idt;

	memset(&idt, 0, sizeof(struct idt_entry) * 256); //clear-out; resetuje sve na 0

	idt_load();
}
