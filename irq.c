#include <system.h>

//servisne rutine koje pointuju na odgovarajuci hendler
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();


//niz pokazivaca na funkcije, koristi se za custom handler-e koje imamo
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

//instalira custom handler za dati request
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
	irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
	irq_routines[irq] = 0;
}


/* Inace se request-i 0-7 mapiraju u 'entry' 8-15, sto je problem jer je 0x08 double fault(tako je definisano).
   Zato saljemo komandu PIC(mikrokontroler) da bi prebacili na ove request-e na drugi 'entry'
*/
void irq_remap(void)
{
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);
	outportb(0x21, 0x20);
	outportb(0xA1, 0x28);
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);
}


//instalira rutine na unose na koje su remapirani 
void irq_install()
{
	irq_remap();

	idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned)irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned)irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned)irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned)irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned)irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned)irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned)irq7, 0x08, 0x8E);

	idt_set_gate(40, (unsigned)irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned)irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned)irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned)irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned)irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned)irq15, 0x08, 0x8E);
}

/* Svaka rutina pointuje na ovu funkciju.
   Postoje 2 kontrolera, master na 0x20 i slejv na 0xA0
*/

void irq_handler(struct regs *r)
{
	void (*handler)(struct regs *r);

	//provjeri imas li odgovarajuci hendler za ovaj request
	handler = irq_routines[r->int_no - 32];
	if (handler)
		handler(r);

	//ako je invocirani unos veci od 40, to su IRQ8-15, signaliziraj slejv sa 0x20(EOI)
	if (r->int_no >= 40)
        	outportb(0xA0, 0x20); //interrupt zavrsen; signalizira slejv kontroleru 

	outportb(0x20, 0x20); //mora se signalizirati i master kontroler
}
