#include <stdio.h> //basic i/o
#include <elf.h>   //elf header types and structs
#include <errno.h> //error printing
#include <string.h>
#include <unistd.h>
#include <stdlib.h> //malloc

#include "shared.h"
#include "e32.h"

static Elf32_Ehdr *e32_hdr;

static
void errorexit(){
	if(e32_hdr){
		free(e32_hdr);
	}
}

static
int get_Elf32_hdr(uint32_t *fd, Elf32_Ehdr *e32h)
{
	if(e32h == NULL){
		printf("ERROR Elf32_Ehdr is NULL\n");
		return -1;
	}
	if((lseek(*fd, (off_t)0, SEEK_SET) != (off_t)0)){
		printf("[-] ERROR lseek %s\n", strerror(errno));
		return -1;
	}
	if(read(*fd, (void*)e32h, sizeof(Elf32_Ehdr)) != sizeof(Elf32_Ehdr)){
		printf("[-] ERROR reading file (32-bit) - %s\n", strerror(errno));
		return -1;
	}

	return 0;
}

int parseElf32(uint32_t fd){

  uint8_t ret;
  e32_hdr = malloc(sizeof(Elf32_Ehdr));
  if(e32_hdr == NULL){
    printf("Heap allocation error: %d\n", errno);
		errorexit();
    return -1;
  }

  ret = get_Elf32_hdr(&fd, e32_hdr);
  if(ret != 0){
    printf("Error getting 32-bit Elf Header\n");
		errorexit();
    return -1;
  }

  ret = get_osabi(e32_hdr->e_ident[EI_OSABI]);
  if(ret != 0){
    printf("Error getting Elf OSABI\n");
		errorexit();
    return -1;
  }

	ret = get_etype(e32_hdr->e_type);
  if(ret != 0){
    printf("Error getting Elf e_type\n");
		errorexit();
		return -1;
  }

  free(e32_hdr);
  return 0;
}
