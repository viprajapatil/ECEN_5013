// kernel module timer

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/timer.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vipraja Patil");
MODULE_DESCRIPTION("Kernel module that use a kernel timer to wake up every 500msec");

static int wakeup = 500;
static int wakeup_count = 0;
static char *name = "Vipraja";

module_param(wakeup, int, S_IRUSR | S_IWUSR | S_IXUSR );
MODULE_PARM_DESC(wakeup, "Kernel Timeout");
module_param(wakeup_count, int, S_IRUSR | S_IWUSR | S_IXUSR );
MODULE_PARM_DESC(wakeup_count, "Count of how many times the timer has fired");
module_param(name, charp, S_IRUSR | S_IWUSR | S_IXUSR);
MODULE_PARM_DESC(name, "My name");

struct timer_list myTimer;

static void time_handler(void)
{   wakeup_count++;
    printk(KERN_INFO "Name: %s, Triggered count: %d", name, wakeup_count);
    mod_timer(&myTimer, jiffies + msecs_to_jiffies(wakeup));
}

static int __init my_module_init(void)
{
    printk(KERN_INFO "my_module_init\n");
    init_timer(&myTimer);
    myTimer.data = (unsigned long)0;
    myTimer.expires = jiffies + msecs_to_jiffies(wakeup);
    myTimer.function = (void(*)(unsigned long))time_handler;
    add_timer(&myTimer);
    return 0;
}

static void __exit my_module_exit(void)
{
    printk("Exiting my module\n");
    del_timer(&myTimer);
    return;
    
}

module_init(my_module_init);
module_exit(my_module_exit);
