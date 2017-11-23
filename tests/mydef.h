#ifndef MYDEF_H
#define MYDEF_H

#include "sandboxrt.h"

typedef struct moxie_memory_map_ent moxie_memory_map_ent;

#define MALLOC(length)                                         \
    mmap(NULL, (length / MACH_PAGE_SIZE + 1) * MACH_PAGE_SIZE, \
         MOXIE_PROT_READ | MOXIE_PROT_WRITE | MOXIE_PROT_EXEC, \
         MOXIE_MAP_PRIVATE | MOXIE_MAP_ANONYMOUS, -1, 0)


#endif /* ifndef MYDEF_H */
