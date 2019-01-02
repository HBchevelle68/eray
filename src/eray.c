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
#include "e64.h"

static
int verify_elf(uint32_t *fd, Elf64_Ehdr *e64_h){

	if(read(*fd, (void*)e64_h, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)){
		printf("[-] ERROR reading file - Elf32 header %s\n", strerror(errno));
		return -1;
	}

	if(!strncmp((char*)e64_h->e_ident, ELFMAG, 4)) {
		return e64_h->e_ident[EI_CLASS];
	}
	return -1;
}

int main(int argc, char** argv){
	uint8_t ret = 0;
	uint32_t fd = 0;
	Elf64_Ehdr elf64_h = {0}; //temp for verify elf

	if(argc < 2){
		printf("Usage: ./parseElf <file>\n");
		return 0;
	}

	fd = open(argv[1], O_RDONLY | O_SYNC);
	if(fd < 0){
		printf("[-] ERROR open %s\n", strerror(errno));
	}

	ret = verify_elf(&fd, &elf64_h);
	if(!ret){
		printf("Not Valid Elf -> Elf Magic missing\n");
		return -1;
	}
	else if(ret == 2){
		printf("ELF 64-bit\n");
		parseElf64(fd);
	}
	else if(ret == 1){
		printf("ELF 32-bit\n");
		parseElf32(fd);
	}



	close(fd);

	return 0;
}
