/*
 * example created for STMF0 ARM Cortex M0
 * at April 2013
 *
 * note: LED CUBE 5x5x5
 *
 * Under a terms of the open source a MIT License,
 * by Lukas Veselovsky. <lukves@gmail.com>
 *
 */

#include <stdint.h>

#define GPIO_BASE 0x48000000

#define GPIOA ((GPIO_Type*) (GPIO_BASE + 0x00000000))
#define GPIOC ((GPIO_Type*) (GPIO_BASE + 0x00000800))

int gpio_switch = 0;

#define L0 gpioa_out(0,1); // delay(20);
#define L1 gpioa_out(1,1); // delay(20);
#define L2 gpioa_out(2,1); // delay(20);
#define L3 gpioa_out(3,1); // delay(20);
#define L4 gpioa_out(4,1); // delay(20);
#define L5 gpioa_out(5,1); // delay(20);
#define L6 gpioa_out(6,1); // delay(20);
#define L7 gpioa_out(7,1); // delay(20);
#define L8 gpioa_out(8,1); // delay(20);
#define L9 gpioa_out(9,1); // delay(20);
#define L10 gpioa_out(0,1); // delay(20);
#define L11 gpioa_out(1,1); // delay(20);
#define L12 gpioa_out(2,1); // delay(20);
#define L13 gpioa_out(3,1); // delay(20);

#define L14 gpioc_out(15,1); // delay(20);

#define L15 gpioa_out(5,1); // delay(20);

#define L16 gpioc_out(0,1); // delay(20);
#define L17 gpioc_out(1,1); // delay(20);
#define L18 gpioc_out(2,1); // delay(20);
#define L19 gpioc_out(3,1); // delay(20);
#define L20 gpioc_out(4,1); // delay(20);
#define L21 gpioc_out(5,1); // delay(20);
#define L22 gpioc_out(6,1); // delay(20);
#define L23 gpioc_out(7,1); // delay(20);
#define L24 gpioc_out(8,1); // delay(20);


typedef struct {
	volatile uint32_t MODER;   /* mode                 0x00  */
	volatile uint16_t OTYPER;  /* output type          0x04  */
	uint16_t RESERVED0;        /* reserved             0x06  */
	volatile uint32_t OSPEEDR; /* output speed         0x08  */
	volatile uint32_t PUPDR;   /* pull-up/pull-down    0x0C  */
	volatile uint16_t IDR;     /* input data           0x10  */
	uint16_t RESERVED1;        /* reserved             0x12  */
	volatile uint16_t ODR;     /* output data          0x14  */
	uint16_t RESERVED2;        /* reserved             0x16  */
	volatile uint32_t BSRR;    /* bit set / reset      0x18  */
	volatile uint32_t LCKR;    /* config lock          0x1C  */
	volatile uint32_t AFR[2];  /* alternate function   0x20  */
	volatile uint16_t BRR;     /* bit reset            0x28  */
	uint16_t RESERVED3;        /* reserved             0x2A  */
} GPIO_Type;

void delay(int num)
{
	int i;
	for(i = 0; i < num*100; ++i) {};
}

int position;

void gpioa_out(int pos, int value) {
	
	// Nastavenie pinu PCx do output režimu
	// GPIOA->MODER = (1 << pos*2);
	// Nastavenie PCx do Push-pull režimu
	// GPIOA->OTYPER &= ~(1 << pos);
	// Vypnutie pull-up a pull-down rezistoru PCx
	// GPIOA->PUPDR &= ~(3 << pos*2);	
	
	if (gpio_switch!=1) gpioa_set();
	
	if (value==0) {
		// Vypnutie PC8 a zapnutie PCx |
		GPIOA->BRR |= (1 << pos);
		// delay();
	} else {
		// Vypnutie PC9 a zapnutie PCx |
		GPIOA->BSRR |= (1 << pos);
		// delay();
	}
	
	position=pos;
	gpio_switch = 1;
}

void gpioc_out(int pos, int value) {	
	
	// Nastavenie pinu PCx do output režimu
	//	GPIOC->MODER = (1 << pos*2);
		// Nastavenie PCx do Push-pull režimu
	//	GPIOC->OTYPER &= ~(1 << pos);
		// Vypnutie pull-up a pull-down rezistoru PCx
	//	GPIOC->PUPDR &= ~(3 << pos*2);
	
	if (gpio_switch!=3) gpioc_set();
	
	if (value==0) {
		// Vypnutie PC8 a zapnutie PCx |
		GPIOC->BRR |= (1 << pos);
		// delay();
	} else {
		// Vypnutie PC9 a zapnutie PCx 
		GPIOC->BSRR |= (1 << pos);
		// delay();
	}
	
	position=pos;
	gpio_switch = 3;
}

void gpioa_set() {
	// Nastavenie pinov z portu GPIOA do output režimu
	GPIOA->MODER = (1 << 0 | 1 << 2 | 1 << 4 | 1 << 6 | 1 << 8 | 1 << 10 | 1 << 12 | 1 << 14 | 1 << 16 | 1 << 18 | 1 << 20  | 1 << 22  | 1 << 24  | 1 << 26  | 1 << 28  | 1 << 30);
	// Nastavenie pinov z portu GPIOA do Push-pull režimu
	GPIOA->OTYPER &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8 | 1 << 9 | 1 << 10  | 1 << 11  | 1 << 12  | 1 << 13  | 1 << 14  | 1 << 15);
	// Vypnutie pull-up a pull-down rezistoru pre piny z portu GPIOA
	GPIOA->PUPDR &= ~(3 << 0 | 3 << 2 | 3 << 4 | 3 << 6 | 3 << 8 | 3 << 10 | 3 << 12 | 3 << 14 | 3 << 16 | 3 << 18 | 3 << 20  | 3 << 22  | 3 << 24  | 3 << 26  | 3 << 28  | 3 << 30);
}

