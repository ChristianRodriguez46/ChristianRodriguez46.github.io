/* notes9.c
 * run this code through gdb to view addresses
 */

int NUM;  /* this address is in the data segment */

int main()
{
	int x = 100; /* on stack frame for main */
	NUM = 500;
	return 0;
}
  
