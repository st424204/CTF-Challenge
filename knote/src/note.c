#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include "note.h"


static int drv_open(struct inode *inode, struct file *filp);
static long drv_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);


static struct file_operations drv_fops = {
	open : drv_open,
	unlocked_ioctl : drv_unlocked_ioctl
};


static struct miscdevice note_miscdev = {
    .minor      = 11,
    .name       = "note",
    .fops       = &drv_fops,
};


static void* my_alloc(size_t size){
	char* ret = pos;
	pos+=size;
	return ret;
}
static void my_clear(void){
	memset(mem,0,sizeof(mem));
	pos = mem;
}


static int drv_open(struct inode *inode, struct file *filp){
	return 0;
}


static long drv_unlocked_ioctl(struct file *filp, unsigned int cmd, unsigned long arg){
    int ret = 0 ,i = 0;
    uint64_t buf[0x20] ;
    uint64_t addr = 0;
    uint64_t size = 0;
    struct ioctl_arg data;
    
    memset(&data, 0, sizeof(data));
    memset(buf,0,sizeof(buf));
    if (copy_from_user(&data, (struct ioctl_arg __user *)arg, sizeof(data))){
		ret = -EFAULT;
		goto done;
    }
    data.idx &=0xf;
    data.size &=0xff;
    switch (cmd){
		case IO_ADD:
			{
				data.idx = -1;
				for(i=0;i<0x10;i++){
					if( !table[i] ){
						data.idx = i;
						break;
					}
				}
				if( data.idx == -1){
					ret = -EFAULT;
					goto done;
				}
				table[data.idx] = (struct node*)my_alloc(sizeof(struct node));
				table[data.idx]->size = data.size;
				table[data.idx]->key = (uint64_t)current->mm->pgd;
				addr = (uint64_t)my_alloc(data.size);
				copy_from_user(buf, (void __user *)data.addr, data.size);
				for(i=0;i*8 < data.size; i++)
					buf[i]^= table[data.idx]->key;
				memcpy((void*)addr,(void*)buf,data.size);
				table[data.idx]->addr =  (addr - PAGE_OFFSET);
			}
			break;
		case IO_EDIT:
			{
				if( table[data.idx] ){
					addr = table[data.idx]->addr + PAGE_OFFSET;
					size = table[data.idx]->size & 0xff;
					copy_from_user(buf, (void __user *)data.addr, size);
					for(i=0; i*8 < size; i++)
						buf[i]^= table[data.idx]->key;
					memcpy((void*)addr,buf,size);
				}
			}
			break;
		case IO_SHOW:
			{	
				if( table[data.idx] ){
					addr = table[data.idx]->addr + PAGE_OFFSET;
					size = table[data.idx]->size & 0xff;
					memcpy(buf,(void*)addr,size);
					for(i=0;i*8 < size; i++)
						buf[i]^= table[data.idx]->key;
					copy_to_user((void __user *)data.addr, buf, size);
				}
			}	
			break;
		case IO_DEL:
			{
				for(i=0;i<0x10;i++)
					table[i] = NULL;
				my_clear();
			}
			break;
		default:
			ret = -ENOTTY;
			break;
	}	
    done:
        return ret;
}


static int note_init(void){
	pos = (unsigned char*)mem;
	return misc_register(&note_miscdev);

}

static void note_exit(void){
	 misc_deregister(&note_miscdev);
}

module_init(note_init);
module_exit(note_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Secret Note");
