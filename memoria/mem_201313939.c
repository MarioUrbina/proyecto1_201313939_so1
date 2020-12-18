#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>

#define BUFSIZE 150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Informacion de memoria RAM");
MODULE_AUTHOR("Mario Enrique Urbina");

struct sysinfo inf;

static int escribir_archivo(struct seq_file * archivo, void *v){
	si_meminfo(&inf);
	long total_mem = (inf.totalram * 4);
	long mem_libre = (inf.freeram * 4);
	
	seq_printf(archivo, " Memoria Total: \t %8lu KB- %8lu MB\n",total_mem, total_mem / 1024);
	seq_printf(archivo, " Memoria Libre: \t %8lu KB- %8lu MB\n",mem_libre, mem_libre / 1024);
	seq_printf(archivo, " Memoria en uso: \t %i %%\n",(mem_libre * 100) /total_mem );
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
    printk(KERN_INFO "201313939\n");
    return 0;
}
 
static void salir(void)
{
    remove_proc_entry("cpu_201313939", NULL);
    printk(KERN_INFO "Sistemas Operativos 1\n");
}
 
module_init(iniciar);
module_exit(salir); 
