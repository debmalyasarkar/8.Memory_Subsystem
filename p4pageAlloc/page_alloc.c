#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>

int init_module(void)
{
  struct page *pgDescriptor;
  char *linearAddr, *physicalAddr;
  long int pgFrameNum;

  /* Interface Functions Set 1 */
  pr_info("\n\nInterface Functions Set 1\n");

  /* Find System Page Size */
  pr_info("Page Size         = %ld\n",PAGE_SIZE);

  /* Allocate Pages - Internally Allocates in Multiples of 2 */
  /* Returns Page Descriptor which is not Directly Usable */
  pgDescriptor = alloc_page(GFP_KERNEL);
  if(!pgDescriptor)
  {
    pr_err("Alloc Page Failed\n");
    return -ENOMEM;
  }
  pr_info("Page Descriptor   = %p\n",pgDescriptor);

  /* Fetch Usable Linear Address from Page Descriptor of Allocated Page */
  linearAddr = page_address(pgDescriptor);
  pr_info("Linear Address    = %p\n",linearAddr);

  /* Get the Physical Address from the Linear Address */
  physicalAddr = (char *)__pa(linearAddr);
  pr_info("Physical Address  = %p\n",physicalAddr);

  /* Fetch the Page Frame Number from Page Descriptor */
  /* Physical Addr = Page Frame Number + Offset */
  pgFrameNum = page_to_pfn(pgDescriptor);
  pr_info("Page Frame Number = %ld",pgFrameNum);
 
  /* Free the Allocated Page */
  __free_page(pgDescriptor);


  /* Interface Functions Set 2 */
  pr_info("\n\nInterface Functions Set 2\n");

  /* Allocate Page and Obtain the Usable Linear Address */
  linearAddr = (char *)__get_free_page(GFP_KERNEL);
  if(!linearAddr)
  {
    pr_err("Get Free Page Failed\n");
    return -ENOMEM;
  }
  pr_info("Linear Address    = %p\n",linearAddr);

  /* Get the Physical Address from the Linear Address */
  physicalAddr = (char *)__pa(linearAddr);
  pr_info("Physical Address  = %p\n",physicalAddr);

  /* Get Page Frame Number by Shifting Out the OFFSET from Physical Address */
  pgFrameNum = (unsigned long)physicalAddr >> PAGE_SHIFT;
  pr_info("Page Frame Number = %ld\n",pgFrameNum);

  /* Get the Page Descriptor from the Page Frame Number */
  pgDescriptor = pfn_to_page(pgFrameNum);
  pr_info("Page Descriptor   = %p\n",pgDescriptor);
  
  /* Free the Allocated Page */
  free_page((unsigned long)linearAddr);

  return 0;
}

void cleanup_module(void)
{
  pr_info("%s\n",__func__);
}

MODULE_AUTHOR("debmalyasarkar1@gmail.com");
MODULE_DESCRIPTION("Page Allocator - Interface Functions");
MODULE_LICENSE("GPL");
