#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/errno.h>

SYSCALL_DEFINE3(sortvp, int32_t __user*, buff_ptr, int, buff_len, int32_t __user*, sort_buff)
{
 int32_t temp;
 int i,j;
 int32_t *buff = NULL;
 printk(KERN_INFO "Syscall for sorting an array from largest to smallest \n");
 buff = (int32_t*)kmalloc(sizeof(int32_t)*buff_len, GFP_KERNEL);
 if(!buff)
 {
	printk(KERN_ALERT "Malloc failed.\n");
	return -ENOMEM;
 } 
 
 
  if (buff_ptr == NULL || sort_buff == NULL)
  {
       printk(KERN_ERR "Null pointer error \n");
	kfree(buff);
       return -EINVAL;
  }
  else
  {
       if(buff_len < 256)
    {
        printk(KERN_DEBUG "Buffer size < 255 \n");
	kfree(buff);
        return -EINVAL;
    }
    
    /* copy buff_ptr, which is in the user’s address space, into buff */
    if (copy_from_user(buff, buff_ptr, (sizeof(int32_t)*buff_len)))
    {
        kfree(buff);
        return -EFAULT;
    }
    
	
    for (i=0;i<buff_len;i++)
  {
      for(j=i+1; j<buff_len; j++)
      {
          if (*(buff+i)<*(buff+j))
          {
              temp = *(buff+i);
              *(buff+i) = *(buff+j);
              *(buff+j) = temp;
          }
      }
  }
    printk("\n");

  for (i=0; i<buff_len; i++)
  {
      printk(KERN_INFO "%i",*(buff+i));
  }
    
    /* copy buff into sort_buff, which is in the user’s address space */
    if (copy_to_user(sort_buff, buff, (sizeof(int32_t)*buff_len)))
    {
        kfree(buff);
        return -EFAULT;
    }
    
  }
return 0;

}
