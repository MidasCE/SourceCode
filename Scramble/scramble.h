#ifndef _scramble_h
#define _scramble_h

template<class T>
class Scramble{
public:
	Scramble();
	Scramble(const Scramble& );
	~Scramble();
	void insert(T);
	void insert(T,T,T);
	void remove(T);
	void print();
	bool empty();
	int size();
	void rotate(int);
	void rotateBack();
	void cut(int);
	void cutBack();
private:
	struct  Node{
		T data;
		Node *link;
	};
	Node *head;
	Node *last;
	int count,perCut,perRotate;
	bool isCut,isRotate;
};
#include "scramble.cpp"
#endif