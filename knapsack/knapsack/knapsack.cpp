#include<iostream>
using namespace std;

int t[8] = {0,0,0,0,0,0,0,0};
void findSub(int *a,int i,int money,int sum){
	if(money == sum){
		for(int i = 0;i < 8;i++){
			if(t[i] == 1)
				cout << a[i] << " ";
		}
		cout << endl;
	}
	else if(sum < money){
		for(;i < 8;i++){
			if(t[i] == 0){
				t[i] = 1;
				findSub(a,i,money,sum+a[i]);
				t[i] = 0;
			}
		}
	}
}

int main(){
	int a[8] = {20, 10,5, 5, 3, 2, 20, 10};
	const int money = 20;
	int sum = 0;	
	findSub(a,0,money,sum);
}