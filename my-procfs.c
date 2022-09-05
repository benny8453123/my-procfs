#include "my-procfs.h"

static int __init my_procfs_init(void)
{
	int ret = 0;

	my_procfs_info("Enter %s\n", __func__);

	/* create seq file in proc */
	ret = create_my_seq_proc_entry();
	if (ret != 0)
		goto out;

	/* create dir in proc */
	ret = create_my_dir_proc_entry();
	if (ret != 0)
		goto remove_seq_file;

	/* create seq buf file */
	ret = create_my_seq_buf_proc_entry();
	if (ret != 0)
		goto remove_dir_file;

	/* all thing created successfully goto out and return 0 */
	goto out;

remove_seq_buf_file:
	remove_my_seq_buf_proc_entry();
remove_dir_file:
	remove_my_dir_proc_entry();
remove_seq_file:
	remove_my_seq_proc_entry();
out:
	return ret;
}

static void __exit my_procfs_exit(void)
{
	my_procfs_info("Enter %s\n", __func__);
	
	remove_my_seq_buf_proc_entry();
	remove_my_dir_proc_entry();
	remove_my_seq_proc_entry();
	
	return; 
}

module_init(my_procfs_init);
module_exit(my_procfs_exit);

MODULE_LICENSE("GPLv2");
MODULE_AUTHOR("Ben Chang");
MODULE_DESCRIPTION("Testing for procfs");
