#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

dev_t devno;
int major = 255;
const char DEVNAME[] = "hust_device";
int write_num[2];
int read_num;
int hust_open(struct inode * ip, struct file * fp)
{
    printk("%s : %d\n", __func__, __LINE__);
    
    /* 一般用来做初始化设备的操作 */
    return 0;
}

int hust_close(struct inode * ip, struct file * fp)
{
    printk("%s : %d\n", __func__, __LINE__);
    
    /* 一般用来做和open相反的操作，open申请资源，close释放资源 */
    return 0;
}

ssize_t hust_read(struct file * fp, char __user * buf, size_t count, loff_t * loff)
{
    int ret;
    printk("%s : %d\n", __func__, __LINE__);
    if(write_num[0]>write_num[1])
    	read_num = write_num[0];
    else
    	read_num = write_num[1];
    if ((ret = copy_to_user(buf, &read_num, count)))
    {
        printk("copy_to_user err\n");
        return -1;
    }
    printk("两数中较大的一个为%d",read_num);
    return count;
}

ssize_t hust_write(struct file * fp, const char __user * buf, size_t count, loff_t * loff)
{
    int ret;
    printk("%s : %d\n", __func__, __LINE__);
    if ((ret = copy_from_user(write_num, buf, count)))
    {
        printk("copy_from_user err\n");
        return -1;
    }
    printk("写入两个数:%d,%d",write_num[0],write_num[1]);
    return count;
}

//分配file_operations结构体
struct file_operations hust_fops = {
    .owner = THIS_MODULE,
    .open  = hust_open,
    .release = hust_close,
    .read = hust_read,
    .write = hust_write
};
struct cdev cdev;

//开始
static int hust_init(void)
{
    int ret;
    printk("%s : %d\n", __func__, __LINE__);
    
    //生成并注册设备号
    devno = MKDEV(major, 0);
    ret  = register_chrdev_region(devno, 1, DEVNAME);
    if (ret != 0)
    {
        printk("%s : %d fail to register_chrdev_region\n", __func__, __LINE__);
        return -1;
    }
    
    //分配、设置、注册cdev结构体 */
    cdev.owner = THIS_MODULE;
    ret = cdev_add(&cdev, devno, 1);
    cdev_init(&cdev, &hust_fops);
    if (ret < 0)
    {
        printk("%s : %d fail to cdev_add\n", __func__, __LINE__);
        return -1;
    }
    printk("register successfully!\n");
    return 0;
}

//结束
static void hust_exit(void)
{
    printk("%s : %d\n", __func__, __LINE__);
    //释放资源
    cdev_del(&cdev);
    unregister_chrdev_region(devno, 1);
}

MODULE_LICENSE("GPL");
module_init(hust_init);
module_exit(hust_exit);

