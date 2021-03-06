/*
 * sopc.h
 *
 *  Created on: 2018-2-27
 *      Author: Dell
 */

#ifndef SOPC_H_
#define SOPC_H_

#include "system.h"
#define _UART
typedef struct {
	union{
		struct{
			volatile unsigned long int RECEIVE_DATA :8;
			volatile unsigned long int NC :24;
		}BITS;
		volatile unsigned long int WORD;
	}RXDATA;
	union{
		struct{
			volatile unsigned long int TRANSMIT_DATA :8;
			volatile unsigned long int NC :24; //2
			}BITS;
			volatile unsigned long int WORD;
	}TXDATA;

	union{
		struct{
			volatile unsigned long int PE :1;
			volatile unsigned long int FE :1;
			volatile unsigned long int BRK :1;
			volatile unsigned long int ROE :1;
			volatile unsigned long int TOE :1;
			volatile unsigned long int TMT :1;
			volatile unsigned long int TRDY :1;
			volatile unsigned long int RRDY :1;
			volatile unsigned long int E :1;
			volatile unsigned long int NC :1;
			volatile unsigned long int DCTS :1;
			volatile unsigned long int CTS :1;
			volatile unsigned long int EOP :1;
			volatile unsigned long int NC1 :19;
		} BITS;
		volatile unsigned long int WORD;
	}STATUS;

	union{
		struct{
			volatile unsigned long int IPE :1;
			volatile unsigned long int IFE :1;
			volatile unsigned long int IBRK :1;
			volatile unsigned long int IROE :1;
			volatile unsigned long int ITOE :1;
			volatile unsigned long int ITMT :1;
			volatile unsigned long int ITRDY :1;
			volatile unsigned long int IRRDY :1;
			volatile unsigned long int IE :1;
			volatile unsigned long int TRBK :1;
			volatile unsigned long int IDCTS :1;
			volatile unsigned long int RTS :1;
			volatile unsigned long int IEOP :1;
			volatile unsigned long int NC :19; //2
			}BITS;
		volatile unsigned long int WORD;
	}CONTROL;

	union{
		struct{
			volatile unsigned long int BAUD_RATE_DIVISOR :16;
			volatile unsigned long int NC :16;
		}BITS;
		volatile unsigned int WORD;
	}DIVISOR;
}UART_ST;

#ifdef _UART
#define UART ((UART_ST *) UART_0_BASE)
#endif /*_UART */

#endif /* SOPC_H_ */
