/*  
 *  hello-param.c - The simplest kernel module.
 */
#include <linux/module.h>	   /* Needed by all modules */
#include <linux/kernel.h>	   /* Needed for KERN_INFO */
#include <linux/moduleparam.h> /* Needed for module_param() */ 
#include <linux/init.h>        /* Needed for __init, __initdata and __exit macros */
#include <linux/stat.h>        /* Needed for module_param() permission value */ 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Noa");

static int hello_time = 1;
static char *whom = "World";

static int myintArray[2] = { -5, 61 };
static int arr_argc = 0;

/* 
 * module_param(foo, int, 0000)
 * The first param is the parameters name
 * The second param is it's data type
 * The final argument is the permissions bits, 
 * for exposing parameters in sysfs (if non-zero) at a later stage.
 */

module_param(hello_time, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(hello_time, "How many times will display hello");

module_param(whom, charp, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(whom, "To Whom say hello");

/*
 * module_param_array(name, type, num, perm);
 * The first param is the parameter's (in this case the array's) name
 * The second param is the data type of the elements of the array
 * The third argument is a pointer to the variable that will store the number 
 * of elements of the array initialized by the user at module loading time
 * The fourth argument is the permission bits
 */

module_param_array(myintArray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintArray, "An array of integers");

int init_module(void)
{
    int i;
    for (i = 0; i <= (hello_time - 1); i++)
    {
	   printk(KERN_INFO "Hello %s 1.\n",whom);
    }

    for (i = 0; i <= (sizeof myintArray / sizeof (int)); i++);
    {
        printk(KERN_INFO "Array[%d] = %d.\n",i,myintArray[i]);
    }
    
	/* 
	 * A non 0 return means init_module failed; module can't be loaded. 
	 */
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}
