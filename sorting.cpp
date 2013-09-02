#include<fstream>
#include<iostream>
#include<string>
#include<cstdio>
#include<vector>
#include<ctime>
#include<cmath>

using namespace std;

void bubbleSort(int *a,int lastIndex){
	bool swap = true;
	while(lastIndex > 1 && swap){
		swap = false;
		for(int i = 0; i < lastIndex;i++){
			if(a[i] > a[i+1]){
				int temp = a[i+1];
				a[i+1] = a[i];
				a[i] = temp;
				swap = true;
			}
		}
		lastIndex--;
	}
}

void selectionSort(int *a,int lastIndex){
	for(;lastIndex >0;lastIndex--){
		int max = INT_MIN;
		int position = 0;
		for(int i = 0;i <= lastIndex;i++){
			if(a[i] > max){
				max = a[i];
				position = i;
			}
		}
		a[position] = a[lastIndex];
		a[lastIndex] = max;		
	}
}

void insertionSort(vector<int> &a,int firstIndex,int lastIndex){
	for(int i = firstIndex+1;i <= lastIndex;i++){
		int item = a[i];
		int j;
		for(j =i;j > 0 && item <= a[j-1];j--){
			a[j] = a[j-1];
		}
		a[j] = item;
	}
}

void merge(vector<int> &a,int iA,int endA,int iB,int endB){
	vector<int> C;
	int sA = iA;
	while(iA <= endA && iB <= endB){
		if(a[iA] < a[iB]){
			C.push_back(a[iA]);
			iA++;
		}
		else{
			C.push_back(a[iB]);
			iB++;
		}
	}
	if(iA > endA && iB <= endB){
		while(iB <= endB){
			C.push_back(a[iB]);
			iB++;
		}
	}
	else if(iB > endB && iA <= endA){
		while(iA <= endA){
			C.push_back(a[iA]);
			iA++;
		}
	}
	for(int i = sA,j = 0; i <= endB && j < C.size();j++,i++){
		a.at(i) = C.at(j);
	}
}

void mergeSort(vector<int> &a,int left,int right){
	if(left < right){
		int center = (left+right)/2;
		mergeSort(a,left,center);
		mergeSort(a,center+1,right);
		merge(a,left,center,center+1,right);
	}
}

int median(vector<int> &a,int left,int right){
	int center = (left+right)/2;
	int b[3];
	b[0] = a[left];
	b[1] = a[center];
	b[2] = a[right];
	bubbleSort(b,2);
	return b[1];
}

void quickSort(vector<int> &a,int left,int right){
	if(left + 10 <= right){
		int center = (left+right)/2;
		int pivot = median(a,left,right);
		int i = left;
		int j = right -1;
		if(a[left] == pivot){
			a[left] = a[j];
			a[j] = pivot;
		}
		else if(a[center] == pivot){
			a[center] = a[j];
			a[j] = pivot;	
		}
		else {
			a[right] = a[j];
			a[j] = pivot;	
		}
		a[center] = a[j];
		a[j] = pivot;
		while(true){
			while(a[i] < pivot){
				i++;
			}
			while(a[j] > pivot){
				j--;
			}
			if(i < j){
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
				i++;
				j--;
			}
			else
				break;
		}
		int temp = a[right-1];
		a[right-1] = a[i];
		a[i] = temp;
		quickSort(a,left,i-1);
		quickSort(a,i+1,right);
	}
	else{
		insertionSort(a,left,right);
	}
}

void initSeed(){
	static bool init = false;
	if(!init){
		srand(int(time(NULL)));
		init = true;
	}
}

int randomInt(int low,int high){
	initSeed();
	double d = rand()/(double(RAND_MAX) -1);
	double s = d*(double(high) - low + 1);
	return int(floor(low+s));
}

int main(){
	const int size = 10;
/*	ifstream infile;
	string filename;
	cout << "Enter file name : ";
	cin >> filename;
	infile.open(filename.c_str());
	if(infile.fail()){
		cerr << "Can't open file" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		int a[500],index = 0;
		string line;
		while(true){
			if(infile.fail()) 
				break;
			getline(infile,line);
			string temp = "";
			int num;
			for(int i =0;i < line.size();i++){
				if(line[i] != ' '){
					temp += line[i];
				}
				else{
					num = atoi(temp.c_str());
					a[index] = num;
					index++;
					temp = "";
				}
			}
		}
	}
*/
	int a[size] = {1,52,4,8,3,0,5,9,22,70};
	bubbleSort(a,size-1);
	for(int i = 0;i < size;i++){
		cout << a[i] << " ";
	}
	cout << endl;
	int b[size] = {3,87,225,6,1,9,54,798,555,70};
	selectionSort(b,size-1);
	for(int i =0;i < size;i++){
		cout << b[i] << " ";
	}
	cout << endl;
	vector<int> d;
	for(int i = 0;i < size;i++){
		int j = 0;
		int rand = randomInt(0,1000);
		bool isHave = false;
		while(j < d.size()){
			if(rand == d.at(j)){
				isHave = true;
				break;
			}
			j++;
		}
		if(!isHave){
			d.push_back(rand);
		}
	}
	mergeSort(d,0,size-1);
	for(int i =0;i < size;i++){
		cout << d[i] << " ";
	}
	cout << endl;
	vector<int> e;
	for(int i = 0;i < size*2;i++){
		int j = 0;
		int rand = randomInt(0,1000);
		bool isHave = false;
		while(j < e.size()){
			if(rand == e.at(j)){
				isHave = true;
				break;
			}
			j++;
		}
		if(!isHave){
			e.push_back(rand);
		}
	}
	quickSort(e,0,(size*2)-1);
	for(int i =0;i < size*2;i++){
		cout << e[i] << " ";
	}
	cout << endl;
}