/*
 * PwmNode.h
 *
 *  Created on: 2017. máj. 19.
 *      Author: peti
 */

#ifndef PWMNODE_H_
#define PWMNODE_H_

#include "mprotocol-nodes/Node.h"
#include <stm32f1xx_hal.h>

class PwmNode: public Node {
	DECLARE_PROP_INT32_RW(R);
	DECLARE_PROP_INT32_RW(G);
	DECLARE_PROP_INT32_RW(B);
public:
	PwmNode(TIM_HandleTypeDef* tim, uint8_t channelR, uint8_t channelG, uint8_t channelB);
	void init();
private:
	TIM_HandleTypeDef* tim;
	uint8_t channelR, channelG, channelB;

	void setCaptureCompareReg(uint8_t channel, uint32_t value);
	uint32_t getCaptureCompareReg(uint8_t channel) const;
};

#endif /* PWMNODE_H_ */