void gpioc_set() {
	// Nastavenie pinov z portu GPIOC do output režimu
	GPIOC->MODER = (1 << 0 | 1 << 2 | 1 << 4 | 1 << 6 | 1 << 8 | 1 << 10 | 1 << 12 | 1 << 14 | 1 << 16 | 1 << 18 | 1 << 20  | 1 << 22  | 1 << 24  | 1 << 26  | 1 << 28  | 1 << 30);
	// Nastavenie pinov z portu GPIOC do Push-pull režimu
	GPIOC->OTYPER &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7 | 1 << 8 | 1 << 9 | 1 << 10  | 1 << 11  | 1 << 12  | 1 << 13  | 1 << 14  | 1 << 15);
	// Vypnutie pull-up a pull-down rezistoru pre Ppiny z portu GPIOC
	GPIOC->PUPDR &= ~(3 << 0 | 3 << 2 | 3 << 4 | 3 << 6 | 3 << 8 | 3 << 10 | 3 << 12 | 3 << 14 | 3 << 16 | 3 << 18 | 3 << 20  | 3 << 22  | 3 << 24  | 3 << 26  | 3 << 28  | 3 << 30);
}

// draw vertical line in 5x5 array
void draw_vline(int x, int xx, int y) {
}

int mainprog(void)
{
	// Nastavenie pinov PC8 a PC9 do output režimu
	//GPIOC->MODER = (1 << 16 | 1 << 18);
	// Nastavenie PC8 a PC9 do Push-pull režimu
	//GPIOC->OTYPER &= ~(1 << 8 | 1 << 9);
	// Vypnutie pull-up a pull-down rezistoru pre PC8 a PC9
	//GPIOC->PUPDR &= ~(3 << 16 | 3 << 18);
	
	int i=0, j=0;
	
	for(;;) {
		// Vypnutie PC8 a zapnutie PC9
		//GPIOC->BSRR = (1 << (16 + 8) | 1 << 9);
		
		gpioc_set();
		gpioc_out(10+i,1);
		
		
		L0; L1; L2;
		
		/*
		gpioa_set();
		gpioa_out(0,1); // delay(20);
		
		gpioa_out(1,1); // delay(20);
		
		gpioa_out(2,1); // delay(20);
		
		gpioa_out(3,1); // delay(20);
		
		gpioa_out(4,1); // delay(20);
		
		gpioa_out(5,1); // delay(20);
		
		gpioa_out(6,1); // delay(20);
		
		gpioa_out(7,1); // delay(20);
		
		gpioa_out(8,1); // delay(20);
		
		gpioa_out(9,1); // delay(20);
		
		gpioa_out(10,1); // delay(20);
		
		gpioa_out(11,1); // delay(20);

		gpioa_out(12,1); // delay(20);
		
		gpioa_out(13,1); // delay(20);
		
		gpioa_out(14,1); // delay(20);
		
		gpioa_out(15,1); // delay(20);
		
		
		gpioc_set();
		gpioc_out(0,1); // delay(20);
		
		gpioc_out(1,1); // delay(20);
		
		gpioc_out(2,1); // delay(20);
		
		gpioc_out(3,1);//  delay(20);
		
		gpioc_out(4,1); // delay(20);
		
		gpioc_out(5,1);//  delay(20);
		
		gpioc_out(6,1);//  delay(20);
		
		gpioc_out(7,1);//  delay(20);
		
		gpioc_out(8,1);//  delay(20);
		
		
		gpioc_out(15,1);

		delay(1000);
		
		/*
		gpioa_out(0,0); // delay(20);
		gpioa_out(1,0); // delay(20);
		gpioa_out(2,0); // delay(20);
		gpioa_out(3,0); // delay(20);
		gpioa_out(4,0); // delay(20);
		gpioa_out(5,0);//  delay(20);
		gpioa_out(6,0); // delay(20);
		gpioa_out(7,0); // delay(20);
		gpioa_out(8,0); // delay(20);
		gpioa_out(9,0); // delay(20);
		gpioa_out(10,0); // delay(20);
		gpioa_out(11,0); // delay(20);		
		gpioa_out(12,0); // delay(20);
		gpioa_out(13,0); // delay(20);
		gpioa_out(14,0); // delay(20);
		gpioa_out(15,0); // delay(20);
		
		gpioc_set();
		gpioc_out(0,0); // delay(20);
		gpioc_out(1,0); // delay(20);
		gpioc_out(2,0);//  delay(20);
		gpioc_out(3,0);//  delay(20);
		gpioc_out(4,0);//  delay(20);
		gpioc_out(5,0);//  delay(20);
		gpioc_out(6,0);//  delay(20);
		gpioc_out(7,0);//  delay(20);
		gpioc_out(8,0);//  delay(20);
		*/
		
		//gpioc_set();
		gpioc_out(10+i,0);

		
		if (j==0) i++; else i--;
		
		if (i>4) { j=1; i=4; }
		if (i<0) { j=0; i=0; }
		
		//i++; if (i>16) { i=0; j++; if (j==16) j=10; }
	}
	return 0;
}

