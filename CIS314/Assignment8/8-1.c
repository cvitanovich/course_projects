/* Assignment 8 Problem 2 CIS 314
 * 11..26.2017
 * By Andrew Cvitanovich
 * User menu options presented in main loop.
 * Writes to cache performed by write2Cache().
 * Reads from cache performed by readCache().
 * Printing the cache uses printCache().
 */

#include <stdio.h>
#define LINES 16
#define BYTES 4
typedef struct block block;

/* 4 byte blocks */
struct block {
	unsigned char valid;
	unsigned int tag;
	unsigned char value[BYTES];
};

/* TODO: fix bit reversal on write to block */
/* write value to user specified address in cache */
void write2Cache(block *c, int length, 
	unsigned int addr, unsigned int val) {
	
	unsigned int tag = addr >> 6;
	unsigned int set = (addr >> 2) & 0xf;
	unsigned int offset = addr & 0x3;
	
	/* evicting block */
	if ( (c + set)->valid == 'y' )
		printf("evicting block - "
			" set: %i - tag: %i - valid: %i "
			" - value: %x %x %x %x\n",
			set, (c + set)->tag,
			(c + set)->valid == 'y' ? 1 : 0,
			(c + set)->value[0],
			(c + set)->value[1],
			(c + set)->value[2],
			(c + set)->value[3]);
	
	/* write to block*/
	(c + set)->valid = 'y';
	(c + set)->tag = tag;
	(c + set)->value[0] = val & 0xff;
	(c + set)->value[1] = (val >> 8) & 0xff;
	(c + set)->value[2] = (val >> 16) & 0xff;
	(c + set)->value[3] = (val >> 24) & 0xff;
	
	/* print written block results*/
	printf("wrote set: %i - tag: %i - valid: %i "
		" - value: %x %x %x %x\n",
		set, (c + set)->tag, 
		(c + set)->valid == 'y' ? 1 : 0,
		(c + set)->value[0],
		(c + set)->value[1],
		(c + set)->value[2],
		(c + set)->value[3]);	
};

/* read from cache */
void readCache(block *c, int length, unsigned int addr) {
	
	unsigned int tag = addr >> 6;
	unsigned int set = (addr >> 2) & 0xf;
	unsigned int offset = addr & 0x3;
	
	printf("looking for set: %i - tag: %i\n", set,tag);
	
	if( (c + set)->valid == 'y' ) {
	
		printf("found set: %i - tag: %i - offset: %i - "
			"valid: %i - value: %x\n",
			set, (c + set)->tag, offset,
			(c + set)->valid == 'y' ? 1 : 0,
			(c + set)->value[offset]);

		if( (c + set)->tag == tag ) {
			printf("hit!\n");
		}
		else
			printf("tags don't match - miss!\n");
	}
	else
		printf("no valid set found - miss!\n");
};

/* print the cache contents */
void printCache(block *c, int length) {
	for(int set = 0; set < length; set++) {
		if( (c + set)->valid == 'y' ) {
			printf("set: %i - tag: %i "
				"- valid: %i - value: "
				"%x %x %x %x\n",
				set, (c + set)->tag,
				(c + set)->valid == 'y' ? 1 : 0,
				(c + set)->value[0],
				(c + set)->value[1],
				(c + set)->value[2],
				(c + set)->value[3]);
		}
	};
};

int main() {
	block cache[LINES]; /* 64 byte cache with 16 blocks */
	char status = '\0';
	char junk = '\0';
	unsigned int addr;
	unsigned int val;
	
	/* main loop */
	do {
	
		/* user menu */
		/* r = read, w = write, p = print, q = quit, other characters invalid */
		printf("Enter 'r' for read,"
		" 'w' for write,"
		" 'p' for print,"
		" 'q' to quit: ");
		
		/* get user menu selection */
		scanf(" %c", &status);
		while ((junk = getchar()) != '\n' && junk != EOF) { };
		
		/* select operation to perform */
		if (status == 'r') {
			printf("Enter 32-bit unsigned hex address: ");
			scanf(" %x", &addr);
			while ((status = getchar()) != '\n' && status != EOF) { };
			readCache(&cache[0], LINES, addr);
		}
		else if (status == 'w') {
			printf("Enter 32-bit unsigned hex address: ");
			scanf(" %x", &addr);
			while ((status = getchar()) != '\n' && status != EOF) { };
			printf("Enter 32-bit unsigned hex value: ");
			scanf(" %x", &val);
			while ((status = getchar()) != '\n' && status != EOF) { };
			write2Cache(&cache[0], LINES, addr, val);
		}
		else if (status == 'p')
			printCache(&cache[0], LINES);
		else if (status == 'q')
			break;
		else {
			printf("Invalid choice!\n");
		}

	} while(status != 'q');

	return 0;
}