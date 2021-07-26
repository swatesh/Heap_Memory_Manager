#ifndef __MM__
#define __MM__

#include <stdint.h>
#include <stddef.h> /*for size_t*/

// Phase 2 

#define MM_MAX_STRUCT_NAME 32
typedef struct vm_page_family_{

    char struct_name[MM_MAX_STRUCT_NAME];
    uint32_t struct_size;
    //vm_page_t *first_page;
    //glthread_t free_block_priority_list_head;
} vm_page_family_t;

typedef struct vm_page_for_families_{
    struct vm_page_for_families_ *next;
    vm_page_family_t vm_page_family[0];
} vm_page_for_families_t;


#define MAX_FAMILIES_PER_VM_PAGE   \
    ((SYSTEM_PAGE_SIZE - sizeof(vm_page_for_families_t *))/sizeof(vm_page_family_t))

#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr, curr)                 \
{                                                                                   \
    uint32_t _count = 0;                                                             \
    for(curr = (vm_page_family_t *)&vm_page_for_families_ptr->vm_page_family[0];    \
        curr->struct_size && _count < MAX_FAMILIES_PER_VM_PAGE;                      \
        curr++,_count++){

#define ITERATE_PAGE_FAMILIES_END(vm_page_for_families_ptr, curr)   }}

vm_page_family_t *
lookup_page_family_by_name(char *struct_name);

#endif /**/