#include "e32.h"



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
