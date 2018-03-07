#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/pid.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vipraja Patil");
MODULE_DESCRIPTION("Print Process tree");

static int no_of_children(struct task_struct* child)
{   
	int count = 0;		
	struct list_head *list	;				
	list_for_each(list, &child->children)	
	{											
		count++;							
	}												
	return count;
}


static int __init my_module_init(void)
{
    printk(KERN_INFO "my_module_init\n");
    struct task_struct* tsk = current;

 while(tsk->pid != 0)
    {
        tsk = tsk->parent;
        printk(KERN_INFO "Process name: %s, PID: %d, State: %i, No. of children: %i, Nice: %d", tsk->comm, tsk->pid, tsk->state, no_of_children(tsk),  task_nice(tsk));

    }
	
    return 0;
}

static void __exit my_module_exit(void)
{
    printk("Exiting my module\n");
    return;
    
}

module_init(my_module_init);
module_exit(my_module_exit);
