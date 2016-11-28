#ifndef __CLOCK_DECODER_H__
#define __CLOCK_DECODER_H__

#include <stdint.h>
#include <stdbool.h>

#include "seven_segment_decoder.h"


enum {HOUR_DISABLED, HOUR_ENABLED};
enum {MINUTE_DISABLED, MINUTE_ENABLED};
enum {SECOND_DISABLED, SECOND_ENABLED};
enum {SEVEN_BITS_PER_DIGIT, EIGHT_BITS_PER_DIGIT};

typedef struct {
	seven_segment_t seven_segment;
	bool hour_enabled;
	bool minute_enabled;
	bool second_enabled;
} clock_t;

clock_t common_cathode_clock(bool hour_enabled, bool minute_enabled, bool second_enabled, bool bit_per_digit);
clock_t common_cathode_clock_reversed(bool hour_enabled, bool minute_enabled, bool second_enabled, bool bit_per_digit);
clock_t common_anode_clock(bool hour_enabled, bool minute_enabled, bool second_enabled, bool bit_per_digit);
clock_t common_anode_clock_reversed(bool hour_enabled, bool minute_enabled, bool second_enabled, bool bit_per_digit);
void decode_clock_from_hour(clock_t clock, uint8_t hour, uint8_t* digits);
void decode_clock_from_hour_minute(clock_t clock, uint8_t hour, uint8_t minute, uint8_t* digits);
void decode_clock_from_hour_minute_second(clock_t clock, uint8_t hour, uint8_t minute, uint8_t second, uint8_t* digits);

#endif