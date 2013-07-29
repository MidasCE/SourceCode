#include<iostream>
#include<sstream>
#include<string>
#include<stack>
using namespace std;
string doubleToString(double number);

int main(){
	stack<string> operands;
	stack<char> operators;
	cout << "Enter math : " ;
	string line;
	getline(cin,line);
	int j = 0;
	cout << line.length() << endl;
	for(int i = 0; i < line.length();i = j+1){
		j=i;
		for(int count = 0; j < line.length();j++,count++){
			if(j == line.length()-1) {
				operands.push(line.substr(j));
				break;
			}
			else if(line[j] == '*' || line[j] == '/' || line[j] == '+' || line[j] == '-' ){
				operands.push(line.substr(i,count));
				if(operators.empty()){
					operators.push(line[j]);
				}
				else {
					if((operators.top() == '+' || operators.top() == '-') && (line[j] == '*' || line[j] == '/')){
						operators.push(line[j]);
					}
					else if((operators.top() == '*' || operators.top() == '/') && (line[j] == '+' || line[j] == '-')){
						double result = 0;
						double a = atof(operands.top().c_str());
						operands.pop();
						double b = atof(operands.top().c_str());
						operands.pop();
						if(operators.top() == '*') result = b*a;
						else result = b/a;
						operators.pop();
						operators.push(line[j]);
						operands.push(doubleToString(result));
					}
					else if((operators.top() == '+' && (line[j] == '-')) || (operators.top() == '-' && (line[j] == '+')) || (operators.top() == '*' && (line[j] == '/')) || (operators.top() == '/' && (line[j] == '*')) ){
						double result = 0;
						double a = atof(operands.top().c_str());
						operands.pop();
						double b = atof(operands.top().c_str());
						operands.pop();
						if(operators.top() == '*') result = a*b;
						else if(operators.top() == '/') result = b/a;
						else if(operators.top() == '+') result = a+b;
						else if(operators.top() == '-') result = b-a;
						operators.pop();
						operators.push(line[j]);
						operands.push(doubleToString(result));
					}
				}
				break;
			}
		}
	}
		while(!operators.empty()){
			double result = 0;
			double a = atof(operands.top().c_str());
			operands.pop();
			double b = atof(operands.top().c_str());
			operands.pop();
			if(operators.top() == '*') result = a*b;
			else if(operators.top() == '/') result = b/a;
			else if(operators.top() == '+') result = a+b;
			else if(operators.top() == '-') result = b-a;
			operators.pop();
			operands.push(doubleToString(result));
		}
		cout << "The result is : " << operands.top() << endl;
}

string doubleToString(double number)
{
	stringstream oss;
	oss << number;
	return oss.str();
}