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


int get_Elf32_hdr(uint32_t *fd, Elf32_Ehdr *e32_h)
{

	if(e32_h == NULL){
		printf("ERROR Elf32_Ehdr is NULL\n");
		return -1;
	}
	if((lseek(*fd, (off_t)0, SEEK_SET) != (off_t)0)){
		printf("[-] ERROR lseek %s\n", strerror(errno));
		return -1;
	}
	if(read(*fd, (void*)e32_h, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr)){
		printf("[-] ERROR reading file - Elf32 header %s\n", strerror(errno));
		return -1;
	}

	return 0;
}

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
