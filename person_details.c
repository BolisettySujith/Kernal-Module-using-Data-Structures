#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
 

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("A Simple LinkedList Implementation in Kernel");
MODULE_AUTHOR("Bolisetty Sujith");

struct Person {

    char name[30];
    unsigned int weight;
    unsigned int height;
    unsigned char gender;
    struct list_head list;/* kernel's list structure */

};


struct Person personList;

#define ARRAY_LEN 3
#define STRING_LEN 40

int array_len;

static char *person1_name;
module_param(person1_name, charp, 0644);

static int person1_details[ARRAY_LEN];
module_param_array(person1_details, int, &array_len, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(person1_details, "Integer array for doing nothing");

static char *person2_name;
module_param(person2_name, charp, 0644);

static int person2_details[ARRAY_LEN];
module_param_array(person2_details, int, &array_len, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(person2_details, "Integer array for doing nothing");


int init_module() {

    struct Person *aNewPerson, *aPerson;

    printk(KERN_INFO "!! Kernel module Initialized !!\n");

    INIT_LIST_HEAD(&personList.list);   //or LIST_HEAD(mylist); 

    printk(KERN_INFO "Adding %s data to the Linked List\n", person1_name);
 	//1st person
 	aNewPerson = kmalloc(sizeof(*aNewPerson), GFP_KERNEL);
    strcpy(aNewPerson->name, person1_name);
    aNewPerson->weight = person1_details[0];
    aNewPerson->height = person1_details[1];
    aNewPerson->gender = person1_details[2];
    INIT_LIST_HEAD(&aNewPerson->list);
    
   /* add the new node to mylist */
    list_add_tail(&(aNewPerson->list), &(personList.list));
    printk(KERN_INFO "Succesfully, added %s data to the Linked List\n", person1_name);
    
    
 	//2rd person
 	printk(KERN_INFO "Adding %s data to the Linked List\n", person2_name);
 	aNewPerson = kmalloc(sizeof(*aNewPerson), GFP_KERNEL);
    strcpy(aNewPerson->name, person2_name);
    aNewPerson->weight = person2_details[0];
    aNewPerson->height = person2_details[1];
    aNewPerson->gender = person2_details[2];
    INIT_LIST_HEAD(&aNewPerson->list);
    
   /* add the new node to mylist */
    list_add_tail(&(aNewPerson->list), &(personList.list));
   	printk(KERN_INFO "Succesfully, added %s data to the Linked List\n", person2_name);
    
    //Traversal
    printk(KERN_INFO "The Data in the Linked List\n");

    list_for_each_entry(aPerson, &personList.list, list) {
	   	//access the member from aPerson
	    printk(KERN_INFO "Person Name: %s \n Weight: %d\n Height: %d\n Gender: %s\n", aPerson->name, aPerson->weight,aPerson->height, aPerson->gender==0?"Female":"Male");
    }
	
    return 0;
}

 
void cleanup_module() {

    struct Person *aPerson, *tmp;
    printk(KERN_INFO "!! Deleting the Linked List !!\n");
    list_for_each_entry_safe(aPerson, tmp, &personList.list, list){

         printk(KERN_INFO "Freeing node %s\n", aPerson->name);

         list_del(&aPerson->list);

         kfree(aPerson);

    }
    printk(KERN_INFO "!! kernel Module unloaded !!\n");

}
