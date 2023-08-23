/*
 * File:        mem_malloc.h
 * Purpose:     generic malloc() and free() engine
 *
 *
 */


#ifndef _MEM_MALLOC_H_
#define _MEM_MALLOC_H_

#ifdef __cplusplus
extern "C" {
#endif



/********************************************************************/

/*
 * This struct forms the minimum block size which is allocated, and
 * also forms the linked list for the memory space used with alloc()
 * and free().  It is padded so that on a 32-bit machine, all malloc'ed
 * pointers are 16-byte aligned.
 */
typedef struct ALLOC_HDR
{
    struct
    {
        struct ALLOC_HDR     *ptr;
        unsigned int size;
    } s;
//    unsigned int align;
//    unsigned int pad;
} ALLOC_HDR;


/********************************************************************/
void mem_free (void *ap);

/********************************************************************/
void *mem_malloc (unsigned short nbytes);

/********************************************************************/
void *mem_realloc (void* p,unsigned short nbytes);

/********************************************************************/
void mem_memset(void *p,unsigned char byte,unsigned short len);


#ifdef __cplusplus
}
#endif

#endif /* _MEM_MALLOC_H_ */




