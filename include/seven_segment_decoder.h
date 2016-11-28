#ifndef __SEVEN_SEGMENT_DECODER_H_
#define __SEVEN_SEGMENT_DECODER_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {COMMON_CATHODE, COMMON_ANODE} common_t;
typedef enum {A_TO_G, G_TO_A} segment_order_t;

enum {DECIMAL_POINT_DISABLED, DECIMAL_POINT_ENABLED};
enum {DECIMAL_POINT_OFF, DECIMAL_POINT_ON};

typedef struct seven_segment_t {
	common_t common;
	segment_order_t order;
	bool decimal_point;
} seven_segment_t;

/**
 * Initialize Seven Segment
 *
 * Creates a seven segment data structure, which will be passed along decoder functions.
 * When the decimal point is enable, segment size is 8 bit.
 * Otherwise, when the decimal point is disable, segment size is 7 bit.
 * 
 * @param  type  			seven segment type, either COMMON_CATHODE or COMMON_ANODE
 * @param  order 			segment ordering, either A_TO_G or G_TO_A
 * @param  decimal_point 	enable decimal point
 * @return       sevent segment data structure
 */
seven_segment_t initialize_seven_segment(common_t type, segment_order_t order, bool decimal_point);

/**
 * Decode Digit to Seven Segment
 *
 * Digit should be between 0 to 9. If it's bigger, the least significat digit will be decoded.
 * 
 * @param  seven_segment seven segment data structure
 * @param  digit         digit do decode
 * @param  decimal_point turn on decimal point
 * @return               decoded segments
 */
uint8_t decode_digit_to_seven_segment(seven_segment_t seven_segment, uint8_t digit, bool decimal_point);

#endif