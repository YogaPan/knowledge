#include <linux/init.h>
#include <linux/module.h>

static int __init hello_init(void)
{
	pr_info("Hello!\n");
	return 0;
}

static void __exit hello_exit(void)
{
	pr_info("Good Bye!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YogaPan <godhand1234567@gmail.com>");
MODULE_DESCRIPTION("Hello!");
