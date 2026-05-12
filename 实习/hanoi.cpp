#include <stdio.h>
void hanio(int n,char A,char B,char C){
	if(n==1){
		printf("move %d from %c to %c\n\n",n,A,C);
		return ;
	}
	hanio(n-1,A,C,B);
	printf("-------\n");
	printf("$move %d from %c to %c\n\n",n,A,C);
	printf("**************\n");
	hanio(n-1,B,A,C);
	printf("============\n");
}

int main(){
	int n=3;
	char A='A',B='B',C='C';
//	scanf("%d",&n);
	hanio(n,A,B,C);
	return 0;
}