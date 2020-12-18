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

struct task_struct *proceso;
#define BUFSIZE 150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Informacion procesos de cpu");
MODULE_AUTHOR("Mario Enrique Urbina");

static int escritura_arch(struct seq_file * archivo, void *v){
	for_each_process(proceso){
		seq_printf(archivo,"PID : \t%d \n",proceso->pid);
		seq_printf(archivo,"Nombre : \t%s \n",proceso->comm);
		seq_printf(archivo,"Estado : \t%ld \n",proceso->state);
		seq_printf(archivo,"----------------------------------\n");
	}
	return 0;
}

static int empiezo(struct inode *inode, struct file *file){
	return single_open(file,escritura_arch, NULL);
}

static struct file_ope operaciones ={
	.open = empiezo,
	.read = seq_read
};

static int inicio(void){
	proc_create("cpu_201313939", 0, NULL, &operaciones);
	printk(KERN_INFO "Mario Enrique Urbina Juarez\n");
	return 0;  
}

static void salgo(void){
	remove_proc_entry("cpu_201313939", NULL);
	printk(KERN_INFO "Sistemas Operativos 1\n");
		
}

module_init(inicio);
module_exit(salgo);
