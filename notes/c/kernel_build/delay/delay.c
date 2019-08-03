#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>

static int __init delay_init(void)
{
	pr_info("delay module loaded\n");

	pr_info("you will see next message after 1000 mseconds...\n");
	udelay(1000);
	pr_info("you see me now!\n");

	return 0;
}

static void __exit delay_exit(void)
{
	pr_info("delay module unloaded\n");
}

module_init(delay_init);
module_exit(delay_exit);

MODULE_AUTHOR("YogaPan <godhand1234567@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Delay");
