#include <stdio.h>  //basic i/o
#include <stdint.h> // portable types
// file ops
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <unistd.h>
//elf header types and structs
#include <elf.h>
//error printing
#include <errno.h>
#include <string.h>
// assert
#include <assert.h>

#include "e32.h"

int verify_elf(Elf32_Ehdr *e32_h){
	if(!strncmp((char*)e32_h->e_ident, "\177ELF", 4)) {
		printf("Valid Elf32 \n");
		return 0;
	}
	return -1;
}

int main(int argc, char** argv){

	if(argc < 2){
		printf("Usage:  parseElf <elf file>\n");
		return 0;
	}
	uint32_t fd = 0;
	Elf32_Ehdr elf32_h = {0};

	fd = open(argv[1], O_RDONLY | O_SYNC);
	if(fd < 0){
		printf("[-] ERROR open %s\n", strerror(errno));
	}


	//read_elf_header(fd, &elf32_h);
	if(get_Elf32_hdr(&fd, &elf32_h) != 0){
		return -1;
	}
	if(verify_elf(&elf32_h) != 0){
		return -1;
	}

	close(fd);

	return 0;
}
