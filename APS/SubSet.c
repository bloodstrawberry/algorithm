#include <stdio.h>
char src[] = {'a',98,99};
int n;

void subSet(){
	for (int i = 0; i < (1<<n); i++){//경우의 수 (0~7)
		printf("{");
		for (int j = 0; j < n; j++){ //검증
			if ((i & (1 << j))){// == (1 << j)){
				printf("%c ", src[j]);
			}
		}
//		printf("}\n");
		puts("}");
	}
}
int main(){
//	n = sizeof(src) / sizeof(char);
//	subSet();
	long long i = 1;
	printf("i : %lld\n", i<<64);
	return 0;
}
