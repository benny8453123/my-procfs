/* For using seq file api */
#include <linux/seq_file.h>
/* For using kmalloc/kfree */
#include <linux/slab.h>
#include "my-procfs.h"

enum {
	CUR_INIT = -1,
	CUR_END = -2,
	CUR_MAX, 
};

struct proc_dir_entry *my_seq_buf_proc_entry = NULL;
static char *seq_buf[] = {"This", "is", "seq buf"};
static int cur_p = CUR_INIT;
int size = sizeof(seq_buf) / sizeof(char *);

/* Reference to /drivers/pci/proc.c */
static int my_seq_buf_proc_show(struct seq_file *file, void *v)
{
	int *cur;

	if (v) {	
		cur = (int *)v;

		my_procfs_info("%s: cur_p = %d\n", __func__, cur_p);
	
		if (*cur > CUR_INIT && *cur < size)
		{
			seq_putc(file, '0' + *cur);
			seq_puts(file, ":\t");
			seq_puts(file, *(seq_buf + *cur));
			seq_putc(file, '\n');
		}
	}

	return 0;
}

static void my_seq_buf_proc_stop(struct seq_file *file, void *v)
{
	my_procfs_info("%s: cur_p = %d\n", __func__, cur_p);

	my_procfs_info("%s: v = %lld\n", __func__, (u64)v);
	/* if arrive here, it means next return NULL and v will be NULL */
	cur_p = CUR_END;
}

static void *my_seq_buf_proc_next(struct seq_file *file, void *v, loff_t *pos)
{
	int *p;
	
	my_procfs_info("%s: cur_p = %d\n", __func__, cur_p);

	(*pos)++;
	if (v) {
		p = (int *)v;
		(*p)++;

		if (*p < size)
			return p;
	}

	return NULL;
}

static void *my_seq_buf_proc_start(struct seq_file *file, loff_t *pos)
{
	my_procfs_info("%s: cur_p = %d\n", __func__, cur_p);

	/* stop reading */
	if (cur_p == CUR_END) {
		cur_p = CUR_INIT;
		*pos = 0;
		return NULL;
	}

	if (cur_p == CUR_INIT)
		cur_p = 0;

	return &cur_p;
}

static const struct seq_operations my_seq_buf_proc_ops = {
	.start = my_seq_buf_proc_start,
	.next = my_seq_buf_proc_next,
	.stop = my_seq_buf_proc_stop,
	.show = my_seq_buf_proc_show,
};


int create_my_seq_buf_proc_entry(void)
{
	my_procfs_info("%s: creating seq buf entry\n", __func__);
	
	my_seq_buf_proc_entry = proc_create_seq(PROC_SEQ_BUF_ENTRY_NAME, 0644, NULL, &my_seq_buf_proc_ops);

	if (!my_seq_buf_proc_entry) {
		my_procfs_err("%s: creating seq buf file failed\n", __func__);
		return -ENOMEM;
	}

	return 0;
}

void remove_my_seq_buf_proc_entry(void)
{
	remove_proc_entry(PROC_SEQ_BUF_ENTRY_NAME, NULL);

	return;
}

