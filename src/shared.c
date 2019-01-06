#include <stdio.h>
#include <elf.h>

#include "shared.h"


int get_osabi(uint8_t elf_osabi){
  //OS- or ABI-specific ELF extensions used by this file
  printf("OS ABI: ");
  switch(elf_osabi){
    case ELFOSABI_SYSV: /* UNIX System V ABI */
      printf("UNIX System V ABI\n");
      break;
    case ELFOSABI_HPUX: /* HP-UX */
      printf("HP-UX\n");
      break;
    case ELFOSABI_NETBSD: /* NetBSD.  */
      printf("NetBSD\n");
      break;
    case ELFOSABI_LINUX: /* Object uses GNU ELF extensions.  */
      printf("Object uses GNU ELF extensions\n");
      break;
    case ELFOSABI_SOLARIS: /* Sun Solaris.  */
      printf("Sun Solaris\n");
      break;
    case ELFOSABI_AIX: /* IBM AIX.  */
      printf("IBM AIX\n");
      break;
    case ELFOSABI_IRIX: /* SGI Irix.  */
      printf("SGI Irix\n");
      break;
    case ELFOSABI_FREEBSD: /* FreeBSD.  */
      printf("FreeBSD\n");
      break;
    case ELFOSABI_TRU64: /* Compaq TRU64 UNIX.  */
      printf("Compaq TRU64 UNIX\n");
      break;
    case ELFOSABI_MODESTO: /* Novell Modesto.  */
      printf("Novell Modesto\n");
      break;
    case ELFOSABI_OPENBSD: /* OpenBSD.  */
      printf("OpenBSD\n");
      break;
    case ELFOSABI_ARM_AEABI: /* ARM EABI */
      printf("ARM EABI\n");
      break;
    case ELFOSABI_ARM: /* ARM */
      printf("ARM\n");
      break;
    case ELFOSABI_STANDALONE: /* Standalone (embedded) application */
      printf("Standalone (embedded) application\n");
      break;
    default:
      printf("No match found for value %d\n", elf_osabi);
      return -1;
  }
  return 0;
}

int get_etype(uint16_t elf_etype){

  printf("e-type: ");
  switch(elf_etype) {
    case ET_NONE:		/* No file type */
      printf("No file type\n");
      break;
    case ET_REL:		/* Relocatable file */
      printf("Relocatable file\n");
      break;
    case ET_EXEC:		/* Executable file */
      printf("Executable file\n");
      break;
    case ET_DYN:		/* Shared object file */
      printf("Shared object file\n");
      break;
    case ET_CORE:		/* Core file */
      printf("Core file\n");
      break;
    case	ET_NUM:		/* Number of defined types */
      printf("Number of defined types\n");
      break;
    case ET_LOOS:		/* OS-specific range start */
      printf("OS-specific range start\n");
      break;
    case ET_HIOS:		/* OS-specific range end */
      printf("OS-specific range end\n");
      break;
    case ET_LOPROC:	/* Processor-specific range start */
      printf("Processor-specific range start\n");
      break;
    case ET_HIPROC:	/* Processor-specific range end */
      printf("Processor-specific range end\n");
      break;
    default:
      printf("No match found for value %d\n", elf_etype);
      return -1;
  }
  return 0;
}
