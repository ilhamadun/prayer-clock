#include "unity.h"
#include "seven_segment_decoder.h"


void setUp(void) {}
void tearDown(void) {}

void decode_seven_segments(struct seven_segment_t seven_segment, uint8_t actual_segments[])
{
	for (int i = 0; i < 10; i++) {
		actual_segments[i] = decode_digit_to_seven_segment(seven_segment, i);
	}
}

void test_decode_common_cathode_seven_segment_with_order_a_to_g(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_CATHODE, A_TO_G);
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

	decode_seven_segments(seven_segment, actual_segments);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_segments, actual_segments, 10);
}

void test_decode_common_cathode_seven_segment_with_order_g_to_a(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_CATHODE, G_TO_A);
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

	decode_seven_segments(seven_segment, actual_segments);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_segments, actual_segments, 10);
}

void test_decode_common_anode_seven_segment_with_order_a_to_g(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_ANODE, A_TO_G);
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

	decode_seven_segments(seven_segment, actual_segments);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_segments, actual_segments, 10);
}

void test_decode_common_anode_seven_segment_with_order_g_to_a(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_ANODE, G_TO_A);
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

	decode_seven_segments(seven_segment, actual_segments);
	TEST_ASSERT_EQUAL_HEX8_ARRAY(expected_segments, actual_segments, 10);
}

void test_decode_with_digit_bigger_than_9(void)
{
	struct seven_segment_t seven_segment = initialize_seven_segment(COMMON_CATHODE, A_TO_G);
	uint8_t actual_segments = decode_digit_to_seven_segment(seven_segment, 12);

	TEST_ASSERT_EQUAL_HEX8(0x6D, actual_segments);
}
