#include "flash.h"
#include "altera_avalon_pio_regs.h"
//***************************
//		Pin assign
//		Cyclone			AD9833
//		PIN_142 		---> SCK
//		PIN_143 		---> MOSI
//		PIN_144			---> MISO
//***************************
int flash = 0;
#define SCLK_L   flash = flash & 0b110; IOWR_ALTERA_AVALON_PIO_DATA(FLASH_BASE, flash ) 
#define DO_L     flash = flash & 0b011; IOWR_ALTERA_AVALON_PIO_DATA(FLASH_BASE, flash)  
#define DIO_L    flash = flash & 0b101; IOWR_ALTERA_AVALON_PIO_DATA(FLASH_BASE, flash )  

#define SCLK_H   flash = flash | 0b001; IOWR_ALTERA_AVALON_PIO_DATA(FLASH_BASE, flash )   
#define DO_H     flash = flash | 0b100; IOWR_ALTERA_AVALON_PIO_DATA(FLASH_BASE, flash)
#define DIO_H    flash = flash | 0b010; IOWR_ALTERA_AVALON_PIO_DATA(FLASH_BASE, flash )

#define DO_Read IORD_ALTERA_AVALON_PIO_DATA(FLASH_BASE+2)&&0x1//读DO的宏


void SPI_Write(unsigned char data) //用SPI发送8位数据
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        SCLK_L;
        if(data&0x80)
            DIO_H;
        else
            DIO_L;
        SCLK_H;
        data<<=1;
     }
} 

unsigned char SPI_Read(void) //SPI接受8位数据
{
    unsigned char buff=0x00,i;
    for(i=0;i<8;i++)
    {
        SCLK_L;
        buff<<=1;
        if(DO_Read)
            buff|=0x01;
        SCLK_H;
    }
    return buff;
}

void Write_Enable(void) //写使能函数 对W25Q16进行写操作之前要进行这一步操作
{
    
    SPI_Write(0x06);
    
}

void Write_Disable(void) //写禁止函数
{
    
    SPI_Write(0x04);
    
}

unsigned char W25Q16_BUSY(void) //判断W25Q16是否繁忙函数 繁忙则返回1
{
    unsigned char flag;
    
    SPI_Write(0x05);
    flag=SPI_Read();
    
    flag&=0x01;
    return flag;
}

void W25Q16_Write(unsigned int address,unsigned char *data,unsigned char j)//向W25Q16写入 j个8位数据 第一个参数是 W25Q16的首地址 第二个参数是 内存的首地址
{
    unsigned char i;
    while(W25Q16_BUSY());//如果芯片繁忙就等在这里
    Write_Enable();//要先写入允许命令
    
    SPI_Write(0x02);
    SPI_Write(address>>16);
    SPI_Write(address>>8);
    SPI_Write(address);
    for(i=0;i<j;i++)
    {
        SPI_Write(*(data+i));
    }
    
}

void W25Q16_Read(unsigned int address,unsigned char *data,unsigned char j)//从W25Q16中的address地址上读取 j个字节的数据保存到 以data为首地址的内存中
{
    unsigned char i;
    while(W25Q16_BUSY());
    
    SPI_Write(0x03);
    SPI_Write(address>>16);
    SPI_Write(address>>8);
    SPI_Write(address);
    for(i=0;i<8;i++)
    {
        *(data+i)=SPI_Read();
    }
    
} 
void W25q16_Erasure()//擦除整个芯片的数据 由于芯片中的数据只能从1写到0所以 写了一次以后就不能写了 要先擦除 擦除成功后的每个字节都是 255
{
    Write_Enable();
    SPI_Write(0x00);
    Write_Enable;
    while(W25Q16_BUSY());
    
    SPI_Write(0xc7);
    
    while(W25Q16_BUSY());
} //擦除过程比较慢