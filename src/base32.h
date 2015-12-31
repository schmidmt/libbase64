#ifndef _BASE32_H
#define _BASE32_H
/*
 *LibBase32 A library for base64 encoding/decoding
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

#include <stddef.h>

/**
 * @brief Determine length of a encoded string of length @c len.
 *
 * @param @c len Length of the string to encode.
 * @returns @c size_t Size of encoded version of string.
 */
size_t Base32Encode_size(size_t len);

/**
 * @brief Encode a string into Base 64 (https://tools.ietf.org/html/rfc4648)
 *
 * @param @c encoded Pointer to char to write encoded string to.
 * @param @c string Pointer to string to encode.
 * @param @c len Length of string to encode.
 *
 * @returns @c size_t Length of encoded string
 */
size_t Base32Encode(char * encoded, const char * string, size_t len);

/**
 * @brief Determine length of a decoded string of length @c len.
 *
 * @param @c len Length of the string to decode.
 * @returns @c size_t Size of decoded version of string.
 */
size_t Base32Decode_size(size_t size);

/**
 * @brief Decode a string from Base 64 (https://tools.ietf.org/html/rfc4648)
 *
 * @param @c string Pointer to char to write decoded string to.
 * @param @c encoded Pointer to string to decode.
 * @param @c len Length of string to decode.
 *
 * @returns @c size_t Length of encoded string or zero if error
 */
size_t Base32Decode(char * string, const char * encoded, size_t len);

#endif /*_BASE32_H */
