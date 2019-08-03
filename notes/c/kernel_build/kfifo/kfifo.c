#include <linux/init.h>
#include <linux/module.h>
#include <linux/kfifo.h>

#define FIFO_SIZE 32
#define BUF_SIZE 64

static struct kfifo fifo;
static char buffer[BUF_SIZE];

static int __init queue_init(void)
{
	int          i;
	unsigned int ret;
	unsigned int val;

	printk(KERN_INFO "FIFO start\n");

	if (kfifo_alloc(&fifo, FIFO_SIZE, GFP_KERNEL)) {
		printk(KERN_WARNING "error kfifo\n");
		return -ENOMEM;
	}

	printk(KERN_INFO "queue size: %u\n", kfifo_size(&fifo));

	kfifo_in(&fifo, "test", 4);

	for (i = 0; i < 4; i++)
		kfifo_in(&fifo, &i, sizeof(i));

	ret = kfifo_out(&fifo, buffer, 4);
	if (ret != 4)
		return -EINVAL;
	printk(KERN_INFO "%s\n", buffer);

	printk(KERN_INFO "queue len: %u\n", kfifo_len(&fifo));

	while (!kfifo_is_empty(&fifo)) {
		ret = kfifo_out(&fifo, &val, sizeof(val));
		if (ret != sizeof(val))
			return -EINVAL;
		printk(KERN_INFO "%u\n", val);
	}

	return 0;
}

static void __exit queue_exit(void)
{
	kfifo_free(&fifo);
	printk(KERN_INFO "FIFO end\n");
}

module_init(queue_init);
module_exit(queue_exit);

MODULE_AUTHOR("YogaPan <godhand1234567@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Queue");
