//generates a file named passkey.bin which contains the passKey
#include <stdio.h>

int main(){
	FILE *f;
	f=fopen("passkey.bin","wb");
    	char s[10]="123456";
	fwrite(&s,sizeof(s),1,f);
	return 0;
}
