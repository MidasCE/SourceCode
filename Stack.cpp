#include<iostream>
#include<string>
#include<fstream>
using namespace std;

template <class T,int MAX = 10>
class stack{
public:
	stack();
	void push(T);
	T pop();
	const T& top() const;
	const int size() const;
	bool empty();
	bool full();
	void print();
	void make_empty();
private : 
	int tops;
	T items[MAX];
};

template <class T,int MAX>
stack<T, MAX>::stack():tops(-1){}


template <class T,int MAX>
void stack<T, MAX>::push(T i){
	if (tops == MAX - 1) 
		throw overflow_error("stack overflow"); 
	else 
		items[++tops] = i;
}

template <class T,int MAX>
T stack<T, MAX>::pop(){
	if (tops == -1) 
		throw underflow_error("stack underflow"); 
	else 
		return items[tops--];
}

template <class T,int MAX>
const T& stack<T, MAX>::top() const{
	return items[tops];
}

template <class T,int MAX>
const int stack<T, MAX>::size() const{
	return tops+1;
}


template <class T,int MAX>
bool stack<T, MAX>::empty(){
	return (tops == -1);
}

template <class T,int MAX>
bool stack<T, MAX>::full(){
	return (tops == MAX - 1);
}

template <class T,int MAX>
void stack<T, MAX>::print(){
	stack<T,MAX> old = *this;
	stack<T,MAX> temp;
	for(int i = 0 ; i <= tops;i++){
		T n = old.pop();
		temp.push(n);
	}
	for(int i = 0 ; i <= tops;i++){
		T n = temp.pop();
		cout << n << ",";
	}
	cout << endl;
}

template <class T,int MAX>
void stack<T, MAX>::make_empty(){
	for(int i = 0 ; i <= tops;i++){
		pop();
	}
}


void parenthesis(){
	//2. try parenthesis matching problem
	stack<char> cStack;
	char c;
	char open;
	int err_pos = 0; //error position
	int error = 0; //err.type(not match, LackOpenParen, LackCloseParen)
	cout << "\n\n========= part 2 =========\n";
	cStack.make_empty();
	cStack.print();
	cout << "Enter expression to test parenthesis matching problem (Enter 0 to stop): ";
	try {
		while (cin >> c && !error) {
			if(c == '0'){
				cout << "Stop Testing." << endl;
				break;
			}
			if(c == '{' || c == '[' || c == '('|| c == '<'){
				open = c;
				cStack.push(open);
			}
			else if (c == ')' || c == ']' || c == '}' || c == '>') {
				if (cStack.empty()){ 
					error = 2;
					break;
				}
				if ((open == '(' && c != ')') || (open == '{' && c != '}') || (open == '[' && c != ']') || (open == '<' && c != '>')){
					error = 1;
					break;
				}
				cStack.pop();
				open = cStack.top();
			}
			err_pos++;
		}
		if (error == 1)
			throw exception("Not Matching");
		else if (error == 2)
			throw exception("Lack open parenthesis");
		else if (cStack.size() == 0)
			cout << "Matching" << endl;
		else
			throw exception("Lack close parenthesis");
	} catch (exception &e) {
		cerr << "------In part 2 : parenthesis matching--------\n";
		cerr << "Caught: " << e.what( );
		cerr << "at position: " << err_pos << " of input." << "\n";
	}//catch 
}

void parkingLodge(){
	//3. try parking lodge problem
	cout << "\n\n========= part 3 : Parking Lodge =========\n";
	stack<string> parkLot;
	string cmd;
	int count = 10;
	while(true){
		getline(cin,cmd);
		if(cmd.substr(0) == "Q"){
			cout << "Quit parking lodge." << endl;
			break;
		}
		if(cmd.substr(0,1) == "A"){
			if(!parkLot.full()){
				count--;
				cout << cmd.substr(2) << " arrived " << "space left : " << count << endl;
				parkLot.push(cmd.substr(2));
			}
			else
				cout << "Parking lodge is full." << endl;
		}
		else if(cmd.substr(0,1) == "D"){
			if(!parkLot.empty()){
				stack<string> temp = parkLot;
				bool isHave = false;
				while(!temp.empty()){
					string s = temp.pop();
					if(cmd.substr(2) == s){
						isHave = true;
						count++;
					}
				}
				if(isHave){
					while(!parkLot.empty()){
						if(parkLot.top() == cmd.substr(2)){
							parkLot.pop();
						}
						else
							temp.push(parkLot.pop());
					}
					while(!temp.empty()){
						parkLot.push(temp.pop());
					}

					cout << cmd.substr(2) << " departed " << "space left : " << count << endl; 
				}
				else
					cout << "Not have that car in parking lodge." << endl;
			}
			else
				cout << "Parking lodge is empty." << endl;
		}
		else
			cout << "Please enter command(A,D,Q) follow by car number." << endl;
	}
}

void postfix(){
	//4.postfix notation
	cout << "\n\n========= part 4 : postfix notation =========\n";
	stack<int> num;
	stack<char> operate;
	string line;
	cin.ignore();
	getline(cin,line);
	double result = 0;
	for(int i = 0;i < line.length();i++){
		if(line[i] > 48 && line[i] <= 57){
			int n = line[i] - '0';	
			num.push(n);
		}
		else if(line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/'){
			operate.push(line[i]);
			if(num.size() >= 2){
				int temp = num.pop();
				char op = operate.pop();
				if(op == '+'){
					result = temp+num.pop();
				}
				else if(op == '-'){
					result = temp-num.pop();
				}
				else if(op == '*'){
					result = temp*num.pop();
				}
				else if(op == '/'){
					result = temp/num.pop();
				}
				num.push(result);
			}
		}
	}
	cout << "Result is : " << num.pop() << endl;
}

int main(){
	// Test stack;
	const int MAXSTACK = 2;
	cout << "======== stack testing part 1 ========\n";
	stack<char,MAXSTACK> s;
	try {
		s.print();
		s.push('A'); 
		s.push('B'); 
		s.print();
	} catch (exception &e) {
		cerr << "---------In part 1-----------\n";
		cerr << "Caught: " << e.what( ) << "\n";
		cerr << "-------------------------------";
	}

	char mode;
	cout << "\nAvailable mode (M,P,N)" << endl;
	cout << "M = parenthesis matching program" << endl;
	cout << "P = parking lodge program" << endl;
	cout << "N = postfix notation program" << endl;
	cout << "\nEnter Mode : ";
	cin >> mode;
	if(mode == 'M'){
		parenthesis();
	}
	else if(mode == 'P'){
		parkingLodge();
	}
	else if(mode == 'N'){
		postfix();
	}
	else
		cout << "Please enter the right command." << endl;
	return 0;
}