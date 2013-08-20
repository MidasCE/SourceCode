#include<iostream>

using namespace std;

template<class T> 
class minHeap{ 
	int size; //array size 
	int last_index; //last index of heap 
	T *h; 
public: 
	minHeap(int size){
		this->size = size;
		h = NULL;
		last_index = -1;
	}
	void print();
	void insert(T);
	void printSideway(int,int);
	void inorder(int);
	void preorder(int);
	void postorder(int);
	void deleteMin(T& min);
};

template<class T>
void minHeap<T>::print(){
	if(this->last_index != -1){
		for(int i = 0;i <= this->last_index;i++){
			cout << h[i] << " ";
		}
		cout << endl;
	}
}

template<class T>
void minHeap<T>::insert(T data){
	if(this->last_index == -1){
		h = new T[size];
		this->last_index++;
		h[this->last_index] = data;
	}
	else{
		this->last_index++;
		T *temp;
		int j,k;
		for(j = this->last_index, k = (j-1)/2;data < h[k] && j > 0; j = k,k = (j-1)/2){
			h[j] = h[k];
		}
		if(k == 0 && data < h[k]){
			h[j] = h[k];
			h[k] = data;
		}
		else 
			h[j] = data;
	}
}

template<class T>
void minHeap<T>::printSideway(int root,int indent){
	if (root < this->size){
		printSideway(2*root+2,indent+1);
		for(int i = 0;i < indent;i++)
			cout << "  ";
		cout << h[root] << endl;
		printSideway(2*root+1,indent+1);
	}
}

template<class T>
void minHeap<T>::inorder(int root){
	if(root < this->size){
		inorder(2*root+1);
		cout << h[root] << " ";
		inorder(2*root+2);
	}
}

template<class T>
void minHeap<T>::preorder(int root){
	if(root < this->size){
		cout << h[root] << " ";
		inorder(2*root+1);
		inorder(2*root+2);
	}
}

template<class T>
void minHeap<T>::postorder(int root){
	if(root < this->size){
		inorder(2*root+1);
		inorder(2*root+2);
		cout << h[root] << " ";
	}
}

template<class T>
void minHeap<T>::deleteMin(T& min){
	T temp;
	int i = 0;
	while(i <= last_index){
		if(i == 0){
			temp = h[i];
		}
		if(2*i+2 <= last_index){
			if(h[2*i+1] > h[2*i+2]) {
				h[i] = h[2*i+2];
				i = 2*i+2;
			}
			else{
				h[i] = h[2*i+1];
				i = 2*i+1;
			}
		}
		else{
			if(2*i+1 <= last_index){
				h[i] = h[2*i+1];
			}
			i++;
		}
	}
	for(i = last_index;i >=0;i--){
		if(temp <h[i]){
			h[i] = temp;
			break;
		}
	}
	last_index--;
	min = temp;
}

template<class T>
void print (T *a,int size){
	for(int i = 0;i < size;i++){
		cout << a[i] << " ";
	}
	cout << endl;
}


template<class T>
void printSideway(T *a,int root,int size,int indent){
	if (root < size){
		printSideway(a,2*root+2,size,indent+1); // right sub tree
		for(int i = 0;i < indent;i++)
			cout << "  ";
		cout << a[root] <<"\n";
		printSideway(a,2*root+1,size,indent+1); // left sub tree
	}
}

template<class T>
void insert(T *a,T data,int i){
	if(i == 0){
		a[i] = data;
	}
	else{
		T temp;
		int j,k;
		for(j = i, k = (j-1)/2;data < a[k] && j > 0; j = k,k = (j-1)/2){
			a[j] = a[k];
		}
		if(k == 0 && data < a[k]){
			a[j] = a[k];
			a[k] = data;
		}
		else 
			a[j] = data;
	}
}

int main(){
	const int size = 10;
	int b[size] = {68,65,32,24,26,21,19,13,16,14};
	print(b,size);
	printSideway(b,0,size,1);
	int h[size];
	cout << "input array : " ;
	print(b,size);
	for(int i = 0; i < size;i++){
		insert(h,b[i],i);
		cout << endl;
		printSideway(h,0,i+1,0);
	}
	cout << endl;
	minHeap<int> a(size);
	for(int i = 0; i < size;i++){
		a.insert(b[i]);
	}
	a.print();
	a.printSideway(0,0);
	a.inorder(0);
	cout << endl;
	a.preorder(0);
	cout << endl;
	a.postorder(0);
	cout << endl;
	int c[size] = {13,14,21,19,16,65,24,68,26,32};
	cout << "--- delete min ---" << endl;
	cout << "input : " ;
	print(c,size);
	for(int i = 0;i < size;i++){
		a.deleteMin(c[i]);
		a.printSideway(0,0);
		cout << endl;
	}
	cout << "-- SORTING A --" << endl;
	a.print();
	a.printSideway(0,0);
	cout << "-- SORTING C --" << endl;
	print(c,size);
}