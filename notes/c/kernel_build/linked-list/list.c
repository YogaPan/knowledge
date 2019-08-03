#include <linux/init.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/slab.h>

#define SIZE 64

struct person {
	char name[SIZE];
	int age;
	struct list_head list;
};

static void show(void)
{
	struct person *yoga;
	struct person *mama;
	struct person *ptr;
	struct person *next;
	struct list_head *list_ptr;
	LIST_HEAD(person_list);

	yoga = kmalloc(sizeof(*yoga), GFP_KERNEL);
	strncpy(yoga->name, "Yoga", SIZE);
	yoga->age = 20;
	INIT_LIST_HEAD(&yoga->list);
	list_add_tail(&yoga->list, &person_list);

	mama = kmalloc(sizeof(*mama), GFP_KERNEL);
	strncpy(mama->name, "mama", SIZE);
	mama->age = 100;
	INIT_LIST_HEAD(&mama->list);
	list_add_tail(&mama->list, &person_list);

	list_for_each_entry(ptr, &person_list, list) {
		printk(KERN_INFO "%s: %d\n", ptr->name, ptr->age);
	}

	list_for_each(list_ptr, &person_list) {
		ptr = list_entry(list_ptr, struct person, list);
		printk(KERN_INFO "%s: %d\n", ptr->name, ptr->age);
	}

	list_for_each_entry_safe(ptr, next, &person_list, list) {
		list_del(&ptr->list);
		kfree(ptr);
	}
}

static int __init list_init(void)
{
	printk(KERN_INFO "List module loaded\n");
	show();
	return 0;
}

static void __exit list_exit(void)
{
	printk(KERN_INFO "List module exit\n");
}

module_init(list_init);
module_exit(list_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YogaPan <godhand1234567@gmail.com>");
MODULE_DESCRIPTION("List");
