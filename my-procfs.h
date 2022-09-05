#ifndef MY_PROCFS_H
#define MY_PROCFS_H

#include <linux/printk.h>
#include <linux/kernel.h>
/* For using proc fs api */
#include <linux/proc_fs.h>
/* Using for module api and try_module_get/module_put */
#include <linux/module.h>

#define my_procfs_info(fmt, ...) \
	pr_info("[my_procfs]: "fmt, ##__VA_ARGS__)

#define my_procfs_err(fmt, ...) \
	pr_err("[my_procfs]: "fmt, ##__VA_ARGS__)

#define my_procfs_debug(fmt, ...) \
	pr_debug("[my_procfs]: "fmt, ##__VA_ARGS__)


#define PROC_SEQ_ENTRY_NAME 	"my-proc-seq"
#define PROC_DIR_ENTRY_NAME	"my-proc-dir"


int create_my_seq_proc_entry(void);
void remove_my_seq_proc_entry(void);

int create_my_dir_proc_entry(void);
void remove_my_dir_proc_entry(void);

#endif /* MY_PROCFS_H */
