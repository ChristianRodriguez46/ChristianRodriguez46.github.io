/* 
 * myexec.c
 * 
 * Run this program to exec another program:
 *
 * $ gcc myecho.c -o myecho
 * $ gcc execve.c -o execve
 * $ ./myexec ./myecho
 * argv[0]: ./myecho
 * argv[1]: hello
 * argv[2]: world
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *newargv[] = { NULL, "hello", "world", NULL };
	char *newenviron[] = { NULL };

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	newargv[0] = argv[1];

	execve(argv[1], newargv, newenviron);
	perror("execve"); /* execve() only returns on error */
	exit(EXIT_FAILURE);
}

/* Below is the code for the program that will be exec'd: 
 * 
 * filename: myecho.c 
 * 
 * #include <stdio.h>
 * #include <stdlib.h>
 * 
 * int main(int argc, char *argv[])
 * {
 *    int j;
 * 
 *    for (j = 0; j < argc; j++)
 *       printf("argv[%d]: %s\n", j, argv[j]);
 * 
 *    exit(EXIT_SUCCESS);
 * }
 * 
 */
