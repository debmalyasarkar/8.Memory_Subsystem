#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>

#define SIZE 5000

/* Fragmented Memory Allocator Pointer */
void *fmptr;

int init_module(void)
{
  pr_info("%s\n",__func__); 
  
  /* Allocate Virtually Contigious Memory */
  fmptr = vmalloc(SIZE);
  if(NULL == fmptr)
  {
    pr_info("Fragment Allocator Failed\n");
    return -ENOMEM;
  }
  pr_info("Kernel Virtual Address = %p\n",fmptr);
  return 0;
}

void cleanup_module(void)
{
  /* Release the Allocated Memory */
  vfree(fmptr);
  pr_info("%s\n",__func__);
}

MODULE_AUTHOR("debmalyasarkar1@gmail.com");
MODULE_DESCRIPTION("Fragment Allocator - Interface Functions");
MODULE_LICENSE("GPL");
