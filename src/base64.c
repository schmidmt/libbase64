/*libbase64 A Base64 Encoding/Decoding Library
 *Copyright © 2015 Michael T. Schmidt <schmidmt@gmail.com>
 *
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "base64.h"

static const char basis64[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

/**
 * This array captures the ascii values of 64bit values and returns their corresponding integer values.
 * The code to acomplish this is as follows:
 *
 * @code
 *	char DeBaseChar(const char c)
 *	{
 *	        if ('A' <= c && c <= 'Z') {
 *	                return c - 'A';
 *	        } else if ('a' <= c && c <= 'z') {
 *	                return c - 'a' + 26;
 *	        } else if ( '0' <= c && c <= '9') {
 *	                return c - '0' + 52;
 *	        } else if (c == '+') {
 *	                return 62;
 *	        } else if (c == '/') {
 *	                return 63;
 *	        } else if (c == '=') {
 *	                return 0;
 *	        } else {
 *	                return 64;
 *	        }
 *	}
 * @endcode
 */
static const unsigned char b64_to_six[] = {
/*       0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15*/
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64,  0, 64, 64,
	64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
	64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};

size_t Base64Encode_size(size_t len)
{
	return ((len + 2) / 3 * 4) + 1;
}

size_t Base64Encode(char * encoded, const char * string, size_t len)
{
	char * p = encoded;
	size_t i;
	for (i = 0; i < len-2; i += 3) {
		*p++ = basis64[(int)((string[i] >> 2) & 0x3F)];
		*p++ = basis64[(int)((string[i] & 0x3) << 4) | ((string[i+1] & 0xF0) >> 4)];
		*p++ = basis64[(int)((string[i+1] & 0xF) << 2) | ((string[i+2] & 0xC0) >> 6)];
		*p++ = basis64[(int)(string[i+2] & 0x3F)];
	}

	if (i < len) {
		*p++ = basis64[(int)((string[i] >> 2) & 0x3F)];
		if (i + 1 == len) {
			*p++ = basis64[(int)((string[i] & 0x3) << 4)];
			*p++ = '=';
		} else {
			*p++ = basis64[(int)((string[i] & 0x3) << 4) | ((string[i+1] & 0xF0) >> 4)];
			*p++ = basis64[(int)((string[i+1] & 0xF) << 2)];
		}
		*p++ = '=';
	}

	*p++ = '\0';
	return p - encoded;
}

size_t Base64Decode_size(const char * encoded)
{
	size_t i = 0;
	while (b64_to_six[(int)(encoded[++i])] < 64);
	return ((i + 3) / 4) * 3;
}



size_t Base64Decode(char * string, const char * encoded, size_t len)
{
	size_t i;
	char * p = string;
	char a, b, c, d;
	for (i = 0; i < len; i+=4) {
		a = b64_to_six[(int)encoded[i]];
		b = b64_to_six[(int)encoded[i+1]];
		c = b64_to_six[(int)encoded[i+2]];
		d = b64_to_six[(int)encoded[i+3]];
		if (a >= 64 || b >= 64 || c >= 64 || d >=64)
			return 0;
		*p++ = (a << 2) | (b >> 4);
		*p++ = (b << 4) | (c >> 2);
		*p++ = (c << 6) | d;
	}
	*p++ = '\0';
	return p - string;
}
