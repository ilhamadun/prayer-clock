#include <assert.h>
#include "clock_decoder.h"


static void nomalize_digits(uint8_t *hour, uint8_t *minute, uint8_t *second);
static uint8_t decode_tens_to_seven_segment(seven_segment_t seven_segment, uint8_t number);
static uint8_t decode_unit_to_seven_segment(seven_segment_t seven_segment, uint8_t number);


clock_t initialize_clock(seven_segment_t seven_segment, bool hour_enabled, bool minute_enabled, bool second_enabled)
{
	clock_t clock;

	clock.seven_segment = seven_segment;
	clock.hour_enabled = hour_enabled;
	clock.minute_enabled = minute_enabled;
	clock.second_enabled = second_enabled;

	return clock;
}

clock_t common_cathode_clock(bool hour_enabled, bool minute_enabled, bool second_enabled, bool bit_per_digit)
{
	seven_segment_t seven_segment = initialize_seven_segment(COMMON_CATHODE, A_TO_G, bit_per_digit);

	return initialize_clock(seven_segment, hour_enabled, minute_enabled, second_enabled);
}

clock_t common_cathode_clock_reversed(bool hour_enabled, bool minute_enabled, bool second_enabled, bool bit_per_digit)
{
	seven_segment_t seven_segment = initialize_seven_segment(COMMON_CATHODE, G_TO_A, bit_per_digit);

	return initialize_clock(seven_segment, hour_enabled, minute_enabled, second_enabled);
}

clock_t common_anode_clock(bool hour_enabled, bool minute_enabled, bool second_enabled, bool bit_per_digit)
{
	seven_segment_t seven_segment = initialize_seven_segment(COMMON_ANODE, A_TO_G, bit_per_digit);

	return initialize_clock(seven_segment, hour_enabled, minute_enabled, second_enabled);
}

clock_t common_anode_clock_reversed(bool hour_enabled, bool minute_enabled, bool second_enabled, bool bit_per_digit)
{
	seven_segment_t seven_segment = initialize_seven_segment(COMMON_ANODE, G_TO_A, bit_per_digit);

	return initialize_clock(seven_segment, hour_enabled, minute_enabled, second_enabled);
}

void decode_clock_from_hour(clock_t clock, uint8_t hour, uint8_t* digits)
{
	uint8_t second = 0, minute = 0;
	nomalize_digits(&hour, &minute, &second);

	digits[0] = decode_tens_to_seven_segment(clock.seven_segment, hour);
	digits[1] = decode_unit_to_seven_segment(clock.seven_segment, hour);
}

void decode_clock_from_hour_minute(clock_t clock, uint8_t hour, uint8_t minute, uint8_t* digits)
{
	uint8_t second = 0;
	nomalize_digits(&hour, &minute, &second);

	digits[0] = decode_tens_to_seven_segment(clock.seven_segment, hour);
	digits[1] = decode_unit_to_seven_segment(clock.seven_segment, hour);
	digits[2] = decode_tens_to_seven_segment(clock.seven_segment, minute);
	digits[3] = decode_unit_to_seven_segment(clock.seven_segment, minute);
}

void decode_clock_from_hour_minute_second(clock_t clock, uint8_t hour, uint8_t minute, uint8_t second, uint8_t* digits)
{
	nomalize_digits(&hour, &minute, &second);

	digits[0] = decode_tens_to_seven_segment(clock.seven_segment, hour);
	digits[1] = decode_unit_to_seven_segment(clock.seven_segment, hour);
	digits[2] = decode_tens_to_seven_segment(clock.seven_segment, minute);
	digits[3] = decode_unit_to_seven_segment(clock.seven_segment, minute);
	digits[4] = decode_tens_to_seven_segment(clock.seven_segment, second);
	digits[5] = decode_unit_to_seven_segment(clock.seven_segment, second);
}

void nomalize_digits(uint8_t *hour, uint8_t *minute, uint8_t *second)
{
	if (*hour > 24)
		*hour = 0;
	if (*minute > 60)
		*minute = 0;
	if (*second > 60)
		*second = 0;
}

uint8_t decode_tens_to_seven_segment(seven_segment_t seven_segment, uint8_t number)
{
	uint8_t tens = (number - (number % 10)) / 10;

	return decode_digit_to_seven_segment(seven_segment, tens, DECIMAL_POINT_OFF);
}

uint8_t decode_unit_to_seven_segment(seven_segment_t seven_segment, uint8_t number)
{
	uint8_t unit = number % 10;

	return decode_digit_to_seven_segment(seven_segment, unit, DECIMAL_POINT_OFF);
}
