
/* Author - Simone Cianni */

// to build:	g++ test.c -o test
// to run :	./test
// to run :	./test <n>

//sudo ./dhtest -V -m  00:53:44:11:51:12 -h ciaoooo

/*
macchanger -l | grep Bticin
0849 - 00:03:50 - Bticino Spa
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

//#include <string.h>

/**
 * random_ether_addr - Generate software assigned random Ethernet address
 * @mac: Pointer to a six-byte array containing the Ethernet address
 *
 * Generate a random Ethernet address (MAC) that is not multicast
 * and has the local assigned bit set.
 */
#define RAND_LEN 3
#define LEN 20
int new_rand_mach (char *mac)
{
        int fd;
        int res = 0 ;
	unsigned char data[RAND_LEN] = "";

	//char mac[10]="";

        fd = open ("/dev/urandom", O_RDONLY);
        if (fd > 0)
		res = read( fd, data, RAND_LEN );
        close (fd);

	sprintf(mac,"00:03:50:%02X:%02X:%02X", data[0], data[1], data[2]);
	//printf("%s \n", Mac);

        data [0] &= 0xfe;       /* clear multicast bit */
        data [0] |= 0x02;       /* set local assignment bit (IEEE802) */

        return res;
}

/*
  hostname labels may contain only the ASCII letters 'a' through 'z'
 (in a case-insensitive manner), the digits '0' through '9', and the hyphen ('-')
 Each label must be between 1 and 63 characters long.
*/
int new_hostname (char *hostn, const char *basehost, int n)
{
	/*
	unsigned char data[] = "host-";
	sprintf(hostn,"%s%d", data,n);
	*/

	/* Append */
	/*
	sprintf(hostn + strlen(hostn),"%d", n);
	*/

	sprintf(hostn,"%s-%d", basehost,n);

        return 1;
}

/*
* main function
* usge: ./test num
* it produce a script for testing
* argc 3
* argv[0] ./test
* argv[1] 1		how many
* argv[2] host          base hostname
* argv[3] (null)
*
*/
int main(int argc, char *argv[])
{
        int i;
	char mac[19]="";
	char hostn[63]=""; /* Max 63 characters */
	char basehost[LEN]="";
	FILE *fp1;
	fp1 = fopen("input.sh", "w+");
	fprintf(fp1,"#!/bin/bash\n\n");

	/* len of argument : argc */

	if (argc > 2)
		sprintf(basehost, "%s",argv[2]);
	else
		sprintf(basehost, "host");

	/*
	printf("argc %i \n", argc);
	printf("argv[0] %s \n", argv[0]);
	printf("argv[1] %s \n", argv[1]);
	printf("argv[2] %s \n", argv[2]);
	printf("argv[3] %s \n", argv[3]);
	printf("argv[4] %s \n", argv[4]);
	printf("argv[5] %s \n", argv[5]);
	*/

	if(argc <= 1 ) {
		new_rand_mach( mac );
		new_hostname( hostn, basehost, 0 );
		/* printf("%s , %s\n", mac, hostn); */
		fprintf(fp1,"sudo ./dhtest -m  %s -h %s 2>&1\n", mac, hostn);
		fprintf(fp1,"killall dhtest\n");
        }
	else {
		for(i = 0; i < atoi(argv[1]); i++){
			new_rand_mach( mac );
			new_hostname( hostn, basehost, i );
			/* printf("%s , %s\n", mac, hostn); */
			fprintf(fp1,"sudo ./dhtest -m  %s -h %s 2>&1\n", mac, hostn);
			fprintf(fp1,"killall dhtest\n");
		}
	}

	fclose(fp1);
	printf("Script created. usage: ./input.sh \n");
        return 1;
}
#if 0
....
#endif
