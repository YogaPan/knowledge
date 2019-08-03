#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

#define MEMORY_MAJOR 60
char *memory_buffer;

static int memory_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int memory_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t memory_read(struct file *filp, char *buf,
		size_t count, loff_t *f_pos)
{
	int ret;

	ret = copy_to_user(buf, memory_buffer, 1);
	if (ret < 0)
		return ret;

	if (*f_pos == 0) {
		*f_pos += 1;
		return 1;
	} else {
		return 0;
	}
}

static ssize_t memory_write(struct file *filp, const char *buf,
		size_t count, loff_t *f_ops)
{
	const char *tmp;
	int ret;

	tmp = buf + count - 1;
	ret = copy_from_user(memory_buffer, tmp, 1);
	if (ret < 0)
		return ret;

	return 1;
}

static struct file_operations memory_fops = {
	.read    = memory_read,
	.write   = memory_write,
	.open    = memory_open,
	.release = memory_release,
};

static int __init memory_init(void)
{
	int ret;

	ret = register_chrdev(MEMORY_MAJOR, "memory", &memory_fops);
	if (ret < 0) {
		pr_err("memory: cannot obtain major number %d\n", MEMORY_MAJOR);
		return ret;
	}

	memory_buffer = kmalloc(1, GFP_KERNEL);
	if (!memory_buffer) {
		ret = -ENOMEM;
	}
	memset(memory_buffer, 0, 1);
	pr_info("Inserted memory module\n");

	return 0;
}

static void __exit memory_exit(void)
{
	unregister_chrdev(MEMORY_MAJOR, "memory");

	if (memory_buffer)
		kfree(memory_buffer);

	pr_info("Removing memory module\n");
}

module_init(memory_init);
module_exit(memory_exit);

MODULE_AUTHOR("YogaPan <godhand1234567@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Driver practice");
