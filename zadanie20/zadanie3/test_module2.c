#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/proc_fs.h>
#include<linux/rwlock.h>
#include<linux/uaccess.h>

static int major = 0;
static rwlock_t lock;
static char test_string[15] = "Hello!\0";
static struct proc_dir_entry *test;
static struct kobject *test_kobj;

ssize_t test_read(struct file *fd, char __user *buff, size_t size, loff_t *off)
{
	size_t rc;

	read_lock(&lock);
	rc = simple_read_from_buffer(buff, size, off, test_string, 15);
	read_unlock(&lock);

	return rc;
}

ssize_t test_write(struct file *fd, const char __user *buff, size_t size, loff_t *off)
{
	size_t rc = 0;
	if(size > 15)
		return -EINVAL;
	
	write_lock(&lock);
	rc = simple_write_to_buffer(test_string, 15, off, buff, size);
	write_unlock(&lock);

	return rc;
}

ssize_t test_proc_read(struct file *fd, char __user *buff, size_t size, loff_t *off)
{
	size_t rc = 0;

	rc = simple_read_from_buffer(buff, size, off, test_string, 15);

	return rc;
}


ssize_t test_proc_write(struct file *fd, const char __user *buff, size_t size, loff_t *off)
{
	size_t rc = 0;

	rc = simple_write_to_buffer(test_string, 15, off, buff, size);

	return rc;
}

static ssize_t string_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	size_t rc = 0;
	memcpy(buf, test_string, 15);
	rc = strlen(test_string);
	return rc;
}

static ssize_t string_store(struct kobject *kobj, struct kobj_attribute *attr, char const *buf, size_t count)
{
	size_t rc = 0;
	memcpy(test_string, buf, count);
	rc = strlen(buf);
	return rc;
}

static struct file_operations fops = {
	.owner = THIS_MODULE,
	.read = test_read,
	.write = test_write
};

static const struct proc_ops pops = {
	.proc_read = test_proc_read,
	.proc_write = test_proc_write,
};

static struct kobj_attribute string_attribute = 
	__ATTR(test_string, 0644, string_show, string_store);

static struct attribute *attrs[ ] = {
	&string_attribute.attr,
	NULL,
};

static struct attribute_group attr_group = {
	.attrs = attrs,
};

int init_module(void)
{
	int retval = 0;
	pr_info("Module loaded!!!!!\n");
	rwlock_init(&lock);
	major = register_chrdev(major, "test_module2", &fops);

	if(major < 0)
		return major;
	pr_info("Major number is %d.\n", major);
	
	test = proc_create("test", 0666, NULL, &pops);

	test_kobj = kobject_create_and_add("kobject_test", kernel_kobj);

	if(!test_kobj) return -ENOMEM;

	retval = sysfs_create_group(test_kobj, &attr_group);

	if(retval) {
		kobject_put(test_kobj);
		return retval;
	}

	return 0;
}


void cleanup_module(void)
{
	unregister_chrdev(major, "test_module2");
	proc_remove(test);
	kobject_put(test_kobj);
	pr_info("Module unloaded!!!!!\n");
}


MODULE_LICENSE("GPL");



