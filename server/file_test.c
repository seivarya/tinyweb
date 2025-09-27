#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void) {

	FILE *fp;
	int charac;
	
	fp = fopen("test_response/index.html", "r");

	while((charac = fgetc(fp)) != EOF) { // EOF is a macro in c, it gets returned by fgetc as a value when we are at the end of the file and trying to read the data that doesn't even exists!
		printf("%c", charac);
	}


	fclose(fp);
}
