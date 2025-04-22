#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void base64_encode(FILE *in, FILE *out) {
	unsigned char inbuf[3], outbuf[4];
	size_t bytes;
	while ((bytes = fread(inbuf, 1, 3, in)) > 0) {
		outbuf[0] = b64_table[inbuf[0] >> 2];
		outbuf[1] = b64_table[((inbuf[0] & 0x03) << 4) | (bytes > 1 ? inbuf[1] >> 4 : 0)];
		outbuf[2] = (bytes > 1) ? b64_table[((inbuf[1] & 0x0F) << 2) | (bytes > 2 ? inbuf[2] >> 6 : 0)] : '=';
		outbuf[3] = (bytes > 2) ? b64_table[inbuf[2] & 0x3F] : '=';
		fwrite(outbuf, 1, 4, out);
	}
}

int b64_index(char c) {
	if (c >= 'A' && c <= 'Z') return c - 'A';
	if (c >= 'a' && c <= 'z') return c - 'a' + 26;
	if (c >= '0' && c <= '9') return c - '0' + 52;
	if (c == '+') return 62;
	if (c == '/') return 63;
	return -1;
}

void base64_decode(FILE *in, FILE *out) {
	unsigned char inbuf[4], outbuf[3];
	int val[4];
	size_t i, bytes;
	int padding = 0;
	int ch;

	while (1) {
		i = 0;
		while (i < 4) {
			ch = fgetc(in);
			if (ch == EOF) {
				break;
			} else if (ch == '\n' || ch == '\r' || ch == ' ' || ch == '\t') {
				continue; // skip whitespace
			} else if (ch == '=') {
				padding++;
				inbuf[i++] = ch;
			} else {
				int idx = b64_index(ch);
				if (idx == -1) {
					fprintf(stderr, "Invalid base64 character: '%c'\n", ch);
					exit(1);
				}
				inbuf[i++] = ch;
			}
		}

		if (i == 0) break; // nothing read, done
		if (i != 4) {
			fprintf(stderr, "Incomplete base64 block\n");
			exit(1);
		}

		// Validate padding placement
		if (inbuf[0] == '=' || inbuf[1] == '=') {
			fprintf(stderr, "Invalid padding position in base64 block\n");
			exit(1);
		}

		for (int j = 0; j < 4; ++j)
			val[j] = (inbuf[j] == '=') ? 0 : b64_index(inbuf[j]);

		outbuf[0] = (val[0] << 2) | (val[1] >> 4);
		outbuf[1] = ((val[1] & 0x0F) << 4) | (val[2] >> 2);
		outbuf[2] = ((val[2] & 0x03) << 6) | val[3];

		if (inbuf[2] == '=' && inbuf[3] != '=') {
			fprintf(stderr, "Invalid padding sequence (only last two chars can be '=')\n");
			exit(1);
		}

		if (inbuf[2] == '=')
			bytes = 1;
		else if (inbuf[3] == '=')
			bytes = 2;
		else
			bytes = 3;

		fwrite(outbuf, 1, bytes, out);
	}
}

int main(int argc, char *argv[]) {
	int decode = 0;
	FILE *out = stdout;
	char **infiles = malloc(argc * sizeof(char*));
	int n_infiles = 0;

	// Parse args
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0) {
			decode = 1;
		} else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			out = fopen(argv[++i], decode ? "wb" : "w");
			if (!out) {
				perror("fopen output");
				return 1;
			}
		} else if (argv[i][0] == '-') {
			fprintf(stderr, "Unknown option: %s\n", argv[i]);
			return 1;
		} else {
			infiles[n_infiles++] = argv[i];
		}
	}

	// Read from stdin if no input files given
	if (n_infiles == 0) {
		if (decode) base64_decode(stdin, out);
		else base64_encode(stdin, out);
	} else {
		for (int i = 0; i < n_infiles; ++i) {
			FILE *in = fopen(infiles[i], "rb");
			if (!in) {
				perror(infiles[i]);
				if (out != stdout) fclose(out);
				free(infiles);
				return 1;
			}

			if (decode) base64_decode(in, out);
			else base64_encode(in, out);

			fclose(in);
		}
	}

	if (out != stdout) fclose(out);
	free(infiles);
	return 0;
}
