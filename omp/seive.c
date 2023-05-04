#include<stdio.h>
#include<omp.h>

int main(){
	int N = 10000000;
	int arr[10000001] = {};
	arr[0] = 1;
	arr[1] = 1;
	int primeCount = 0, k = 2, mul=0, temp=0;


	for(int i=0;1;){
		mul = 1;
		temp=k;
		for(int j = k+1; j <= N; j++){
			if(arr[j] != 1){
				k = j;
				break;
			}
		}
		if(k==temp)
			break;
		// printf("original k: %d\n", k);
		primeCount++;
		for(int x = k, mul = 1; x <= N+1; mul++){
			arr[x] = 1;
			x=k;
			x *=mul;
		}
	}

	// while(1){
	// 	mul = 1;
		
	// 	int index = k+1, temp=0;
	// 	while(arr[index] == 1){
	// 		index++;
	// 	}
	// 	if(index > N+1)
	// 		break;
	// 	k=index;
	// 	temp=k;
	// 	// printf("original k: %d\n", k);
	// 	primeCount++;
	// 	while(temp <= N+1){
	// 		arr[temp] = 1;
	// 		temp=k;
	// 		mul+=1;
	// 		temp *= mul;
	// 	}
	// }

	printf("primeCount: %d\n",primeCount);
}
	