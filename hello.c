// simple c program to make a simple file_system read using proc
// read only module
// u can see values of read :  cat /proc/<name>
// here name is cat /proc/tlc_proc_a
// u can give any name
// to write use echo
// echo "helloamfromuserspace" > /proc/tlc_proc_a

#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h> /* Necessary because we use the proc fs */
#include <asm/types.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>
MODULE_LICENSE("GPL");
struct proc_dir_entry *tlc_proc_a;
#define MAXLEN 30
int abc =100;
char proc_buf[MAXLEN]="default";


static ssize_t tlc_proc_a_write(struct file *fp,const char *buf, size_t len, loff_t *off)
{
  if(len> MAXLEN)
  {
    return -EFAULT;
  }
  if(raw_copy_from_user(proc_buf,buf,len))
  {
    return -EFAULT;
  }
  //abc = simple_strtoul(proc_buf,NULL,10);  this func convert string into int

  //strcpy(proc_buf,"MUNISH MY FILE SYSYEM\n");

  return len;
}

static ssize_t tlc_proc_a_read(struct file *fp, char *buf, size_t len, loff_t *off)
{
  static int finished =0;
  if(finished)
  {
    finished =0;
    return 0;
  }
  finished=1;

  //strcpy(buf, "HELLO MUNISH BHARDWAJ :: MY FILE SYSYEM\n");
   sprintf(buf,"sprintf %s\n",proc_buf);
  // strcpy(buf,proc_buf);
  return strlen(buf);
}

static struct file_operations tlc_proc_a_fops ={.owner = THIS_MODULE, .read=tlc_proc_a_read, .write = tlc_proc_a_write,};

static int hello_init(void)
{
  printk(KERN_INFO "%s: in Func INIT \n",__func__);
  tlc_proc_a = proc_create("tlc_proc_a", 0666, NULL, &tlc_proc_a_fops); // 0666 for read write permision 0444 for only read
  if(tlc_proc_a == NULL)
  {
    printk(KERN_ALERT "ERROR : Could not initialize %s\n","tlc_proc_a");
  }
  return 0;
}

static void hello_exit(void)
{
  remove_proc_entry("tlc_proc_a", NULL);
  printk(KERN_INFO "%s in func EXIT \n",__func__);
}

module_init(hello_init);
module_exit(hello_exit);
