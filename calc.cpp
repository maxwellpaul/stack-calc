//calc.cpp
#include "Stack.h"
#include "Rational.h"
using namespace std;

class Pred {
	Rational key;
	public:

		//MODIFIES	key
		//EFFECTS	Initializes the Pred class
		Pred(Rational key_in)
		: key(key_in) {}

		//EFFECTS	Returns true if the num matches
		//			the key, serves as an overload for ()
		bool operator()(Rational num) {
			return num == key;
		}
};

class Calculator {
	public:

		//MODIFIES	stack
		//EFFECTS	Initializes the Calculator class
		Calculator()
		: quit_bool(false), stack(Stack<Rational>()) {}

		//MODIFIES	stack
		//EFFECTS	Adds num to the top of the stack
		void push(Rational num);

		//REQUIRES	stack has at least two elements
		//MODIFIES	stack
		//EFFECTS	pops off the first two elements
		//			from the stack, then pushes the
		//			summation of those two
		void add();

		//REQUIRES	stack has at least two elements
		//MODIFIES	stack
		//EFFECTS	pops off the first two elements
		//			from the stack, then pushes the
		//			difference of the two
		void subtract();

		//REQUIRES	stack has at least two elements
		//MODIFIES	stack
		//EFFECTS	pops off the first two elements
		//			from the stack, then pushes the
		//			product of the two
		void multiply();

		//REQUIRES	stack has at least two elements
		//MODIFIES	stack
		//EFFECTS	pops off the first two elements
		//			from the stack, then pushes the
		//			quotient of the two
		void divide();

		//REQUIRES	stack has at least one element
		//MODIFIES	stack
		//EFFECTS	adds a duplicate of the top element
		void duplicate();

		//REQUIRES	stack has at least two elements
		//MODIFIES	stack
		//EFFECTS	pops the top two elements off
		//			the stack, then reverses them
		//			and pushes them back
		void reverse();

		//EFFECTS	prints out the top element on
		//			the stack
		void print();

		//MODIFIES	stack
		//EFFECTS	removes all elements frmo the stack
		void clear();

		//EFFECTS	prints out all the elements in the
		//			stack
		void print_all();

		//REQUIRES	stack has at least one element
		//MODIFIES	stack
		//EFFECTS	negates the top element in the stack
		void negate();

		//REQUIRES	stack has at least one element
		//MODIFIES	stack
		//EFFECTS	pops the top element off the stack,
		//			then pushes the number of matches to
		//			that element
		void match();

		//MODIFIES	stack
		//EFFECTS	finds the correct operation for the input,
		//			the calls the correct function based on that
		void find_operation(string input);

		void quit();

		bool quit_bool;

	private:
		Stack<Rational> stack;
	};

void Calculator::push(Rational num) {
	stack.push(num);
}

void Calculator::add() {
	Rational num_1(stack.pop());
	Rational num_2(stack.pop());
	stack.push(num_1 + num_2);
}

void Calculator::subtract() {
	Rational num_1(stack.pop());
	Rational num_2(stack.pop());
	stack.push(num_2 - num_1);
}

void Calculator::multiply() {
	Rational num_1(stack.pop());
	Rational num_2(stack.pop());
	stack.push(num_1 * num_2);
}

void Calculator::divide() {
	Rational num_1(stack.pop());
	Rational num_2(stack.pop());
	stack.push(num_2 / num_1);
}

void Calculator::duplicate() {
	stack.push(stack.top());
}

void Calculator::reverse() {
	Rational num_1(stack.pop());
	Rational num_2(stack.pop());
	stack.push(num_1);
	stack.push(num_2);
}

void Calculator::print() {
	if (stack.empty()) return;
	cout << stack.top() << endl;
}

void Calculator::clear() {
	while (!stack.empty()) stack.pop();
}

void Calculator::print_all() {
	cout << stack << endl;
}

void Calculator::negate() {
	Rational num(stack.pop());
	stack.push(num * -1);
}

void Calculator::match() {
	Pred pred(stack.pop());
	stack.push(stack.count_if(pred));
}

void Calculator::quit() {
	quit_bool = true;
}

void Calculator::find_operation(string input) {
	if (input == "+") add();
	else if (input == "-") subtract();
	else if (input == "*") multiply();
	else if (input == "/") divide();
	else if (input == "d") duplicate();
	else if (input == "r") reverse();
	else if (input == "p") print();
	else if (input == "c") clear();
	else if (input == "a") print_all();
	else if (input == "n") negate();
	else if (input == "m") match();
	else if (input == "q") quit();
	else push(Rational(atoi(input.c_str())));
}

int main() {
	Calculator calc;
	string input;
	while(cin >> input) {
		calc.find_operation(input);
		if (calc.quit_bool) break;
	}
	return 0;
}

