/*
 * AD.h
 *
 *  Created on: 2018-3-1
 *      Author: Dell
 */

#ifndef AD_H_
#define AD_H_
#include "altera_avalon_pio_regs.h"
float ReadAdRes(int BASE);
void parseAdData(float *input, unsigned char * source);
#endif /* AD_H_ */
