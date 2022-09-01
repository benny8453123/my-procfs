#include <linux/module.h>
/* For using proc fs api */
#include <linux/proc_fs.h>
/* For using seq file api */
#include <linux/seq_file.h>
#include "my-procfs.h"

#define PROC_SEQ_ENTRY_NAME 	"my-proc-seq"

/* Reference to /fs/proc/stat.c */
static int print_seq_message(struct seq_file *p, void *v)
{
	seq_puts(p, "This is ");
	seq_puts(p, PROC_SEQ_ENTRY_NAME);
	seq_putc(p, '\n');

	return 0;
}

static int my_seq_proc_open(struct inode *inode, struct file *file)
{
	unsigned int size = sizeof(PROC_SEQ_ENTRY_NAME);

	return single_open_size(file, print_seq_message, NULL, size);
}

static const struct proc_ops my_seq_proc_ops = {
	.proc_open = my_seq_proc_open,
	.proc_read_iter = seq_read_iter,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};


int create_my_seq_proc_entry(void)
{
	my_procfs_info("%s: creating proc entry\n", __func__);
	
	proc_create(PROC_SEQ_ENTRY_NAME, 0644, NULL, &my_seq_proc_ops);

	return 0;
}

static int __init my_procfs_init(void)
{
	int ret = 0;

	my_procfs_info("Enter %s\n", __func__);

	ret = create_my_seq_proc_entry();

	

	return ret;
}

static void __exit my_procfs_exit(void)
{
	my_procfs_info("Enter %s\n", __func__);
	
	remove_proc_entry(PROC_SEQ_ENTRY_NAME, NULL);
	
	return; 
}

module_init(my_procfs_init);
module_exit(my_procfs_exit);

MODULE_LICENSE("GPLv2");
MODULE_AUTHOR("Ben Chang");
MODULE_DESCRIPTION("Testing for procfs");
