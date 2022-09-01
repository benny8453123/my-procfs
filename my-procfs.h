#ifndef MY_PROCFS_H
#define MY_PROCFS_H

#include <linux/printk.h>
#include <linux/kernel.h>

#define my_procfs_info(fmt, ...) \
	pr_info("[my_procfs]: "fmt, ##__VA_ARGS__)

#define my_procfs_err(fmt, ...) \
	pr_err("[my_procfs]: "fmt, ##__VA_ARGS__)

#define my_procfs_debug(fmt, ...) \
	pr_debug("[my_procfs]: "fmt, ##__VA_ARGS__)



#endif /* MY_PROCFS_H */
