#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

#define KTHREADD_PID 2

static int __init task_init(void)
{
	struct task_struct *kthreadd_task;
	struct task_struct *task;
	struct list_head *list;

	printk(KERN_INFO "task load\n");

	kthreadd_task = pid_task(find_vpid(KTHREADD_PID), PIDTYPE_PID);
	printk(KERN_INFO "Process name: %s\n", kthreadd_task->comm);

	list_for_each(list, &kthreadd_task->children) {
		task = list_entry(list, struct task_struct, sibling);
		printk(KERN_INFO "    Child name: %s\n", task->comm);
	}

	for_each_process(task)
		printk(KERN_INFO "%s\n", task->comm);

	printk(KERN_INFO "\ncurrent process: %s\n", current->comm);

	return 0;
}

static void __exit task_exit(void)
{
	printk(KERN_INFO "task exit\n");
}

module_init(task_init);
module_exit(task_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YogaPan <godhand1234567@gmail.com>");
MODULE_DESCRIPTION("task");
