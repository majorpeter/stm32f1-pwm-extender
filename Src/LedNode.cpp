#include "LedNode.h"
#include <stm32f1xx_hal.h>
#include "main.h"

MK_PROP_BOOL_RW(LedNode, Green, "Controls the green LED on the board");

PROP_ARRAY(props) = {
	PROP_ADDRESS(LedNode, Green)
};

LedNode::LedNode(): Node("LED", "Controls the LED on the board") {
	NODE_SET_PROPS(props);
}

ProtocolResult_t LedNode::setGreen(const bool value) {
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, value ? GPIO_PIN_RESET : GPIO_PIN_SET);
	return ProtocolResult_Ok;
}

ProtocolResult_t LedNode::getGreen(bool* dest) const {
	GPIO_PinState state = HAL_GPIO_ReadPin(LED_GPIO_Port, LED_Pin);
	*dest = (state == GPIO_PIN_RESET);
	return ProtocolResult_Ok;
}
