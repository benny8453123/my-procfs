/* Using for kmalloc/kfree */
#include <linux/slab.h>
#include "my-procfs.h"

#define MY_DATA_IN_DIR_NAME	"my-data"
#define BUF_SIZE 		64

struct proc_dir_entry *my_dir_proc_entry = NULL;
struct proc_dir_entry *my_data_in_dir = NULL;
static char *strbuf = NULL;

/* Reference to /kernel/irq/proc.c */
ssize_t my_data_read(struct file *file, char __user *buf, size_t count, loff_t *lof)
{
	int len;

	if (!strbuf) {
		my_procfs_err("%s: write buffer address not exist\n", __func__);
		return -EFAULT;
	}

	len = strlen(strbuf) + 1;

	if(*lof == len) {
		return 0;
	}

	if (copy_to_user(buf, strbuf, strlen(strbuf) + 1))
		return -EFAULT;

	*lof += len;

	return len;
}

ssize_t my_data_write(struct file *file, const char __user *buf, size_t count, loff_t *lof)
{
	if (!strbuf) {
		my_procfs_err("%s: write buffer address not exist\n", __func__);
		return -EFAULT;
	}

	if (count > BUF_SIZE) {
		my_procfs_err("%s: write string size is exceed buffer size\n", __func__);
		return 0;
	}

	memset(strbuf, 0, BUF_SIZE);
	if (copy_from_user(strbuf, buf, count))
		return -EFAULT;

	*lof += count;

	return count;
}

static int my_data_open(struct inode *inode, struct file *file)
{
	/* make kernel account that this module is being
	 * need include linux/module.h
	 */
	try_module_get(THIS_MODULE);
	return 0;
}

static int my_data_release(struct inode *inode, struct file *file)
{
	/* make kernel accout that this module is not being used
	 * need include linux/module.h
	 */
	module_put(THIS_MODULE);
	return 0;
}

static const struct proc_ops my_data_ops = {
	.proc_write = my_data_write,
	.proc_read = my_data_read,
	.proc_open = my_data_open,
	.proc_release = my_data_release,
};

int create_data_in_dir_proc_entry(void)
{
	my_procfs_info("%s: creating data in dir entry\n", __func__);

	/* create data in dir */
	my_data_in_dir = proc_create_data(MY_DATA_IN_DIR_NAME, 0644, my_dir_proc_entry, &my_data_ops, NULL);
	if (!my_data_in_dir) {
		my_procfs_err("%s: creating data in dir failed\n", __func__);
		return -ENOMEM;
	}

	/* alloc write & read buffer */
	strbuf = kmalloc(BUF_SIZE, GFP_KERNEL);
	if (!strbuf) {
		my_procfs_err("%s: alloc data buffer failed\n", __func__);

		remove_proc_entry(MY_DATA_IN_DIR_NAME, my_dir_proc_entry);
		return -ENOMEM;
	}

	memset(strbuf, 0, BUF_SIZE);

	return 0;
}

int create_my_dir_proc_entry(void)
{
	my_procfs_info("%s: creating dir entry\n", __func__);

	my_dir_proc_entry = proc_mkdir(PROC_DIR_ENTRY_NAME, NULL);
	if (!my_dir_proc_entry) {
		my_procfs_err("%s: creating dir file failed\n", __func__);
		return -ENOMEM;
	}

	/* create a file in dir */
	if (create_data_in_dir_proc_entry() != 0) {
		remove_proc_entry(PROC_DIR_ENTRY_NAME, NULL);
		return -ENOMEM;
	}

	return 0;
}

void remove_my_dir_proc_entry(void)
{
	kfree(strbuf);
	remove_proc_entry(MY_DATA_IN_DIR_NAME, my_dir_proc_entry);
	remove_proc_entry(PROC_DIR_ENTRY_NAME, NULL);

	return;
}
