#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "base64.h"
#include "version.h"

const char* COMPILE_INFO = "Compiled on " __DATE__ " at " __TIME__;

int main(int argc, char *argv[]) {
	if (argc == 2) {
		if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
			printf(
				"Usage: b64 [options] [file1 file2 ...]\n"
				"\n"
				"Base64 encoder/decoder. Reads input files or stdin, writes to a single output or stdout.\n"
				"\n"
				"Options:\n"
				"  -d    --decode       Decode input instead of encoding\n"
				"  -o <file>            Write output to <file> instead of stdout\n"
				"  -h    --help         Show this help message and exit\n"
				"  -v    --version      Show version information and exit\n"
				"\n"
				"If no input files are given, input is read from stdin.\n"
				"\n"
				"Examples:\n"
				"  b64 input.txt > out.b64\n"
				"  b64 -d -o decoded.bin out.b64\n"
				"  cat data | b64 > encoded.txt\n"
				"\n"
			);
			return 0;
		} else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
			printf("%s - %s - %s\n", APP_NAME, VERSION_FULL_STR, COMPILE_INFO);
			return 0;
		}
	}

	int error = 0;
	bool decode = 0;
	bool ignore_garbage = 0; // not implemented yet, may not be needed

	FILE *out = stdout;
	char **infiles = malloc(argc * sizeof(char*));
	int n_infiles = 0;

	// Parse args
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--decode") == 0) {
			decode = true;
		} else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--ignore-garbage") == 0) {
			ignore_garbage = true;
		} else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
			out = fopen(argv[++i], decode ? "wb" : "w");
			if (!out) {
				perror("fopen output");
				error = 1;
				break;
			}
		} else if (argv[i][0] == '-') {
			fprintf(stderr, "Unknown option: '%s'\n", argv[i]);
			error = 1;
			break;
		} else {
			infiles[n_infiles++] = argv[i];
		}
	}

	if (error) {
		free(infiles);
		return error;
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

			if (decode) {
				error = base64_decode(in, out);
			} else {
				base64_encode(in, out);
			}

			fclose(in);
			if (error) break;
		}
	}

	if (out != stdout) fclose(out);
	free(infiles);
	return error;
}
