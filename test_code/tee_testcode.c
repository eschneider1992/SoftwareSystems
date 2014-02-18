#include <stdio.h>
     #include <stdlib.h>
     #include <unistd.h>

int main (int argc, char **argv) {

	int c;
	char line[80];
	FILE *out;
	FILE *in = fopen("input_file.txt", "r");

	if (argc < 2) {
		fprintf(stderr, "You need to give at least one argument, the name of the output file\n");
		return 1;
	}
	else if (((c = getopt (argc, argv, "a:")) != -1) && (c == 'a')) {
		out = fopen(optarg, "a");
		// fprintf(out, "I detected an a flag! \n");
	}
	else {
		out = fopen(argv[1], "w");
		// fprintf(out, "I did not detect an a flag! \n");	
	}

	fprintf(stdout, "\n");
// GOOGLE HOW TO READ A STRING AND DETECT THE END OF FILE
	while ((c =fgetc(in)) != EOF){
		fprintf(out, "%c", c);
		fprintf(stdout, "%c", c);
	}
	fprintf(stdout, "\n\n");
	fclose(out);
	return 0;

}