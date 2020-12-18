#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/sched/signal.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

struct task_struct  *proceso;

#define BUFSIZE     150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Informacion procesos de cpu");
MODULE_AUTHOR("Mario Enrique Urbina");

static int escribir_archivo(struct seq_file * archivo, void *v) {
    for_each_process(proceso){            
	seq_printf(archivo, " PID   : \t%d \n", proceso->pid); 
        seq_printf(archivo, " Nombre: \t%s \n", proceso->comm); 
        seq_printf(archivo, " Estado: \t%ld \n", proceso->state);
        seq_printf(archivo, "---------------------------------\n"); 		 
	} 
    return 0;
}


static int al_abrir(struct inode *inode, struct  file *file) {
  return single_open(file, escribir_archivo, NULL);
}

static struct file_operations operaciones =
{        
    .open = al_abrir,
    .read = seq_read
};


static int iniciar(void)
{
    proc_create("cpu_201313939", 0, NULL, &operaciones);
    printk(KERN_INFO "Mario Enrique Urbina\n");
    return 0;
}
 
static void salir(void)
{
    remove_proc_entry("cpu_201313939", NULL);
    printk(KERN_INFO "Diciembre 2020\n");
}
 
module_init(iniciar);
module_exit(salir); 
