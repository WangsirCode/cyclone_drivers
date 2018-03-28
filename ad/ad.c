#include "ad.h"
/*
 * 函数说明：
 * 通过给定的输入信号频率和FFT点数计算并设置定时器的预置数
 * 参数说明：
 * Freq为输入信号的频率，单位为赫兹
 * pointN为fft点数
 * BASE为相应定时器基地址
 */
void SetFreq(int Freq,int pointN,int BASE)
{
    int preData = 1;//待求预置数

    preData = 50000000/(Freq * pointN);
    //修改预置数寄存器的值
    IOWR_ALTERA_AVALON_TIMER_PERIODL(BASE, 0xFFFF&preData);
    IOWR_ALTERA_AVALON_TIMER_PERIODH(BASE, (0xFFFF0000&preData)>>4);

    IOWR_ALTERA_AVALON_TIMER_CONTROL(BASE, 0x07);
}

/*
 * 函数说明：
 * 调用函数可读取AD转换结果（二补数），并返回其真实值
 * 参数说明：
 * BASE为相应AD模块数据位链接的并行IO口的基地址
 */
float ReadAdRes(int BASE)
{
    float Res = 0;                              //待计算的AD结果
	int databits = 0;                           //AD结果数值位
	int DVolt = 0;                              //ADC得到二补数结果
	DVolt = IORD_ALTERA_AVALON_PIO_DATA(BASE);
	databits = DVolt & 0x7FF;
	if(0x800==(DVolt & 0x800))
	{
		Res = (databits - 0x800)/4095.0*10;
	}
	else
	{
		Res = (databits)/4095.0*10;
	}
	return Res;
}
