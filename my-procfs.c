#include <linux/module.h>
#include "my-procfs.h"

static int __init my_procfs_init(void)
{
	my_procfs_info("Enter %s\n", __func__);
	return 0;
}

static void __exit my_procfs_exit(void)
{
	my_procfs_info("Enter %s\n", __func__);
	return; 
}

module_init(my_procfs_init);
module_exit(my_procfs_exit);

MODULE_LICENSE("GPLv2");
MODULE_AUTHOR("Ben Chang");
MODULE_DESCRIPTION("Testing for procfs");
