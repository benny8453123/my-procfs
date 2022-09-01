#include "my-procfs.h"

struct proc_dir_entry *my_dir_proc_entry = NULL;

/* Reference to /kernel/irq/proc.c */
int create_my_dir_proc_entry(void)
{
	my_procfs_info("%s: creating dir entry\n", __func__);

	my_dir_proc_entry = proc_mkdir(PROC_DIR_ENTRY_NAME, NULL);
	if (!my_dir_proc_entry) {
		my_procfs_err("%s: creating dir file failed\n", __func__);
		return -ENOMEM;
	}

	return 0;
}
