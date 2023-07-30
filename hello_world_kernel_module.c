#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello world with nf_register_hook");

// The function that will be executed when a packet passes through the hook
static unsigned int my_hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    int i;
    for (i = 0; i < 10; ++i) {
        printk(KERN_INFO "Hello world\n"); // Print "Hello world" message to the kernel log 10 times
    }
    return NF_ACCEPT; // Accept the packet and let it continue through the network stack
}

// Structure that defines the hook parameters
static struct nf_hook_ops my_hook = {
    .hook = my_hook_func,             // Pointer to the hook function
    .hooknum = NF_INET_PRE_ROUTING,   // Hook into the pre-routing stage of IPv4 packets
    .pf = NFPROTO_IPV4,               // IPv4 protocol family
    .priority = NF_IP_PRI_FIRST,      // Highest priority for the hook (runs first)
};

// Module initialization function
static int __init hello_init(void) {
    int ret = nf_register_net_hook(&init, &my_hook); // Register the hook with Netfilter framework
    if (ret < 0) {
        printk(KERN_ERR "Failed to register netfilter hook\n"); // Print an error message if registration fails
        return ret; // Return the error code to indicate module loading failure
    }

    printk(KERN_INFO "Module loaded\n"); // Print a message indicating successful module loading
    return 0; // Return 0 to indicate successful module loading
}

// Module exit function
static void __exit hello_exit(void) {
    nf_unregister_net_hook(&init, &my_hook); // Unregister the hook from Netfilter framework
    printk(KERN_INFO "Module unloaded\n"); // Print a message indicating the module is being unloaded
}

module_init(hello_init); // Specify the module initialization function
module_exit(hello_exit); // Specify the module exit function
