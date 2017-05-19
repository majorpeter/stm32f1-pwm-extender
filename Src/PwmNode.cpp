/*
 * PwmNode.cpp
 *
 *  Created on: 2017. máj. 19.
 *      Author: peti
 */

#include "PwmNode.h"

MK_PROP_INT32_RW(PwmNode, R, "Red channel PWM");
MK_PROP_INT32_RW(PwmNode, G, "Green channel PWM");
MK_PROP_INT32_RW(PwmNode, B, "Blue channel PWM");

PROP_ARRAY(props) = {
		PROP_ADDRESS(PwmNode, R),
		PROP_ADDRESS(PwmNode, G),
		PROP_ADDRESS(PwmNode, B),
};

static const int32_t PwmMaxValue = 0x100 - 1;

PwmNode::PwmNode(TIM_HandleTypeDef* tim, uint8_t channelR, uint8_t channelG, uint8_t channelB):
	Node("PWM", "PWM channels controller") {
	this->tim = tim;
	this->channelR = channelR;
	this->channelG = channelG;
	this->channelB = channelB;

	NODE_SET_PROPS(props);
}

void PwmNode::init() {
	  tim->Init.Period = PwmMaxValue;
	  HAL_TIM_Base_Init(tim);

	  HAL_TIM_PWM_Start(tim, channelR);
	  HAL_TIM_PWM_Start(tim, channelG);
	  HAL_TIM_PWM_Start(tim, channelB);

	  this->setR(0);
	  this->setG(0);
	  this->setB(0);

	  HAL_TIM_Base_Start(tim);
}

void PwmNode::setCaptureCompareReg(uint8_t channel, uint32_t value) {
	switch (channel) {
	case TIM_CHANNEL_1: tim->Instance->CCR1 = value; break;
	case TIM_CHANNEL_2: tim->Instance->CCR2 = value; break;
	case TIM_CHANNEL_3: tim->Instance->CCR3 = value; break;
	case TIM_CHANNEL_4: tim->Instance->CCR4 = value; break;
	}
}

uint32_t PwmNode::getCaptureCompareReg(uint8_t channel) const {
	switch (channel) {
	case TIM_CHANNEL_1: return tim->Instance->CCR1;
	case TIM_CHANNEL_2: return tim->Instance->CCR2;
	case TIM_CHANNEL_3: return tim->Instance->CCR3;
	case TIM_CHANNEL_4: return tim->Instance->CCR4;
	}
	return 0;
}

ProtocolResult_t PwmNode::getR(int32_t* dest) const {
	*dest = getCaptureCompareReg(channelR);
	return ProtocolResult_Ok;
}

ProtocolResult_t PwmNode::setR(const int32_t value) {
	if ((value < 0) || (value > PwmMaxValue)) {
		return ProtocolResult_InvalidValue;
	}
	this->setCaptureCompareReg(channelR, value);
	return ProtocolResult_Ok;
}

ProtocolResult_t PwmNode::getG(int32_t* dest) const {
	*dest = getCaptureCompareReg(channelG);
	return ProtocolResult_Ok;
}

ProtocolResult_t PwmNode::setG(const int32_t value) {
	if ((value < 0) || (value > PwmMaxValue)) {
		return ProtocolResult_InvalidValue;
	}
	this->setCaptureCompareReg(channelG, value);
	return ProtocolResult_Ok;
}

ProtocolResult_t PwmNode::getB(int32_t* dest) const {
	*dest = getCaptureCompareReg(channelB);
	return ProtocolResult_Ok;
}

ProtocolResult_t PwmNode::setB(const int32_t value) {
	if ((value < 0) || (value > PwmMaxValue)) {
		return ProtocolResult_InvalidValue;
	}
	this->setCaptureCompareReg(channelB, value);
	return ProtocolResult_Ok;
}
