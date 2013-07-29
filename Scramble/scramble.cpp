#include <iostream>
#ifdef _scramble_h

template<class T>
Scramble<T>::Scramble(){
	head = new Node;
	head->link = NULL;
	count = 0,perCut = 0,perRotate = 0;
	isCut = isRotate = false;
}

template<class T>
Scramble<T>::Scramble(const Scramble& list){
	list = *this;
}

template<class T>
Scramble<T>::~Scramble(){
	Node *temp = head;
	while (temp != NULL) {
		Node *next = temp->link;
		delete temp;
		temp = next;
		count--;
	}
}

template<class T>
void Scramble<T>::insert(T data){
	Node *n = new Node;
	n->data = data;
	if(empty()){
		head = n;
		n->link= 0;
		last = head;
	}
	else{
		Node *temp;
		temp = head;
		while(temp->link != NULL){
			temp = temp->link;
		}
		temp->link = n;
		n->link = NULL;
		last = n;
	}
	count++;
}

template<class T>
void Scramble<T>::insert(T data,T before,T after){
	try{
		if(empty()){
			throw exception("Can't insert between data because this linklist is empty.");
		}
		else{
			Node *first,*second,*temp;
			temp = first = second = head;
			while(temp != NULL){
				if(temp->data == before){
					first = temp;
				}
				if(first != head && temp->data == after){
					second = temp;
				}
				temp = temp->link;
			}
			if(first == head || second == head){
				throw exception("Can't insert : error input front or back data.");
			}
			else{
				Node *n = new Node;
				n->data = data;
				n->link = second;
				first->link = n;
				count++;
			}
		}
	}
	catch(exception &e){
		cerr << "Caught: " << e.what( );
	}
}

template<class T>
void Scramble<T>::remove(T data){
	try{
		if(empty()){
			throw exception("Can't remove data from the list because this linklist is empty.")
		}
		else{
			Node *temp = head,*before;
			while(temp != NULL){
				before = temp;
				if(temp.data == data){
					before->link = temp->link;
					delete temp;
					count--;
					break;
				}
				temp = temp->link;
			}
		}
	}
	catch(exception &e){
		cerr << "Caught: " << e.what( );
	}
}

template<class T>
void Scramble<T>::print(){
	Node *temp = head;
	while(temp!= NULL){
		cout << temp->data ;
		temp = temp->link;
	}
	cout << endl;
}

template<class T>
int Scramble<T>::size(){
	return count;
}

template<class T>
bool Scramble<T>::empty(){
	return (count == 0);
}

template<class T>
void Scramble<T>::rotate(int percent){
	int real = ((percent)*(*this).size())/100;
	perRotate = real;
	Node *temp,*temp2,*next,*next2,*first;
	temp = head;
	for(int i = 0; i < real-1;i++){
		temp = temp->link;
	}
	last = temp;
	first = last->link;
	temp = head;
	temp2 = first;
	last->link = NULL;
	if(real > 5){
		while(temp2 != NULL){
			next = temp->link;
			next2 = temp2->link;
			temp->link = temp2;
			temp2->link = next;
			temp = next;
			temp2 = next2;
		}
	}
	else{
		while(temp->link != NULL){
			next = temp->link;
			next2 = temp2->link;
			temp->link = temp2;
			temp2->link = next;
			temp = next;
			temp2 = next2;
		}
		last->link = temp2;
		while(temp2->link != NULL){
			temp2 = temp2->link;		
		}
		last = temp2;
		last->link = NULL;
	}
	isRotate = true;
}

template<class T>
void Scramble<T>::cut(int percent){
	int real = ((percent)*(*this).size())/100;
	perCut = real;
	Node *temp,*first;
	temp = head;
	first = head;
	if(real > 1)
		real--;
	for(int i = 0; i < real;i++){
		temp = temp->link;
	}
	head = temp->link;
	temp->link = NULL;
	last->link = first;
	isCut = true;
}

template<class T>
void Scramble<T>::rotateBack(){
	if(isRotate){
		int real = (*this).size() - perRotate;
		Node *temp,*next,*first;
		temp = head;
		next = temp->link;
		first = next;
		int shuf = real;
		if(real > 5)
			shuf = perRotate;
		for(int i = 0;i < shuf-1;i++){
				temp->link = next->link;
				temp = temp->link;
				next->link = temp->link;
				next = next->link;
		}
		if(real > 5){
			temp->link = first;
			while(next->link != NULL){
				next = next->link;
			}
			last = next;
			last->link = NULL;
		}
		else {
			temp->link = next->link;
			while(temp->link != NULL){
				temp = temp->link;
			}
			temp->link = first;
			last = next;
			last->link = NULL;
		}
		perRotate = 0;
		isRotate = false;
	}
}

template<class T>
void Scramble<T>::cutBack(){
	if(isCut){
		int real = (*this).size() - perCut;
		perCut = 0;
		Node *temp,*first;
		temp = head;
		first = head;
		if(real > 1)
			real--;
		for(int i = 0; i < real;i++){
			temp = temp->link;
		}
		head = temp->link;
		temp->link = NULL;
		last->link = first;
		isCut = false;
	}
}
#endif
