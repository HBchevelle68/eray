#include <stdio.h>  //basic i/o
#include <elf.h> //elf header types and structs
#include <errno.h> //error printing
#include <string.h>
#include <sys/types.h> //uint*_t types
#include <unistd.h>
#include <stdlib.h> //malloc

#include "shared.h"
#include "e64.h"

static Elf64_Ehdr *e64_hdr;

static
void errorexit(){
	if(e64_hdr){
		free(e64_hdr);
	}
}

static
int get_Elf64_hdr(uint32_t *fd, Elf64_Ehdr *e64h)
{
	if(e64h == NULL){
		printf("ERROR Elf64_Ehdr is NULL\n");
		return -1;
	}
	if((lseek(*fd, (off_t)0, SEEK_SET) != (off_t)0)){
		printf("[-] ERROR lseek %s\n", strerror(errno));
		return -1;
	}
	if(read(*fd, (void*)e64h, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr)){
		printf("[-] ERROR reading file (32-bit) - %s\n", strerror(errno));
		return -1;
	}

	return 0;
}

int parseElf64(uint32_t fd){
  uint8_t ret;
  e64_hdr = malloc(sizeof(Elf64_Ehdr));
  if(e64_hdr == NULL){
    printf("Heap allocation error: %d\n", errno);
    errorexit();
		return -1;
  }

  ret = get_Elf64_hdr(&fd, e64_hdr);
  if(ret != 0){
    printf("Error getting 32-bit Elf Header\n");
    errorexit();
		return -1;
  }

  ret = get_osabi(e64_hdr->e_ident[EI_OSABI]);
  if(ret != 0){
    printf("Error getting Elf OSABI\n");
    errorexit();
		return -1;
  }

	ret = get_etype(e64_hdr->e_type);
  if(ret != 0){
    printf("Error getting Elf e_type\n");
    errorexit();
		return -1;
  }

  free(e64_hdr);
  return 0;
}
