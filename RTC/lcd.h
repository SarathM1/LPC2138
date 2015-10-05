
void delay(unsigned int x)
{
	unsigned int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<7777;j++);
}

void lcd_char(char ch)
{
	IO1CLR = 0xffffffff;

	IO1SET = 0x000A0000;
	IO1CLR = 0x00040000;
	IO1SET = IO1SET | ( (ch & 0xf0) << 16 );
	delay(10);
	IO1CLR = 0x00080000;

	IO1CLR = 0xffffffff;

	IO1SET = 0x000A0000;
	IO1CLR = 0x00040000;
	IO1SET = IO1SET | ( (ch & 0x0F) << 20 );
	delay(10);
	IO1CLR = 0x00080000;

	IO1CLR = 0xffffffff;
	
}
void lcd_str(char ch[20])
{
	unsigned int i;
	for(i=0;ch[i]!='\0';i++)
		lcd_char(ch[i]);

}
void write_command(char ch)
{
	IO1CLR = 0xffffffff;	

	IO1CLR = 0x00060000;
	IO1SET = 0X00080000;
	IO1SET = IO1SET | ((ch & 0xf0)<<16);
	delay(10);
	IO1CLR = 0x00080000;

	
}
void cmd(char ch)
{
	IO1CLR = 0xffffffff;	

	IO1CLR = 0x00060000;
	IO1SET = 0X00080000;
	IO1SET = IO1SET | ((ch & 0xf0)<<16);
	delay(10);
	IO1CLR = 0x00080000;

	IO1CLR = 0xffffffff;

	IO1CLR = 0x00060000;
	IO1SET = 0X00080000;
	IO1SET = IO1SET | ((ch & 0x0f)<<20);
	delay(10);
	IO1CLR = 0x00080000;

	IO1CLR = 0xffffffff;

}

void lcd_int(long int num)
{
	char str[10];
	int i,r,j;

	for(i=0;i<2;i++,num/=10)
	{
		r = num%10;
		str[i] = r + 48;
	}
	str[i]='\0';

	for(j=i-1;j>=0;j--)
		lcd_char(str[j]);

}

void lcd_init()
{
	  IODIR1 |= 0x00FE0000;		 //   if bug, check IODIR1 = 0x00FE0000;  
	  write_command(0x30); 
	  delay(10);
	  write_command(0x30);
	  delay(10);
	  write_command(0x30);
	  delay(10);
	  write_command(0x20);


	cmd(0x28);  // 4 bit mode
	cmd(0x06);	// Auto incre
	cmd(0x0c);  // Cursor off
	cmd(0x01);	// LCD Clear
	
}


