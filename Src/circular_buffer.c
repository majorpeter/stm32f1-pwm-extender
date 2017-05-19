/*
 * circular_buffer.c
 *
 *  Created on: 2017. máj. 19.
 *      Author: peti
 */

#include "circular_buffer.h"
#include <string.h>

void circular_buffer_init(struct circular_buffer* buf, uint16_t size) {
	buf->buffer = malloc(size);
	buf->size = size;
	buf->read_index = buf->write_index = 0;
}

int circular_buffer_append(struct circular_buffer* buf, const uint8_t* data, uint16_t length) {
	uint16_t copied_bytes_count = 0;
	while (length > 0) {
		uint16_t next_write_index = buf->write_index + 1;
		if (next_write_index == buf->size) {
			next_write_index = 0;
		}

		if (next_write_index == buf->read_index) {
			return copied_bytes_count;
		}

		buf->buffer[buf->write_index] = *data;
		buf->write_index = next_write_index;

		data++;
		length--;
	}
	return copied_bytes_count;
}

int circular_buffer_get_contiguous_data(struct circular_buffer* buf, uint8_t** data) {
	*data = buf->buffer + buf->read_index;
	if (buf->read_index < buf->write_index) {
		uint16_t length = buf->write_index - buf->read_index;
		return length;
	}
	if (buf->read_index > buf->write_index) {
		uint16_t length = buf->size - buf->read_index;
		return length;
	}
	// (buf->read_index == buf->write_index) -> empty
	return 0;
}

int circular_buffer_drop_bytes(struct circular_buffer* buf, uint16_t count) {
	uint16_t length = 0;
	if (buf->read_index < buf->write_index) {
	  length = buf->write_index - buf->read_index;
	} else if (buf->read_index > buf->write_index) {
		length = buf->size - buf->read_index + buf->write_index;
	}

	if (count > length) {
		count = length;
	}

	buf->read_index += count;
	if (buf->read_index >= buf->size) {
		buf->read_index -= buf->size;
	}
	return count;
}
