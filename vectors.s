;@-----------------------
.cpu cortex-m0
.thumb
;@-----------------------
.thumb_func
.global _start
_start:
	ldr r0,stacktop ;@ načítanie konštanty 0x20001000 do r0
	mov sp,r0       ;@ nastavenie stack pointra

;@--- povolenie GPIOA (RCC->AHBENR |= (1 << 19);) ---
	ldr r0,ahebnr   ;@ do r0 0x40021000 (RCC) + offst 0x14 (AHEBNR)
	ldr r0,[r0]     ;@ načítanie AHBENR
	ldr r1,ahebnrina ;@ 1<<19 do r1
	orr r1,r0,r1    ;@ r1 = (1<<19) | RCC->AHBENR
	ldr r0,ahebnr   ;@ adresa AHEBNR do R0
	str r1,[r0]     ;@ nastavenie AHEBNR

;@--- povolenie GPIO (RCC->AHBENR |= (1 << 19);) ---
	ldr r0,ahebnr   ;@ do r0 0x40021000 (RCC) + offst 0x14 (AHEBNR)
	ldr r0,[r0]     ;@ načítanie AHBENR
	ldr r1,ahebnrinc ;@ 1<<19 do r1
	orr r1,r0,r1    ;@ r1 = (1<<19) | RCC->AHBENR
	ldr r0,ahebnr   ;@ adresa AHEBNR do R0
	str r1,[r0]     ;@ nastavenie AHEBNR


;@--- hlavný program ---
	bl mainprog     ;@ zavolanie hlavného programu
	b hang          ;@ ukončenie programu
.thumb_func
hang:   b .
;@-----------------------
.align
stacktop: .word 0x20001000
ahebnr:   .word 0x40021014
ahebnrina: .word 0x00020000
ahebnrinc: .word 0x00080000
;@-----------------------
.end
;@-----------------------
