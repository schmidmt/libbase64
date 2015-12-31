#include "base32.h"

static const char basis32[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

static const unsigned char b32_to_five[] = {
/*       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15*/
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 26, 27, 28, 29, 30, 31, 32, 32, 32, 32, 32,  0, 32, 32,
	32,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};

/*                15
 * 1    5    9    |
 * ABCDEFGHIJK----
 * -----+++++-0000
 *
 */

size_t Base32Encode_size(size_t len)
{
	return ((len + 4) / 5 * 8) + 1;
}


size_t Base32Encode(char * encoded, const char * string, size_t len)
{
	/* Map
	* xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
	* -----      -----      ---- -     -- ---
	*      --- --     - ----      -----      -----
	*   0     1    2     3     4    5    6     7
	*/
	char *p = encoded;
	size_t i;
	for (i = 0; i < len-4 && len >= 5; i+= 5) {
		/* 0 */	*p++ = basis32[(int)((string[i] >> 3) & 0x1F)];
		/* 1 */	*p++ = basis32[(int)(((string[i] & 0x7) << 2) | ((string[i+1] >> 6) & 0x3))];
		/* 2 */ *p++ = basis32[(int)((string[i+1] >> 1) & 0x1F)];
		/* 3 */	*p++ = basis32[(int)(((string[i+1] & 0x1) << 4) | ((string[i+2] >> 4) & 0xF))];
		/* 4 */	*p++ = basis32[(int)(((string[i+2] & 0xF) << 1) | ((string[i+3] >> 7) & 0x1))];
		/* 5 */ *p++ = basis32[(int)((string[i+3] >> 2) & 0x1F)];
		/* 6 */	*p++ = basis32[(int)(((string[i+3] & 0x3) << 3) | ((string[i+4] >> 5) & 0x7))];
		/* 7 */	*p++ = basis32[(int)((string[i+4] & 0x1F))];
	}

	switch (len - i) {
		case 0:
			break;
		case 1:
			/* 0 */	*p++ = basis32[(int)((string[i] >> 3) & 0x1F)];
			/* 1 */	*p++ = basis32[(int)((string[i] & 0x7) << 2)];
			/* 2 */ *p++ = '=';
			/* 3 */	*p++ = '=';
			/* 4 */	*p++ = '=';
			/* 5 */ *p++ = '=';
			/* 6 */	*p++ = '=';
			/* 7 */	*p++ = '=';
			break;
		case 2:
			/* 0 */	*p++ = basis32[(int)((string[i] >> 3) & 0x1F)];
			/* 1 */	*p++ = basis32[(int)(((string[i] & 0x7) << 2) | ((string[i+1] >> 6) & 0x3))];
			/* 2 */ *p++ = basis32[(int)((string[i+1] >> 1) & 0x1F)];
			/* 3 */	*p++ = basis32[(int)(((string[i+1] & 0x1) << 4))];
			/* 4 */	*p++ = '=';
			/* 5 */ *p++ = '=';
			/* 6 */	*p++ = '=';
			/* 7 */	*p++ = '=';
			break;
		case 3:
			/* 0 */	*p++ = basis32[(int)((string[i] >> 3) & 0x1F)];
			/* 1 */	*p++ = basis32[(int)(((string[i] & 0x7) << 2) | ((string[i+1] >> 6) & 0x3))];
			/* 2 */ *p++ = basis32[(int)((string[i+1] >> 1) & 0x1F)];
			/* 3 */	*p++ = basis32[(int)(((string[i+1] & 0x1) << 4) | ((string[i+2] >> 4) & 0xF))];
			/* 4 */	*p++ = basis32[(int)(((string[i+2] & 0xF) << 1))];
			/* 5 */ *p++ = '=';
			/* 6 */	*p++ = '=';
			/* 7 */	*p++ = '=';
			break;
		case 4:
			/* 0 */	*p++ = basis32[(int)((string[i] >> 3) & 0x1F)];
			/* 1 */	*p++ = basis32[(int)(((string[i] & 0x7) << 2) | ((string[i+1] >> 6) & 0x3))];
			/* 2 */ *p++ = basis32[(int)((string[i+1] >> 1) & 0x1F)];
			/* 3 */	*p++ = basis32[(int)(((string[i+1] & 0x1) << 4) | ((string[i+2] >> 4) & 0xF))];
			/* 4 */	*p++ = basis32[(int)(((string[i+2] & 0xF) << 1) | ((string[i+3] >> 7) & 0x1))];
			/* 5 */ *p++ = basis32[(int)((string[i+3] >> 2) & 0x1F)];
			/* 6 */	*p++ = basis32[(int)(((string[i+3] & 0x3) << 3))];
			/* 7 */	*p++ = '=';
			break;
	}
	*p++ = '\0';
	return p - encoded;
}

size_t Base32Decode_size(size_t size)
{
	return ((size + 7) / 8) * 5 + 1;
}

size_t Base32Decode(char * string, const char * encoded, size_t len)
{
	/* Map
	* xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx xxxxxxxx
	* -----      -----      ---- -     -- ---
	*      --- --     - ----      -----      -----
	*   0     1    2     3     4    5    6     7
	*/
	char *p = string;
	char a, b, c, d, e, f, g, h;
	for (size_t i = 0; i < len; i+= 8) {
		a = b32_to_five[(int)encoded[i]];
		b = b32_to_five[(int)encoded[i+1]];
		c = b32_to_five[(int)encoded[i+2]];
		d = b32_to_five[(int)encoded[i+3]];
		e = b32_to_five[(int)encoded[i+4]];
		f = b32_to_five[(int)encoded[i+5]];
		g = b32_to_five[(int)encoded[i+6]];
		h = b32_to_five[(int)encoded[i+7]];
		if (a >= 32 || b >= 32 || c >= 32 || d >= 32 || e >= 32 || f >= 32 || g >= 32 || h >= 32)
			return 0;

		*p++ = (a << 3) | ((b >> 2) & 0x7);
		*p++ = ((b & 0x3) << 6) | (c << 1) | ((d >> 4) & 0x1);
		*p++ = ((d & 0xF) << 4) | ((e >> 1) & 0xF);
		*p++ = ((e & 0x1) << 7) | (f << 2) | ((g >> 3) & 0x3);
		*p++ = ((g & 0x7) << 5) | h;
	}

	*p++ = '\0';
	return p - string;
}
