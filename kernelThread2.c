#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h> /* for tasklets API */

//char tasklet_data[]="We use a string; but it could be pointer to a structure";
/* Tasklet handler, that just print the data */

void tasklet_work(unsigned long data)
{
	printk("%s\n", (char *)data);
}

//DECLARE_TASKLET(my_tasklet, tasklet_function, (unsigned long) tasklet_data);

static int __init my_init(void)
{
	printf("my_init\n"); 
	//tasklet_schedule(&my_tasklet);
	return 0;
}
void my_exit(void)
{
	printf("my_exit\n");
	//tasklet_kill(&my_tasklet);
}
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("John Madieu <john.madieu@gmail.com>");
MODULE_LICENSE("GPL");
