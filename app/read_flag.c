#include <stdio.h>
#include <stdlib.h>
char flag[0x100];
int main(){
	FILE* fp = fopen("flag","r");
	if(fp){
		fread(flag,1,0x100,fp);
		puts(flag);
		close(fp);
	}
	else{
		puts("[Error] You have no Permission (Protect from AppArmor XD)");
	}	
}
