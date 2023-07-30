#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello world with nf_register_hook");

static unsigned int my_hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    int i;
    for (i = 0; i < 10; ++i) {
        printk(KERN_INFO "Hello world\n");
    }
    return NF_ACCEPT;
}

static struct nf_hook_ops my_hook = {
    .hook = my_hook_func,
    .hooknum = NF_INET_PRE_ROUTING,
    .pf = NFPROTO_IPV4,
    .priority = NF_IP_PRI_FIRST,
};

static int __init hello_init(void) {
    int ret = nf_register_hook(&my_hook);
    if (ret < 0) {
        printk(KERN_ERR "Failed to register netfilter hook\n");
        return ret;
    }

    printk(KERN_INFO "Module loaded\n");
    return 0;
}

static void __exit hello_exit(void) {
    nf_unregister_hook(&my_hook);
    printk(KERN_INFO "Module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
