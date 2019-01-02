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
      printf("Error getting OSABI -> No match found for value %d\n", elf_osabi);
      return -1;
  }
  return 0;
}
