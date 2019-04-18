/**
 * @file    cs483hello.c
 * @author  Greg Brault
 * @date    13 April 2018
 * @version 0.1
 * @brief  An introductory "Hello World!" loadable kernel module (LKM) that can display a message
 * in the /var/log/kern.log file when the module is loaded and removed. The module can accept an
 * argument when it is loaded -- the name, which appears in the kernel log files.
*/
 
#include <linux/init.h>             // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>           // Core header for loading LKMs into the kernel
#include <linux/kernel.h>           // Contains types, macros, functions for the kernel
 
MODULE_LICENSE("GPL");              // The license type -- this affects runtime behavior
MODULE_AUTHOR("Greg Brault");       // The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux Loadable Kernel Module.");  // The description -- see modinfo
MODULE_VERSION("0.1");              // The version of the module
 
/** @brief The LKM initialization function
 *  The static keyword restricts the visibility of the function to within this C file. The __init
 *  macro means that for a built-in driver (not a LKM) the function is only used at initialization
 *  time and that it can be discarded and its memory freed up after that point.
 *  @return returns 0 if successful
 */
static int __init cs483hello_init(void){
   printk(KERN_INFO "CS483 Module: Hello from the LKM!\n");
   return 0;
}
 
/** @brief The LKM cleanup function
 *  Similar to the initialization function, it is static. The __exit macro notifies that if this
 *  code is used for a built-in driver (not a LKM) that this function is not required.
 */
static void __exit cs483hello_exit(void){
   printk(KERN_INFO "CS483 Module: Goodbye from the LKM!\n");
}
 
/** @brief A module must use the module_init() module_exit() macros from linux/init.h, which
 *  identify the initialization function at insertion time and the cleanup function (as
 *  listed above)
 */
module_init(cs483hello_init);
module_exit(cs483hello_exit);


