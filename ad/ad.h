/*
 * AD.h
 *
 *  Created on: 2018-3-1
 *      Author: Dell
 */

#ifndef AD_H_
#define AD_H_
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer.h"
#include "altera_avalon_timer_regs.h"
void SetFreq(int Freq,int pointN,int BASE);
float ReadAdRes(int BASE);
#endif /* AD_H_ */
