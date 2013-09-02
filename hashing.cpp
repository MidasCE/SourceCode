#include<iostream>
#include<string>
#include<cstdio>
#include<fstream>

using namespace std;

bool isPrime(int n){
	for(int i=2;i<n;i++){
		if(n%i==0)
			return false;
	}
	return true;
}

int nextPrime(int n){
	if(!isPrime(n))
		return nextPrime(n+1);
	return n;
}

int hashkey(string key,int tableSize){
	int hashVal = 0;
	for(int i = 0; i < key.size();i++){
		hashVal = 37*hashVal+key.at(i);
	}
	hashVal %= tableSize;
	if(hashVal < 0){
		hashVal += tableSize;
	}
	return hashVal;
}

void rehash(string *(&table),int &size,int &maxChain){
	string *temp = table;
	int oldSize = size;
	size = nextPrime(size*2);
	table = new string[size];
	for(int i = 0;i < size;i++){
		table[i] = "";
	}
	for(int i =0;i < oldSize;i++){
		if(temp[i] != ""){
			int key = hashkey(temp[i],size);
			int j =0;
			while(table[(key+(j*j))%(size)] != ""){
				j++;
			}
			if(j > maxChain){
				maxChain = j;
			}
			table[(key+(j*j))%(size)] = temp[i];
		}
	}
	delete[] temp;
}


int main(){
	ifstream infile;
	string filename;
	cout << "Enter file name : ";
	cin >> filename;
	infile.open(filename.c_str());
	if(infile.fail()){
		cerr << "Can't open file" << endl;
		exit(EXIT_FAILURE);
	}
	else{
		int size = 19,i;
		int count = 0,maxChain = 0;
		string *table;
		table = new string[size];
		for(i = 0;i < size;i++){
			table[i] = "";
		}
		string word;
		while(infile >> word){
			count++;
			if((double)count/size >= 0.5)
				rehash(table,size,maxChain);
			int key = hashkey(word,size);
			i = 0;
			while(table[(key+(i*i))%size] != ""){
				i++;
			}
			if(i > maxChain){
				maxChain = i;
			}
			table[(key+(i*i))%size] = word;
		}

		while(true){
			string input;
			cout << "Enter your word: " << endl;
			cin >> input;
			int key = hashkey(input,size);
			int j = 0;
			bool found = false;
			while(j < maxChain){
				if(table[(key+(j*j))%size] == input){
					found =true;
					break;
				}
				j++;
			}
			if(found){
				cout << "\"" << input << "\""<< "is correctly spelled" << endl;
			}
			else{
				cout << "\"" << input << "\""<< "is not in the dictionary" << endl;
			}
		}
	}
}