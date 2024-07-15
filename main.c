#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/blkdev.h>

static char *blkdev_name;
static struct block_device *blkdev;  

static int __init blkdev_driver_init(void)
{
	pr_info("driver init\n");

	return 0;
}

static void __exit blkdev_driver_exit(void)
{
	if (!blkdev_name)
		kfree(blkdev_name);

	if (!blkdev)
		kfree(blkdev);

	pr_info("driver exit\n");
}

static int open_bdev(void)
{
	struct file *bdev_file = bdev_file_open_by_path(blkdev_name, BLK_OPEN_READ | BLK_OPEN_WRITE, NULL, NULL);
	
	if (IS_ERR(bdev_file))
		return PTR_ERR(bdev_file);

	blkdev = file_bdev(bdev_file);

	return 0;
}

static int close_bdev(void)
{
	if (!blkdev)
		return -EINVAL;
	
	kfree(blkdev);
	
	return 0;
}

static int driver_module_execute_command_set(const char *arg, const struct kernel_param *kp)
{
	if (!blkdev_name)
		return -EINVAL;

	int error = 0;

	if (!strcmp(arg, "open")) { 
		error = open_bdev();
	} else if (!strcmp(arg, "close")) {
		error = close_bdev();
	} else if (!strcmp(arg, "get name")) {
		if (!blkdev)
			return -EINVAL;

		pr_warn("%s\n", blkdev_name); // should work only if device is openned
	} else return -EINVAL;
    
	return 0;
}

static const struct kernel_param_ops driver_module_execute_command_ops = {
	.set = driver_module_execute_command_set,
	.get = NULL,
};

MODULE_PARM_DESC(execute_command, "Execute_command");
module_param_cb(execute_command, &driver_module_execute_command_ops, NULL, S_IWUSR);

MODULE_PARM_DESC(blkdev_name, "Block device name");
module_param_named(blkdev_name, blkdev_name, charp, S_IRUGO | S_IWUSR);

module_init(blkdev_driver_init);
module_exit(blkdev_driver_exit);

MODULE_AUTHOR("Karim Shakirov <karimshak06@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Block device driver");
