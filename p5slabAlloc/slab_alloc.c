#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>

/* PAGE_SIZE is the default Macro */
#define NO_OF_PAGES 10
#define SIZE (NO_OF_PAGES * PAGE_SIZE)

char *ptr;
char *newptr;

int init_module(void)
{
  int ii,jj;

  /* Allocate Slab */
  ptr = kmalloc(SIZE, GFP_KERNEL);
  if(NULL == ptr)
  {
    pr_err("Slab Allocation Failed\n");
    return -ENOMEM;
  }
 
  /* Print the base address of each page */
  /* Check if addresses are linearity and contigious */
  for(ii = 0, jj = 1; ii < SIZE; ii += PAGE_SIZE,jj++)
    pr_info("Page Number %d   = %p\n",jj,&ptr[ii]);
  
  /* Free the allocated slab */
  kfree(ptr);

  /* Testing Reallocation */
  /* Allocate Zero Filled Slab */
  ptr = kzalloc(SIZE, GFP_KERNEL);
  if(NULL == ptr)
  {
    pr_err("Slab Allocation Failed\n");
    return -ENOMEM;
  }
  /* Print the base address of the first PAGE */
  pr_info("Old Linear Address = %p\n",ptr);

  /* Reallocate the old slab with higher size */
  newptr = krealloc(ptr, SIZE * 2, GFP_KERNEL);
  if(NULL == newptr)
  {
    pr_err("Slab Reallocation Failed\n");
    return -ENOMEM;
  }
  /* Print the base address of the first page of reallocated slab */
  pr_info("New Linear Address = %p\n",newptr);

  /* Print the base address of each page */
  for(ii = 0, jj = 1; ii < SIZE * 2; ii += PAGE_SIZE,jj++)
    pr_info("Page Number %d   = %p\n",jj,&newptr[ii]);

  return 0;
}

void cleanup_module(void)
{
  pr_info("%s\n",__func__);
  /* Free the allocated Memory */
  kzfree(newptr);
}

MODULE_AUTHOR("debmalyasarkar1@gmail.com");
MODULE_DESCRIPTION("Slab Allocator - Interface Functions");
MODULE_LICENSE("GPL");
