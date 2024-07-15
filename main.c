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

static int open_bdev(const char *arg, const struct kernel_param *kp)
{
	struct file *bdev_file = bdev_file_open_by_path(blkdev_name, BLK_OPEN_READ | BLK_OPEN_WRITE, NULL, NULL);
	
	if (IS_ERR(bdev_file))
		return PTR_ERR(bdev_file);

	blkdev = file_bdev(bdev_file);

	return 0;
}

static const struct kernel_param_ops driver_module_open_blkdev_ops = {
	.set = open_bdev,
	.get = NULL,
};

static int close_bdev(const char *arg, const struct kernel_param *kp)
{
	if (!blkdev)
		return -EINVAL;
	
	kfree(blkdev);
	
	return 0;
}

static const struct kernel_param_ops driver_module_close_blkdev_ops = {
	.set = close_bdev,
	.get = NULL,
};

static int get_name(const char *arg, const struct kernel_param *kp)
{
	if (!blkdev)
		return -EINVAL;

	pr_warn("%s\n", blkdev_name); // should work only if device is openned
	
	return 0;
}

static const struct kernel_param_ops driver_module_get_name_ops = {
	.set = get_name,
	.get = NULL,
};

MODULE_PARM_DESC(open_blkdev, "Open block device");
module_param_cb(open_blkdev, &driver_module_open_blkdev_ops, NULL, S_IWUSR);

MODULE_PARM_DESC(close_blkdev, "Close openned block device");
module_param_cb(close_blkdev, &driver_module_close_blkdev_ops, NULL, S_IWUSR);

MODULE_PARM_DESC(get_name, "Get openned block device name");
module_param_cb(get_name, &driver_module_get_name_ops, NULL, S_IWUSR);

MODULE_PARM_DESC(blkdev_name, "Block device name");
module_param_named(blkdev_name, blkdev_name, charp, S_IRUGO | S_IWUSR);

module_init(blkdev_driver_init);
module_exit(blkdev_driver_exit);

MODULE_AUTHOR("Karim Shakirov <karimshak06@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Block device driver");
