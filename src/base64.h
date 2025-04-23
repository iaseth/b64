#ifndef BASE64_H
#define BASE64_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

static const char b64_table_default[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char b64_table_url_safe[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

/**
 * Encode input from a FILE* stream to base64, writing to another FILE* stream.
 *
 * @param in   Input stream (opened in binary mode)
 * @param out  Output stream (opened in text mode)
 */
void base64_encode(FILE *in, FILE *out, const char *b64_table);

/**
 * Decode base64 input from a FILE* stream, writing binary output to another stream.
 * Exits with error if invalid base64 is encountered.
 *
 * @param in   Input stream (opened in text mode)
 * @param out  Output stream (opened in binary mode)
 */
int base64_decode(FILE *in, FILE *out, const char *b64_table);

/**
 * Get index of base64 character in the base64 alphabet.
 *
 * @param c    Character to look up
 * @return     Index in base64 table (0–63) or -1 if invalid
 */
int base64_index(char c, const char *b64_table);

#ifdef __cplusplus
}
#endif

#endif // BASE64_H
