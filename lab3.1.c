/*
===============================================================================
 Name        : lab3.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#define CLKSRCSEL (*(volatile unsigned int *)0x400FC10C)
#define PLL0CFG (*(volatile unsigned int *)0x400fc084)
#define PLL0CON (*(volatile unsigned int *)0x400fc080)
#define PLL0FEED (*(volatile unsigned int *)0x400fc08c)
#define PLL0STAT (*(volatile unsigned int *)0x400fc088)
#define CCLKCFG (*(volatile unsigned int *)0x400fc104)
#define CLKOUTCFG (*(volatile unsigned int *)0x400FC1C8)
#define PINSEL3 (*(volatile unsigned int *)0x4002C00C)

void config() {
		CLKSRCSEL &= 0;
		CLKOUTCFG &= 0;
		CLKOUTCFG |= (1<<8);
		PINSEL3 &= ~(1<<23);
		PINSEL3 |= (1<<22);

}

void PLL0feed() {
	PLL0FEED = 0xAA;
	PLL0FEED = 0x55;
}

void PLL0seq() {
	int M = (103 / 2);
	int N = 1;
	int K = (208 / 7);
	PLL0CON &= ~(1<<1);
	PLL0feed();
	PLL0CON &= ~(1<<0);
	PLL0feed();
	CLKSRCSEL &= 0;
	PLL0CFG |= (M<<0);
	PLL0CFG |= (N<<16);
	PLL0feed();
	PLL0CON &= ~(1<<0);
	PLL0CON |= (1<<0);
	PLL0feed();
	PLL0STAT |= (1<<26);
	CCLKCFG |= (K<<0);
	PLL0CON |= (1<<1);
	PLL0feed();
}


int main(void) {
	config();
	PLL0seq();

}
