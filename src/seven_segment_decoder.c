#include "seven_segment_decoder.h"


/**
 * Seven segment truth table in Common Cathode with order A to G
 *
 * Other seven segment configuration could be derived by doing bit operation to these values.
 */
static const uint8_t seven_segment_truth_table[10] = {
	0x7E, // 0
	0x30, // 1
	0x6D, // 2
	0x79, // 3
	0x33, // 4
	0x5B, // 5
	0x5F, // 6
	0x70, // 7
	0x7F, // 8
	0x7B  // 9
};

static uint8_t normalize_digit(uint8_t digit);
static uint8_t decode_common_cathode(uint8_t digit);
static uint8_t decode_common_anode(uint8_t digit);
static uint8_t add_decimal_point(seven_segment_t seven_segment, uint8_t segments, bool decimal_point);
static uint8_t reverse_segments(seven_segment_t seven_segment, uint8_t segments);


seven_segment_t initialize_seven_segment(common_t type, segment_order_t order, bool decimal_point)
{
	struct seven_segment_t seven_segment;
	seven_segment.common = type;
	seven_segment.order = order;
	seven_segment.decimal_point = decimal_point;

	return seven_segment;
}

uint8_t decode_digit_to_seven_segment(seven_segment_t seven_segment, uint8_t digit, bool decimal_point)
{
	uint8_t segments;
	digit = normalize_digit(digit);

	if (seven_segment.common == COMMON_CATHODE)
		segments = decode_common_cathode(digit);
	else
		segments = decode_common_anode(digit);

	if (seven_segment.decimal_point == DECIMAL_POINT_ENABLED)
		segments = add_decimal_point(seven_segment, segments, decimal_point);

	if (seven_segment.order == G_TO_A)
		segments = reverse_segments(seven_segment, segments);

	return segments;
}

/**
 * Make sure digit is not bigger than 9
 */
inline uint8_t normalize_digit(uint8_t digit)
{
	return digit % 10;
}

uint8_t decode_common_cathode(uint8_t digit)
{
	return seven_segment_truth_table[digit];
}

uint8_t decode_common_anode(uint8_t digit)
{
	return ~(seven_segment_truth_table[digit] | 0x80);
}

uint8_t add_decimal_point(seven_segment_t seven_segment, uint8_t segments, bool decimal_point)
{
	segments <<= 1;

	if (seven_segment.common == COMMON_CATHODE) {
		segments |= (decimal_point == DECIMAL_POINT_ON ? 1 : 0);
	} else {
		segments |= (decimal_point == DECIMAL_POINT_ON ? 0 : 1);
	}

	return segments;
}

uint8_t reverse_segments(seven_segment_t seven_segment, uint8_t segments)
{
	uint8_t reversed = segments;
	reversed = (reversed & 0xAA) >> 1 | (reversed & 0x55) << 1;
	reversed = (reversed & 0xCC) >> 2 | (reversed & 0x33) << 2;
	reversed = (reversed & 0xF0) >> 4 | (reversed & 0x0F) << 4;

	if (seven_segment.decimal_point == DECIMAL_POINT_DISABLED)
		reversed >>= 1;

	return reversed;
}