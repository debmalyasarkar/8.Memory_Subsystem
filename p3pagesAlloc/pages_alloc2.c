#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>

/* Number of Pages = 2^ORDER */
#define ORDER 2
#define TEST_VAL 0xAA

int init_module(void)
{
  char *linearAddr;
  int ii;

  pr_info("Page Size = %ld\n",PAGE_SIZE);

  /* Allocate Pages - Internally Allocates in Multiples of 2 */
  linearAddr = (char *)__get_free_pages(GFP_KERNEL, ORDER);
  if(!linearAddr)
  {
    pr_err("Get Free Pages Failed\n");
    return -ENOMEM;
  }
    
  pr_info("Linear Address = %p\n",linearAddr);

  /* Access allocated memory */
  /* As Order is 2 so Num of Pages is 2^2 i.e. 4 */
  for(ii = 0; ii < PAGE_SIZE * 4; ii++)
    linearAddr[ii] = TEST_VAL;

//  for(ii = 0; ii < PAGE_SIZE * 4; ii++)
//   pr_info("%02X\n",(uint8_t)linearAddr[ii]); 

  /* Free the Allocated Page */
  free_pages((unsigned long)linearAddr, ORDER);

  return 0;
}

void cleanup_module(void)
{
  pr_info("%s\n",__func__);
}

MODULE_AUTHOR("debmalyasarkar1@gmail.com");
MODULE_DESCRIPTION("Page Allocator - Interface Functions Set 2");
MODULE_LICENSE("GPL");
