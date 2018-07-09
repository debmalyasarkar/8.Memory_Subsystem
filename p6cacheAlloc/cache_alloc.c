#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>

typedef struct private_struct
{
  int param1;
  int param2;
  int param3;
  int param4;
}pstruct;

/* Private Cache */
struct kmem_cache *pcache;

/*
 * Cache Constructor Routine:
 * Invoked with address of each object as parameter, 
 * This call gets invoked whenever new objects are setup.
 */
void cache_init(void *data)
{
  pstruct *ptr = (pstruct *)data;
  ptr->param1 = 0x01;
  ptr->param2 = 0x02;
  ptr->param3 = 0x03;
  ptr->param4 = 0x04;
}
 
/* Cache Specific Derived Object Allocator Routine. */
/* Can be used from driver code for Allocation Operations. */
pstruct *palloc(void)
{
  pstruct *pobj = NULL;
  pobj = kmem_cache_alloc(pcache, GFP_KERNEL);
  if(NULL == pobj)
    pr_info("Cache Object Allocation Failed\n");
  return pobj;
}

/* Cache Specific Derived Object Deallocator Routine. */
/* Can be used from driver code for Deallocation Operations. */
void pfree(pstruct *pobj)
{
  kmem_cache_free(pcache, pobj);
}

int init_module(void)
{
  pstruct *handle = NULL;

  pr_info("%s\n",__func__);

  /* Create Private Slab Cache List and Align it with Hardware Cache */
  pcache = kmem_cache_create
           ("PrivateCache",sizeof(pstruct),0,SLAB_HWCACHE_ALIGN,cache_init);
  if(NULL == pcache)
  {
    pr_info("Cache Creation Failed\n");
    return -ENOMEM;
  }

  /* Print Cache Size */
  pr_info("Cache Size = %d\n", kmem_cache_size(pcache));

  /* Allocate an Object from Cache List */
  handle = palloc();
  if(NULL == handle)
    return -ENOMEM;

  /* Print Object Parameters Initialized by Constructor Func - cache_init() */
  pr_info("Parameter1 = %d\nParameter2 = %d\n",handle->param1, handle->param2);
  pr_info("Parameter3 = %d\nParameter4 = %d\n",handle->param3, handle->param4);

  /* Release the Object */
  pfree(handle);
  
  return 0;
}

void cleanup_module(void)
{
  /* Delete Cache List */
  kmem_cache_destroy(pcache);
  pr_info("%s\n",__func__);
}

MODULE_AUTHOR("debmalyasarkar1@gmail.com");
MODULE_DESCRIPTION("Cache Allocator - Interface Functions");
MODULE_LICENSE("GPL");
