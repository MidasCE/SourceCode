#include<iostream>
using namespace std;

int sum(int *a,int i,int size){
	if(i == size-1){
		return a[i];
	}
	else{
		return a[i] + sum(a,i+1,size);
	}
}

bool check(int *a,int data,int i,int size){
	if(i == size-1){
		return a[i] == data;
	}
	else {
		if(a[i] != data)
			return check(a,data,i+1,size);
		else
			return true;
	}
}

int count(int *a,int data,int i,int size){
	if(i < size){
		if(a[i] == data)
			return 1 + count(a,data,i+1,size);
		else
			return 0 + count(a,data,i+1,size);
	}
	return 0;
}

bool isSort(int *a,int i,int size){
	if(i < size-1){
		if(a[i] < a[i+1]){
			return isSort(a,i+1,size);
		}
		else
			return false;
	}
	if(i == size-1){
		return true;
	}
}

int main(){
	int a[6] = {1,2,6,2,2,6};
	int b[6] = {1,2,3,4,5,6};
	cout << sum(a,0,6) << endl;
	cout << check(a,5,0,6) << endl;
	cout << check(b,3,0,6) << endl;
	cout << count(a,2,0,6) << endl;
	cout << isSort(a,0,6) << endl;
	cout << isSort(b,0,6) << endl;
}