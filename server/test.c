#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
	char *test_str = "it is what it is.";
	printf("size using sizeof: %d\n", sizeof(test_str));

	printf("size using strlen: %ld\n", strlen(test_str));

}
