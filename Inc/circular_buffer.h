/*
 * circular_buffer.h
 *
 *  Created on: 2017. máj. 19.
 *      Author: peti
 */

#ifndef CIRCULAR_BUFFER_H_
#define CIRCULAR_BUFFER_H_

#include <stdint.h>

struct circular_buffer {
	uint8_t* buffer;
	uint16_t size;
	uint16_t read_index;
	uint16_t write_index;
};

void circular_buffer_init(struct circular_buffer* buf, uint16_t size);
int circular_buffer_append(struct circular_buffer* buf, const uint8_t* data, uint16_t length);
int circular_buffer_get_contiguous_data(struct circular_buffer* buf, uint8_t** data);
int circular_buffer_drop_bytes(struct circular_buffer* buf, uint16_t count);

#endif /* CIRCULAR_BUFFER_H_ */
