#include"LPC213x.h"

//__irq void I2C_ISR()
void I2C_ISR(void)__irq
{
	static int flag = 1;
	int temp=0;
	temp=I2C0STAT;
	switch(temp)
	{
		case 8:					/* Start condition transmitted */
			I2C0DAT=0XA0;  		/* Slave address + write */
			I2C0CONCLR=0x28; 	/* Clear SI and Start flag */
			break;
		
		case 24: 				/* Acknowledgement received from slave for slave address */
			I2C0DAT=0X00;  		/* Data to be transmitted */
			I2C0CONCLR=0x8;		/* clear SI */
			break;
		
		case 40:				/* Acknowledgement received from slave for byte transmitted from master. Stop
								condition is transmitted in this state signaling the end of transmission */
			if(flag)
			{
				I2C0DAT='A';
				flag = 0;
			}
			else
			{
				I2C0CONSET=0x10; 	/* Transmit stop condition */
			}
			I2C0CONCLR=0x8;  	/* clear SI */
			break;
		
		default :
			break;
	} 
	
	//VICVectAddr = 0xFF;  		// Change here
	VICVectAddr	= 0;
}

void i2c_init()
{
	
	//MEMMAP = 0x2;				/* Remap interrupt vectors to SRAM */
	PINSEL0 = 0x50;				/* Initialize Pin Connect Block */
	I2C0CONCLR = 0XFF; 			/* clearing all flags */
	//I2C0CONSET = 0x40; 		// Change here 
	I2C0CONSET = 0X44;		   // ENABLE THE I2C BY SETTING I2EN BIT & ACKNOWEDGE FLAG SET  
	I2C0SCLH = 0x96; 			/* 100 KHz */
	I2C0SCLL = 0x96;
	
	/* Initialize VIC for I 2 C use */
	VICIntSelect = 0x0; 				/* selecting IRQ */
	VICIntEnable = 0x200;  				/* enabling I 2 C */
	VICVectCntl0 = (1<<5) | (0x09); 	/* highest priority and enabled, int_request(4:0) = 0x09, IRQslot_en1(5) = 1 */
	VICVectAddr0 = (unsigned) I2C_ISR;	/* ISR address written to the respective address register*/
}

int main()
{
	i2c_init();
	I2C0CONSET=0x64; 			/* Send start bit */
	while(1);
}


