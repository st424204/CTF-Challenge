#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <seccomp.h>
#include <string.h>
void myprintf(char* buf){
	write(1,buf,strlen(buf));
}
void myputs(char* buf){
	write(1,buf,strlen(buf));
	write(1,"\n",1);
}

char* note[0x100];
int read_int(){
	char buf[0x8];
	read(0,buf,sizeof(buf));
	return atoi(buf);
}
void add(){
	uint32_t idx = 0;
	for(idx=0;idx<0x100;idx++){
		if(note[idx]==NULL)
			break;
	}
	myprintf("Size: ");
	uint32_t size = read_int();
	note[idx]  = malloc(size);
	myprintf("Content: ");
	if(note[idx])
		note[idx][read(0,note[idx],size)]=0;
}
void Remove(){
	myprintf("Idx: ");
	uint32_t idx = read_int();
	if( idx < 0x100){
		free(note[idx]);
		note[idx] = NULL;
	}
}
void Show(){
 	myprintf("Idx: ");
        uint32_t idx = read_int();
        if( idx < 0x100 && note[idx]){
       		myputs(note[idx]); 
        }

}
int menu(){
	myputs("********************");
	myputs("1. New a note");
	myputs("2. Delete a note");
	myputs("3. Show a note");
	myputs("********************");
	myprintf("Choice: ");
	return read_int();
}
void init(){
	scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_KILL);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(open), 0);
    	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(read), 0);
 	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(write), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit), 0);
	seccomp_rule_add(ctx, SCMP_ACT_ALLOW, SCMP_SYS(exit_group), 0);
	seccomp_load(ctx);
}
int main(){
	init();
	while(1){
	switch( menu() ){
		case 1:
			add();
			break;
		case 2:
			Remove();
			break;
		case 3:
			Show();
			break;
		default:
			myputs("Wrong");
			break;
	}
	}
}

