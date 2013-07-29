#include<iostream>
#include<string>
#include"scramble.h"
using namespace std;

int main(){
	Scramble<char> sc;
	string line;
	cout << "Enter some sentence : ";
	getline(cin,line);
	for(int i = 0; i< line.length();i++){
		sc.insert(line[i]);
	}
	sc.print();
	sc.insert('G','1','2');
	sc.print();
	sc.cut(30);
	sc.print();
	sc.rotate(50);
	sc.print();
	sc.rotateBack();
	sc.print();
	sc.cutBack();
	sc.print();
}