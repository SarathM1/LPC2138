/*****************
Working Code

******************/


#include<lpc213x.h>

int flag = 0;
char resp[] = "ok";

void uart(void)__irq;	  //Fn Declaration

void uart_tx_char(unsigned char ch)
{
	U0THR = ch;
	while( !(U0LSR &0x20) );
}

void uart_tx_str(char *ch)
{
	unsigned int i;
	for(i=0;ch[i]!='\0';i++)
	{
		uart_tx_char(ch[i]);
	}
}



void uart_init()
{
	PINSEL0 = 0x05; // Enable Txd0 on P0.0, Rxd0 on P0.1
	
	U0IER = 0x01; // Enable RX interrupt
	U0FCR = 0x01; //FIFO Enable
	
	U0LCR = 0x83;
	
	U0DLM = 0x00;
	U0DLL = 0xc3;
	
	U0LCR = 0x03;

}

void interrupt_init()
{
	VICIntEnable = 0x00000040; // Enable UART0 Interrupt
	VICIntSelect = 0x00000000; // Set UART0 interrupt as IRQ
	VICVectCntl0 = 0x26;	// Asign 6 for UART0 and set IRQslot_en
	VICVectAddr0 = (unsigned)uart;	 // Address for ISR
}

void uart(void)__irq // ISR for UART0
{
	char ch;
	ch = U0RBR; 		// Echo what is recieved

	lcd_char(ch);
	if(ch == resp[flag])
	{
		flag++;
		//lcd_char(ch);
	}
	VICVectAddr = 0;
}

