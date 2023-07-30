#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("BAN");
MODULE_DESCRIPTION("Hello world!");

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello world\n");
    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_INFO "bye bye world\n");
}

module_init(hello_init);
module_exit(hello_exit);
