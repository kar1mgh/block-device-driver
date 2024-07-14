#include <linux/module.h>
#include <linux/moduleparam.h>
// #include <linux/blkdev.h>

static char *blkdev_name; 

static int __init blkdev_driver_init(void)
{
	pr_info("driver init\n");

	return 0;
}

static void __exit blkdev_driver_exit(void)
{
	pr_info("driver exit\n");
}

// static int driver_module_blkdev_name_set(const char *arg, const struct kernel_param *kp)
// {
// 	ssize_t len = strlen(arg) + 1;

// 	if (device_name) {
// 		kfree(device_name);
// 		device_name = NULL;
// 	}
	
// 	device_name = kzalloc(sizeof(char) * len, GFP_KERNEL);
// 	if (!device_name)
// 		return -ENOMEM;
// 	strcpy(device_name, arg);
	
// 	return 0;
// }

// static int driver_module_blkdev_name_get(char *buf, const struct kernel_param *kp)
// {
// 	ssize_t len;

// 	if (!device_name)
// 		return -EINVAL;
// 	len = strlen(device_name);

// 	strcpy(buf, device_name);

// 	return len;
// }

// static const struct kernel_param_ops driver_module_device_name_ops = {
// 	.set = driver_module_device_name_set,
// 	.get = driver_module_device_name_get,
// };

// static int driver_module_execute_command_set(const char *command, const struct kernel_param *kp)
// {
// 	switch {
//         case strcmp(command, "open"):
            
//             break;
        
//         case strcmp(command, "close"):

//             break;

//         case strcmp(command "get name"):
//             pr_warn(device_name, "\n")
//             break;
        
//         default:
//             return -EINVAL;
//             break;
//     }

// 	return 0;
// }

// static const struct execute_command_ops driver_module_execute_command_ops = {
// 	.set = driver_module_execute_command_set,
// 	.get = NULL,
// };

MODULE_PARM_DESC(device_name, "Device name");
module_param_named(device_name, blkdev_name, charp, S_IRUGO | S_IWUSR);

// MODULE_PARM_DESC(execute_command, "Execute_command");
// module_param_cb(execute_command, &driver_module_execute_command_ops, NULL, S_IWUSR);

module_init(driver_init);
module_exit(driver_exit);

MODULE_AUTHOR("Karim Shakirov <karimshak06@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Block device driver");
