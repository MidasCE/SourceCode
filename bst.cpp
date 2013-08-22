#include<iostream>
#include<vector>
using namespace std;

template<typename T> 
class BST; //forward declaration 

template<typename T> 
class node{ 
	T data; 
	node *left, *right; 
	friend class BST<T>; 
public:
	node(T data){
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
}; 

template<typename T> 
class BST{ 
	node<T>* root; 
	void printSubtree(node<T> *r,int level){
		if(r != NULL){
			printSubtree(r->right,level+1);
			for(int i = 0 ;i < level;i++)
				cout << "   " ;
			cout << r->data << endl;
			printSubtree(r->left,level+1);
		}
	}
	void remove(node<T> *r,node<T> *f,T item){
		if(r != NULL){
			if(item > r->data){
				remove(r->right,r,item);
			}
			else if(item < r->data){
				remove(r->left,r,item);
			}
			else{
				if(r->left == NULL && r->right == NULL){
					if(r->data > f->data)
						f->right = NULL;
					else
						f->left = NULL;
					delete r;
				}
				else if(r->left == NULL || r->right == NULL){
					if(r->data > f->data){
						if(r->left == NULL)
							f->right = r->right;
						else
							f->right = r->left;
					}
					else{
						if(r->left == NULL)
							f->left = r->right;
						else
							f->left = r->left;
					}
					delete r;
				}
				else{
					vector<int> a;
					sortData(a);
					for(int n=0;n < a.size();n++){
						if(a[n] == item){
							T temp = a[n-1];
							remove(r->left,f,temp);
							r->data = temp;
							break;
						}
					}
				}
			}
		}
	}

	void sort(node<T> *r,vector<T> &a){
		if(r != NULL){
			sort(r->left,a);
			a.push_back(r->data);
			sort(r->right,a);
		}
	}

	void printPath(node<T> *p,T item,int level){
		if(p->data != item){
			if(item > p->data)
				printPath(p->right,item,level+1);
			for(int i = 0 ;i < level;i++)
				cout << "   " ;
			cout << p->data << endl;
			if (item < p->data) 
				printPath(p->left,item,level+1);
		}
		else {
			for(int i = 0 ;i < level;i++)
				cout << "   " ;
			cout << p->data << endl;
		}
	}

	int countLev(node<T> *p,int lev,int i){
		if(i < lev && p != NULL){
			return countLev(p->right,lev,i+1) + countLev(p->left,lev,i+1);
		}
		else{
			if( p != NULL)
				return 1;
			else
				return 0;
		}
	}

	int countHeight(node<T> *p){
		if(p->left == NULL && p->right == NULL){
			return 1;
		}
		else{
			if(p->left != NULL){
				return 1+countHeight(p->left);
			}
			if (p->right != NULL){
				return 1+countHeight(p->right);
			}
		}
	}

public:
	BST(T data){
		root = new node<T>(data);	
	}
	~BST(){
		delete root;
	}
	void addNode(T item){
		node<T> *p,*t;
		p = new node<T>(item);
		t = this->root;
		while(t->left != NULL && t->right != NULL){
			if(item > t->data){
				t = t->right;
			}
			else{
				t = t->left;
			}
		}	
		if(item > t->data){
			t->right = p;
		}
		else{
			t->left = p;
		}
	}
	void removeNode(T item){
		if(find(item)){
			node<T> *f;
			f = root;
			if(item > f->data){
				remove(root->right,f,item);	
			}
			else if (item < f->data){
				remove(root->left,f,item);
			}
			else{
				remove(root,f,item);
			}
		}
	}
	
	void removeTree(T item){
		node<T> *p,*f;
		p = root;
		while(p->data != item){
			f = p;
			if(item > p->data){
				p = p->right;
			}
			else{
				p = p->left;
			}
		}
		if(f->data > p->data){
			f->left = NULL;
		}
		else{
			f->right = NULL;
		}
		while(p->left != NULL){
			remove(p->left,p,p->left->data);
		}
		while(p->right != NULL){
			remove(p->right,p,p->right->data);
		}
		remove(p,f,p->data);
	}

	int countMore(T item){
		node<T> *p;
		p = root;
		int count = 0;
		vector<int> a;
		sortData(a);
		for(int i = 0;i < a.size();i++){
			if(a[i] > item){
				count++;
			}
		}
		return count;
	}

	int atLevel(int lev){
		return countLev(root,lev,1);
	}

	int height(T item){
		if(find(item)){
			node<T> *p;
			p = root;
			while(p->data != item){
				if(item > p->data){
					p = p->right;
				}
				else
					p = p->left;
			}
			int hL = 0,hR = 0,h = countHeight(root);
			if(p->left != NULL)
				hL = countHeight(p->left);
			if(p->right != NULL)
				hR = countHeight(p->right);
			int temp = hL;
			if(hR > hL){
				temp = hR;
			}
			return temp;
		}
		else
			return -1;
	}
	
	bool isBalanced(T item){
		if(find(item)){
			if(item == root->data){
				int hl = countHeight(root->left);
				int hr = countHeight(root->right);
				return hl > hr || hl < hr;
			}
			else{
				node<T> *p;
				p = root;
				while(p->data != item){
					if(item > p->data){
						p = p->left;
					}
					else
					{
						p = p->right;
					}
				}
				int hl = countHeight(p->left);
				int hr = countHeight(p->right);
				return hl > hr || hl < hr;
			}
		}
		else{
			return false;
		}
	}

	bool isBalanced(){
		return isBalanced(root->data);
	}

	void path(T item){
		node<T> *p;
		p = root;
		printPath(p,item,0);
		cout << endl;
	}

	bool find(T item){
		node<T> *p;
		p = root;
		while(p != NULL){
			if(item > p->data){
				p = p->right;
			}
			else if(item < p->data){
				p = p->left;
			}
			else{
				return item == p->data;
			}
		}
		return false;
	}

	void print(){
		printSubtree(root,0);
		cout << endl;
	}

	void listAll(){
		vector<int> a;
		sortData(a);
		for(int i = 0; i < a.size() ; i++){
			cout << a[i] << " ";
		}
		cout << endl;
	}

	T smallest(){
		node<T> *p;
		p = this->root;
		while(p->left != NULL){
			p = p->left;
		}
		return p->data;
	}

	T largest(){
		node<T> *p;
		p = this->root;
		while(p->right != NULL){
			p = p->right;
		}
		return p->data;
	}

	void sortData(vector<T> &a){
		sort(root,a);
	}
	
};


int main(){ 
	BST<int> tree(10);
	tree.addNode(11);
	tree.addNode(9);
	tree.print();
	tree.removeNode(10);
	tree.print();
	tree.listAll();
	cout << tree.find(9) << endl;
	tree.addNode(5);
	tree.addNode(6);
	tree.addNode(12);
	tree.addNode(10);
	tree.print();
//	tree.removeTree(11);
	tree.print();
//	tree.path(11);
	//cout << tree.atLevel(3) << endl;;
	cout << tree.isBalanced() << endl;
	cout << tree.height(9) << endl;
	return 0; 
}