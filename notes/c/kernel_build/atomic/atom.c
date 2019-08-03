#include <linux/init.h>
#include <linux/module.h>

static int __init atom_init(void)
{
	atomic_t counter;

	pr_info("Hello\n");
	atomic_set(&counter, 0);
	if (atomic_inc_and_test(&counter))
		pr_info("zero1\n");

	if (atomic_dec_and_test(&counter))
		pr_info("zero2\n");

	return 0;
}

static void __exit atom_exit(void)
{
	pr_info("Good Bye!!\n");
}

module_init(atom_init);
module_exit(atom_exit);
