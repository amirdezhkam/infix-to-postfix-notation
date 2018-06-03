#include <iostream>
using namespace std;

// Data Structure for Stack
class Stack {
private:
    int top_pointer = 0;
    char* values;
    int max_size;
    
public:
    Stack(int max_size) : max_size(max_size) {
        this -> values = new char[this -> max_size];
    }
    
    bool is_empty() {
        if (this -> top_pointer == 0) {
            return true;
        }
        else {
            return false;
        }
    }
    
    bool is_full() {
        if (this -> top_pointer == this -> max_size) {
            return true;
        }
        else {
            return false;
        }
    }
    
    void push(char value) {
        if (is_full()) {
            throw invalid_argument("The stack is full. ");
        }
        else {
            this -> values[top_pointer] = value;
            top_pointer++;
        }
    }
    
    char pop() {
        if (is_empty()) {
            throw invalid_argument("The stack is empty. ");
        }
        else {
            this -> top_pointer--;
            return this -> values[top_pointer];
        }
    }
    
    char get_top() {
        return this -> values[top_pointer - 1];
    }
};

// Function to Check Whether a Character is an Operator or not
bool is_operator(char ch) {
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
        return true;
    }
    else {
        return false;
    }
}

// Function to Check Precedence of Operators
bool check_precedence(char ch, char in_stack) {
    if ((ch == '*' || ch == '/') &&
        (in_stack == '+' || in_stack == '-')) {
        return true;
    }
    else {
        return false;
    }
}

// Function to Convert "Infix Notation" to "Postfix Notation"
string infix_to_postfix(string infix_notation) {
    string postfix_notation = "";
    int length_of_string = int(infix_notation.length());
    Stack stack(length_of_string);
    
    for (int i = 0; i < length_of_string; i++) {
        char ch = infix_notation[i];
        
        if (ch == '(') {
            stack.push(ch);
        }
        
        else if (isdigit(ch)) {
            postfix_notation += ch;
        }
        
        else if (is_operator(ch)) {
            if (check_precedence(ch, stack.get_top()) ||
                !is_operator(stack.get_top())) {
                stack.push(ch);
            }
            else if (!stack.is_empty()) {
                postfix_notation += stack.pop();
                
                while (!stack.is_empty() &&
                       !check_precedence(ch, stack.get_top())) {
                    postfix_notation += stack.pop();
                }
            }
            
            if (!stack.is_empty() &&
                check_precedence(ch, stack.get_top())) {
                stack.push(ch);
            }
        }
        
        else if (ch == ')') {
            while (!stack.is_empty() && stack.get_top() != '(') {
                postfix_notation += stack.pop();
            }
            
            if (!stack.is_empty() && stack.get_top() == '(') {
                stack.pop();
            }
        }
    }
    
    while (!stack.is_empty()) {
        postfix_notation += stack.pop();
    }
    
    return postfix_notation;
}

int main() {
    // Testing the Program
    string infix_notaion = "(((((1+2)/(3-4))+5)*6)-7)";
    
    cout << "The postfix notation of \"" << infix_notaion <<
    "\" is \"" << infix_to_postfix(infix_notaion) << "\". \n";
}
