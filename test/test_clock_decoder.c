#include "unity.h"
#include "clock_decoder.h"
#include "seven_segment_decoder.h"


void setUp(void) {}
void tearDown(void) {}

void test_decode_common_cathode_clock_with_eight_bit_per_digit_second_disabled(void)
{
	uint8_t actual_digits[4];
	uint8_t expected_digits[4] = {0b11111100, 0b11100000, 0b01100110, 0b11111110};

	clock_t clock = common_cathode_clock(HOUR_ENABLED, MINUTE_ENABLED, SECOND_DISABLED, EIGHT_BITS_PER_DIGIT);
	decode_clock_from_hour_minute(clock, 07, 48, actual_digits);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_digits, actual_digits, 4);
}

void test_decode_common_cathode_reversed_with_seven_bit_per_digit_second_enabled(void)
{
	uint8_t actual_digits[6];
	uint8_t expected_digits[6] = {0b0000110, 0b1111101, 0b1001111, 0b1101111, 0b1101101, 0b1011011};

	clock_t clock = common_cathode_clock_reversed(HOUR_ENABLED, MINUTE_ENABLED, SECOND_ENABLED, SEVEN_BITS_PER_DIGIT);
	decode_clock_from_hour_minute_second(clock, 16, 39, 52, actual_digits);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_digits, actual_digits, 6);
}

void test_decode_common_anode_clock_with_seven_bit_per_digit_hour_enabled(void)
{
	uint8_t actual_digits[2];
	uint8_t expected_digits[2] = {0b0000001, 0b0001111};

	clock_t clock = common_anode_clock(HOUR_ENABLED, MINUTE_DISABLED, SECOND_DISABLED, SEVEN_BITS_PER_DIGIT);
	decode_clock_from_hour(clock, 7, actual_digits);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_digits, actual_digits, 2);
}

void test_decode_common_anode_reversed_with_eight_bit_per_digit_second_enabled(void)
{
	uint8_t actual_digits[6];
	uint8_t expected_digits[6] = {0b11111001, 0b10000010, 0b10110000, 0b10010000, 0b10010010, 0b10100100};

	clock_t clock = common_anode_clock_reversed(HOUR_ENABLED, MINUTE_ENABLED, SECOND_ENABLED, EIGHT_BITS_PER_DIGIT);
	decode_clock_from_hour_minute_second(clock, 16, 39, 52, actual_digits);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_digits, actual_digits, 6);
}

void test_decode_invalid_clock(void)
{
	uint8_t actual_digits[6];
	uint8_t expected_digits[6] = {0b11111100, 0b11111100, 0b11111100, 0b11111100, 0b01100110, 0b11111110};

	clock_t clock = common_cathode_clock(HOUR_ENABLED, MINUTE_ENABLED, SECOND_ENABLED, EIGHT_BITS_PER_DIGIT);
	decode_clock_from_hour_minute_second(clock, 35, 69, 48, actual_digits);

	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_digits, actual_digits, 6);
}
