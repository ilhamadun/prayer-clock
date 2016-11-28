#ifndef __SEVEN_SEGMENT_DECODER_H_
#define __SEVEN_SEGMENT_DECODER_H_

#include <stdint.h>

enum common_type {COMMON_CATHODE, COMMON_ANODE};
enum segment_order {A_TO_G, G_TO_A};

struct seven_segment_t {
	enum common_type common;
	enum segment_order order;
};

/**
 * Initialize Seven Segment
 *
 * Creates a seven segment data structure, which will be passed along decoder functions.
 * 
 * @param  type  seven segment type, either COMMON_CATHODE or COMMON_ANODE
 * @param  order segment ordering, either A_TO_G or G_TO_A
 * @return       sevent segment data structure
 */
struct seven_segment_t initialize_seven_segment(enum common_type type, enum segment_order order);

/**
 * Decode Digit to Seven Segment
 *
 * Digit should be between 0 to 9. If it's bigger, the least significat digit will be decoded.
 * 
 * @param  seven_segment seven segment data structure
 * @param  digit         digit do decode
 * @return               decoded segments
 */
uint8_t decode_digit_to_seven_segment(struct seven_segment_t seven_segment, uint8_t digit);

#endif