#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/pid.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/kfifo.h>



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Vipraja Patil");
MODULE_DESCRIPTION("Kthread api");

struct task_struct *p1;
struct task_struct *p2; 
struct timer_list myTimer;
#define fifoname "vpfifo"

void firstthread()
{
	kfifo_put(fifoname,current);
	mod_timer(&myTimer, jiffies + msecs_to_jiffies(500));
}

void secondthread()
{
	struct task_struct *data;
	while(1)
	{
	if (kthread_should_stop())
	break;

	int ret = kfifo_get(fifoname, &data);
	if (ret == 0)
	{
		printk("Kfifo empty");
		//printf("Kfifo empty");
	}
	else
	{
		printk(KERN_LOG "Previous pid: %d, vruntime: %llu",list_prev_entry(data,tasks)->pid, list_prev_entry(data,tasks)->se.vruntime);
		printk(KERN_LOG "Current pid: %d, vruntime: %llu",data->pid,data->vruntime);
		printk(KERN_LOG "Next pid: %d, vruntime: %llu",list_next_entry(data,tasks)->pid, list_next_entry(data,tasks)->se.vruntime);
	}

	}
}

static int __init my_module_init(void)
{
    printk(KERN_INFO "my_module_init\n");
    	INIT_KFIFO(vpfifo);
	
	// create kthreads
	p1 = kthread_run(firstthread,NULL,"First thread");
	p2 = kthread_run(secondthread, NULL, "Second thread");
	init_timer(&myTimer);
    myTimer.data = (unsigned long)0;
    myTimer.expires = jiffies + msecs_to_jiffies(500);
    myTimer.function = (void(*)(unsigned long))firstthread;
    add_timer(&myTimer);		
		
	
    return 0;
}

static void __exit my_module_exit(void)
{
    printk("Exiting my module\n");
	kthread_stop(p1);
	kthread_stop(p2);
	del_timer(&myTimer);
    return;
    
}

module_init(my_module_init);
module_exit(my_module_exit);
