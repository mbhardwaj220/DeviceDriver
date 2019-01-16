// simple kernel painc program to see what happen when kernel panic

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL");

static int test_init(void)
{
  printk(KERN_ALERT "%s in Init func\n",__func__);
  panic("panic from init func Test\n");
  return 0;
}

static void test_exit(void)
{
  printk(KERN_ALERT "%s : in Exit func\n",__func__);
}

module_init(test_init);
module_exit(test_exit);
