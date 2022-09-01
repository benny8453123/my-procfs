/* For using seq file api */
#include <linux/seq_file.h>
#include "my-procfs.h"

struct proc_dir_entry *my_seq_proc_entry = NULL;

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
	my_procfs_info("%s: creating seq entry\n", __func__);
	
	my_seq_proc_entry = proc_create(PROC_SEQ_ENTRY_NAME, 0644, NULL, &my_seq_proc_ops);

	if (!my_seq_proc_entry) {
		my_procfs_err("%s: creating seq file failed\n", __func__);
		return -ENOMEM;
	}

	return 0;
}

void remove_my_seq_proc_entry(void)
{
	remove_proc_entry(PROC_SEQ_ENTRY_NAME, NULL);

	return;
}

