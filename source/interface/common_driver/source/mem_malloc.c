/*
 * File:        mem_malloc.c
 * Purpose:     generic malloc() and free() engine
 *
 *
 */

#include "type_def.h"
#include "mem_malloc.h"


#pragma section = "HEAP"


/********************************************************************/



static ALLOC_HDR base;
static ALLOC_HDR *freep = NULL;


/********************************************************************/
void mem_free (void *ap)
{
    ALLOC_HDR *bp, *p;

    bp = (ALLOC_HDR *)ap - 1;   /* point to block header */
    for (p = freep; !((bp > p) && (bp < p->s.ptr)) ; p = p->s.ptr)
    {
        if ((p >= p->s.ptr) && ((bp > p) || (bp < p->s.ptr)))
        {
            break; /* freed block at start or end of arena */
        }
    }

    if ((bp + bp->s.size) == p->s.ptr)
    {
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
    {
        bp->s.ptr = p->s.ptr;
    }

    if ((p + p->s.size) == bp)
    {
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
    {
        p->s.ptr = bp;
    }

    freep = p;
}

/********************************************************************/
void *mem_malloc (unsigned short nbytes)
{
    /* Get addresses for the HEAP start and end */
    char* __HEAP_START = __section_begin("HEAP");
    char* __HEAP_END = __section_end("HEAP");
    
    ALLOC_HDR *p, *prevp;
    unsigned nunits;

    nunits = ((nbytes+sizeof(ALLOC_HDR)-1) / sizeof(ALLOC_HDR)) + 1;

    if ((prevp = freep) == NULL)
    {
        p = (ALLOC_HDR *)__HEAP_START;
        p->s.size = ( ((unsigned long)__HEAP_END - (unsigned long)__HEAP_START)
            / sizeof(ALLOC_HDR) );
        p->s.ptr = &base;
        base.s.ptr = p;
        base.s.size = 0;
        prevp = freep = &base;
    }

    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)
        {
            if (p->s.size == nunits)
            {
                prevp->s.ptr = p->s.ptr;
            }
            else
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }

        if (p == freep)
            return NULL;
    }
}

/********************************************************************/
void *mem_realloc (void* p,unsigned short nbytes)
{
    void *vp = NULL;
    ALLOC_HDR *pTemp = NULL;
    unsigned int dwUnitOld = 0;
    unsigned short wIndex = 0;

    if (NULL == p)
    {
        return mem_malloc(nbytes);
    }
    /* check length. */
    pTemp = (ALLOC_HDR *)p - 1;
    dwUnitOld = pTemp->s.size;
    if(nbytes <= dwUnitOld)
    {
        return p;
    }
    /* get a new memory. */
    vp = mem_malloc(nbytes);
    if(NULL == vp)
    {
        return NULL;
    }
    /* get the data of old memory. */
    for (wIndex = 0; wIndex < ((dwUnitOld - 1) * sizeof(ALLOC_HDR)); wIndex++)
    {
        ((unsigned char*)vp)[wIndex] = ((unsigned char*)p)[wIndex];
    }
    /* release old memory. */
    mem_free(p);

    return vp;
    
}
/********************************************************************/
void mem_memset(void *p,unsigned char byte,unsigned short len)
{
    unsigned short index;
    for(index = 0;index < len;index++)
    {
        *((unsigned char*)p+index) = byte;
    }
    
    return;
}


