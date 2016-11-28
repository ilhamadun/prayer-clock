#include <stdbool.h>
#include "unity.h"
#include "seven_segment_decoder.h"


void setUp(void) {}
void tearDown(void) {}

void decode_seven_segments(struct seven_segment_t seven_segment, uint8_t actual_segments[], bool decimal_point)
{
	for (int i = 0; i < 10; i++) {
		actual_segments[i] = decode_digit_to_seven_segment(seven_segment, i, decimal_point);
	}
}

void test_decode_common_cathode_seven_segment_with_order_a_to_g(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_CATHODE, A_TO_G, DECIMAL_POINT_DISABLED);
	uint8_t actual_segments[10];
	uint8_t expected_segments[10] = {
		0b1111110, // 0
		0b0110000, // 1
		0b1101101, // 2
		0b1111001, // 3
		0b0110011, // 4
		0b1011011, // 5
		0b1011111, // 6
		0b1110000, // 7
		0b1111111, // 8
		0b1111011  // 9
	};

	decode_seven_segments(seven_segment, actual_segments, DECIMAL_POINT_OFF);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_segments, actual_segments, 10);
}

void test_decode_common_cathode_seven_segment_with_order_g_to_a(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_CATHODE, G_TO_A, DECIMAL_POINT_DISABLED);
	uint8_t actual_segments[10];
	uint8_t expected_segments[10] = {
		0b0111111, // 0
		0b0000110, // 1
		0b1011011, // 2
		0b1001111, // 3
		0b1100110, // 4
		0b1101101, // 5
		0b1111101, // 6
		0b0000111, // 7
		0b1111111, // 8
		0b1101111  // 9
	};

	decode_seven_segments(seven_segment, actual_segments, DECIMAL_POINT_OFF);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_segments, actual_segments, 10);
}

void test_decode_common_anode_seven_segment_with_order_a_to_g(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_ANODE, A_TO_G, DECIMAL_POINT_DISABLED);
	uint8_t actual_segments[10];
	uint8_t expected_segments[10] = {
		0b0000001, // 0
		0b1001111, // 1
		0b0010010, // 2
		0b0000110, // 3
		0b1001100, // 4
		0b0100100, // 5
		0b0100000, // 6
		0b0001111, // 7
		0b0000000, // 8
		0b0000100  // 9
	};

	decode_seven_segments(seven_segment, actual_segments, DECIMAL_POINT_OFF);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_segments, actual_segments, 10);
}

void test_decode_common_anode_seven_segment_with_order_g_to_a(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_ANODE, G_TO_A, DECIMAL_POINT_DISABLED);
	uint8_t actual_segments[10];
	uint8_t expected_segments[10] = {
		0b1000000, // 0
		0b1111001, // 1
		0b0100100, // 2
		0b0110000, // 3
		0b0011001, // 4
		0b0010010, // 5
		0b0000010, // 6
		0b1111000, // 7
		0b0000000, // 8
		0b0010000  // 9
	};

	decode_seven_segments(seven_segment, actual_segments, DECIMAL_POINT_OFF);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_segments, actual_segments, 10);
}

void test_decode_common_cathode_with_decimal_point(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_CATHODE, A_TO_G, DECIMAL_POINT_ENABLED);
	uint8_t actual_segments[10];
	uint8_t expected_point_off_segments[10] = {
		0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110,
		0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110
	};
	uint8_t expected_point_on_segments[10] = {
		0b11111101, 0b01100001, 0b11011011, 0b11110011, 0b01100111,
		0b10110111, 0b10111111, 0b11100001, 0b11111111, 0b11110111
	};

	decode_seven_segments(seven_segment, actual_segments, DECIMAL_POINT_OFF);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_point_off_segments, actual_segments, 10);

	decode_seven_segments(seven_segment, actual_segments, DECIMAL_POINT_ON);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_point_on_segments, actual_segments, 10);
}

void test_decode_common_anode_with_decimal_point(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_ANODE, G_TO_A, DECIMAL_POINT_ENABLED);
	uint8_t actual_segments[10];
	uint8_t expected_point_off_segments[10] = {
		0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001,
		0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10010000
	};
	uint8_t expected_point_on_segments[10] = {
		0b01000000, 0b01111001, 0b00100100, 0b00110000, 0b00011001,
		0b00010010, 0b00000010, 0b01111000, 0b00000000, 0b00010000
	};

	decode_seven_segments(seven_segment, actual_segments, DECIMAL_POINT_OFF);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_point_off_segments, actual_segments, 10);

	decode_seven_segments(seven_segment, actual_segments, DECIMAL_POINT_ON);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_point_on_segments, actual_segments, 10);
}

void test_decode_with_digit_bigger_than_9(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_CATHODE, A_TO_G, DECIMAL_POINT_DISABLED);
	uint8_t actual_segments = decode_digit_to_seven_segment(seven_segment, 12, false);

	TEST_ASSERT_EQUAL_HEX8(0x6D, actual_segments);
}
