#ifndef _OS_HW5_DRIVER_H
#define _OS_HW5_DRIVER_H

#include <linux/ioctl.h>

#define IOC_MAGIC '\xFF'

#define IO_ADD     _IOWR(IOC_MAGIC, 0, struct ioctl_arg)
#define IO_EDIT    _IOWR(IOC_MAGIC, 1, struct ioctl_arg)
#define IO_SHOW    _IOWR(IOC_MAGIC, 2, struct ioctl_arg) 
#define IO_DEL	   _IOWR(IOC_MAGIC, 3, struct ioctl_arg) 

struct ioctl_arg
{
	uint64_t idx;
	uint64_t size;
	uint64_t addr;
};

struct node
{
	uint64_t key;
	uint64_t size;
	uint64_t addr;
};
static struct node *table[0x10];
static unsigned char mem[0x2000];
static unsigned char* pos ;

#endif
