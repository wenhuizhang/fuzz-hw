// program adapted from an example by mykter

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define INPUTSIZE 100


int process(char *input)
{
	char *out;
	char *rest;
	int len, newlen;
        int i;
	input[INPUTSIZE-1] = '\n';
	if (strncmp(input, "u ", 2) == 0)
	{ // upper case command
		char *rest;
		char delim[] = " ";
		char *ptr0 = strtok(input, delim);
		char *ptr1 = strtok(input, delim);
		int n = atoi(ptr1);
		int count = 0;
		while (n != 0) {
        		n /= 10;     // n = n/10
        		++count;
    		}
		if ( strlen(ptr1 ) != count) {
    			printf("its not an integer\n");
			return 1;

		}	
		len = strtol(input + 2, &rest, 10); // how many characters of the string to upper-case
		newlen = atoi(input+2);
		int firstN = input[2] - '0';
		if(newlen == 0 && firstN != 0){
			printf("N should be a number\n");
			return 1;
		}
		if(len < 0){
			printf("Specified length %d should be positive\n", len);
			return 1;
		}
		rest += 1;							// skip the first char (should be a space)
		out = (char*) malloc(len + strlen(input));  // could be shorter, but play it safe
		if (len > (int)strlen(input))
		{
			printf("Specified length %d was larger than the input!\n", len);
			return 1;
		}
		else if (out == NULL)
		{
			printf("Failed to allocate memory\n");
			return 1;
		}
		for (i = 0; i != len; i++)
		{
			if(!((rest[i] - 'a' >= 0) &&  (rest[i] - 'z' <= 0))){
				printf("Letters should be small letters, this program only handles ASCII\n");
				return 1;
			}
			out[i] = rest[i] - 32; // only handles ASCII
		}
		out[len] = 0;
		strcat(out, rest + len); // append the remaining text
		printf("%s", out);
		free(out);
	}
	else if (strncmp(input, "head ", 5) == 0)
	{ // head command
		if (strlen(input) > 6)
		{
			len = strtol(input + 4, &rest, 10);
			rest += 1;		  // skip the first char (should be a space)
			rest[len] = '\0'; // truncate string at specified offset
			printf("%s\n", rest);
		}
		else
		{
			fprintf(stderr, "head input was too small\n");
		}
	}
	else
	{
		return 1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	char *usage = "Usage: %s\n"
				  "Text utility - accepts commands and data on stdin and prints results to stdout.\n"
				  "\tInput             | Output\n"
				  "\t------------------+-----------------------\n"
				  "\tu <N> <string>    | Uppercased version of the first <N> bytes of <string>.\n"
				  "\thead <N> <string> | The first <N> bytes of <string>.\n";
	char input[INPUTSIZE] = {0};

	// Slurp input
	if (read(STDIN_FILENO, input, INPUTSIZE) < 0)
	{
		fprintf(stderr, "Couldn't read stdin.\n");
	}

	int ret = process(input);
	if (ret)
	{
		fprintf(stderr, usage, argv[0]);
	};
	return ret;
}
