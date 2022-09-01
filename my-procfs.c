#include <linux/module.h>
#include "my-procfs.h"

static int __init my_procfs_init(void)
{
	int ret = 0;

	my_procfs_info("Enter %s\n", __func__);

	/* create seq file in proc */
	ret = create_my_seq_proc_entry();
	if (ret != 0)
		goto remove_seq_file;

	/* create dir in proc */
	ret = create_my_dir_proc_entry();
	if (ret != 0)
		goto remove_dir_file;

	/* all thing created successfully goto out and return 0 */
	goto out;

remove_dir_file:
	/* nothing to do */
remove_seq_file:
	remove_proc_entry(PROC_SEQ_ENTRY_NAME, NULL);
out:
	return ret;
}

static void __exit my_procfs_exit(void)
{
	my_procfs_info("Enter %s\n", __func__);
	
	remove_proc_entry(PROC_DIR_ENTRY_NAME, NULL);
	remove_proc_entry(PROC_SEQ_ENTRY_NAME, NULL);
	
	return; 
}

module_init(my_procfs_init);
module_exit(my_procfs_exit);

MODULE_LICENSE("GPLv2");
MODULE_AUTHOR("Ben Chang");
MODULE_DESCRIPTION("Testing for procfs");
