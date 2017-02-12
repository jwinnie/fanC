
/*

using stdio -> #include <stdio.h>
using ./header -> #include "header.h"

$ fanC < test.fanC > test.c

*/

#include <stdio.h>
#include <string.h>

int main() {

	char line[256];

	for (;;) {

		if (fgets(line, 255, stdin) == NULL) {
			break;

		} else {

			// @
			char *p;
			for (p = line; *p != '\0'; p++) {
				if (*p == '@') {
					*p = '*';
				}
 			}

			// using
			if (strncmp(line, "using ", 6) == 0) {

				*(line + strlen(line) - 1) = '\0';
				const char *filename = line + 6;

				if (strncmp(filename, "./", 2) == 0) {
					printf("#ifndef %s\n", filename + 2);
					printf("#include \"%s.h\"\n", filename + 2);
					printf("#define %s\n", filename + 2);
				} else {
					printf("#ifndef %s\n", filename);
 					printf("#include <%s.h>\n", filename);
					printf("#define %s\n", filename);
				}
				printf("#endif\n");

 			// func
 			} else if (strncmp(line, "func ", 5) == 0) {

 				p = line + 5;
 				char *declaration = p;
 				char *type;

 				while (strncmp(p, "->", 2) != 0 && *p != '\0') {
 					p++;
 				}

 				if (*p == '\0') break;

 				*p = '\0';

 				p += 3;

 				type = p;

 				while (*p != '{' && *p != '\0') {
 					p++;
 				}

 				*p = '\0';

 				printf("%s %s {\n", type, declaration);

 			} else {
				fputs(line, stdout);
			}
		}

	}
}