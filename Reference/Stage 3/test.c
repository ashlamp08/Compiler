#include <stdio.h>
int main() {
	int c, i, j, nwhite, nother, max = 0, limit = 60;
	while ((c = getc(stdin)) != EOF){
		fprintf(stderr, "Read %c\n", c);
		putc(c,stdout);
	}
	return 0;
}
