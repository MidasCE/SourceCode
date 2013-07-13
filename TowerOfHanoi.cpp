#include<iostream>
#include<stack>
using namespace std;

stack<int> a;
stack<int> b;
stack<int> c;

void print(stack<int> s,int i,int size){
	if(!s.empty()){
		if(i == size -1){
			cout << s.top();
		}
		else{
			int data = s.top();
			s.pop();
			cout << data;
			print(s,i+1,size);
			s.push(data);
		}
	}
}

void print3(){
	print(a,0,a.size()); 
	cout <<	",";
	print(b,0,b.size());
	cout << ",";
	print(c,0,c.size());
	cout << endl;
}

void tower(int size,stack<int> &at,stack<int> &spare,stack<int> &goal){
	print3();
	if(size == 1){
		goal.push(at.top());
		at.pop();
	}
	else{
		tower(size-1,at,goal,spare);
		goal.push(at.top());
		at.pop();
		tower(size-1,spare,at,goal);
	}
}

int main(){
	for(int i = 3;i > 0;i--){
		a.push(i);
	}
	print(a,0,3);
	cout << endl;
	tower(3,a,b,c);
	print3();
}
