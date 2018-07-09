#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/printk.h>

static char *virtAddr;
static char *physAddr;

int init_module(void)
{
  /* Print the sizeof struct page */
  pr_info("%s : Size of struct page     = %u bytes\n",__func__,sizeof(struct page));

  /* Print the number of nodes / pages in page list */
  pr_info("%s : No of physical pages    = %ld bytes\n",__func__,get_num_physpages());

  /* Print the total physical memory (RAM) of the system, assuming page size is 4K */
  pr_info("%s : Total physical memory   = %ld MB\n",__func__,((4096 * get_num_physpages()) / (1024 * 1024)));

  /* Allocate a page buffer using allocator routine */
  /* Allocator routines return start linear address (page+offset) of the allocated chunk */
  virtAddr = kmalloc(4096, GFP_KERNEL);
  pr_info("%s : Virtual Address         = %p\n",__func__,virtAddr);

  /*  Get physical address mapped to linear address returned by allocator routine from page frame table */
  physAddr = (char *) __pa(virtAddr);
  pr_info("%s : Physical Address        = %p\n",__func__,physAddr);

  return 0;
}

void cleanup_module(void)
{
  pr_info("%s\n",__func__);
  kfree(virtAddr);
}

MODULE_AUTHOR("debmalyasarkar1@gmail.com");
MODULE_DESCRIPTION("Page Structure Parameters");
MODULE_LICENSE("GPL");
