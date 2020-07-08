#include "dlist.h"
#include <iostream>
#include <string>

using namespace std;

const char nameCmd[] = {'+', '-', '*', '/',
     'n', 'd', 'r', 'p', 'c', 'a', 'q'};
const unsigned int numCmd = 11;

class BadInputException{};
class NotEnoughException{};
class ZeroDividerException{};

// returns true if the input is a number. 
// first see the first char, if it is digit
//     and so are all the rest char, than input is number
//     throws an instance of invalidInput if there are non-digits among the rest.
// return false is the first char is non-digit, possibly a command.

// Support one pos/neg sign before number,
// if found +/-, check the string behind it.

bool isNum(string in){
    if (((in[0] == '-') || (in[0] == '+')) && in.length() > 1 ) {
        return isNum(in.substr(1));
    }
    else if (isdigit(in[0])){
        for (unsigned int i = 1; i < in.length(); i++){
            if (!isdigit(in[i])){BadInputException e; throw e;}
        }
        return 1;
    } else return 0;
}

// if input is number, call this function.
// transfer the string input into an int number.
int str2num_helper(string st){
    if(st.length() == 1) return atoi(&st[0]);
    else
    {
        return atoi(&st[st.length()-1]) + 
         str2num_helper(st.substr(0,st.length()-1)) * 10;
    }
}
int str2num(string st){
    if (st[0] == '-')
        return - str2num_helper(st.substr(1));
    else if (st[0] == '+')
        return str2num_helper(st.substr(1));
    else
        return str2num_helper(st);    
}

// Return the char representing the commands, if input is 
// a valid command input.
// throws an instance of invalidInput if not valid.
char getCmd(string in){
    if (in.length()>1) {BadInputException e; throw e;}
    char c = in[0];
    for (unsigned int i = 0; i < numCmd; i++) {
        if (c == nameCmd[i]) return c;
    }
    BadInputException e; throw e;
}

void cmd_n(Dlist<int> &numList){
    if (numList.isEmpty())
        {NotEnoughException e; throw e;}
    int *temp1 = numList.removeFront();
    *temp1 = - *temp1;
    numList.insertFront(temp1);
}

void cmd_d(Dlist<int> &numList){
    if (numList.isEmpty())
        {NotEnoughException e; throw e;}
    int *temp1 = numList.removeFront();
    int *num = new int(*temp1);
    numList.insertFront(temp1);
    numList.insertFront(num);
}

void cmd_r(Dlist<int> &numList){
    if (numList.isEmpty())
    {NotEnoughException e; throw e;}
    int *temp1 = numList.removeFront();
    if (numList.isEmpty())
    {numList.insertFront(temp1); NotEnoughException e; throw e;}
    int *temp2 = numList.removeFront();
    numList.insertFront(temp1);
    numList.insertFront(temp2);
}

void cmd_p(Dlist<int> &numList){
    if (numList.isEmpty())
        {NotEnoughException e; throw e;}
    int *temp1 = numList.removeFront();
    cout << *temp1 << endl;
    numList.insertFront(temp1);
}

void cmd_a(Dlist<int> &numList){
    Dlist<int> temp = numList;
    while (!temp.isEmpty()) {
        int *temp1 = temp.removefront();
        cout << *temp1 << " ";
        delete temp1;
    }
    cout << endl;
    temp.~Dlist();
}

void cmd_add(Dlist<int> &numList){
    if (numList.isEmpty())
    {NotEnoughException e; throw e;}
    int *temp1 = numList.removeFront();
    if (numList.isEmpty())
    {numList.insertFront(temp1); NotEnoughException e; throw e;}
    int *temp2 = numList.removeFront();
    int *num = new int(*temp2 + *temp1);
    delete temp1;
    delete temp2;
    numList.insertFront(num);
}

void cmd_multi(Dlist<int> &numList){
    if (numList.isEmpty())
    {NotEnoughException e; throw e;}
    int *temp1 = numList.removeFront();
    if (numList.isEmpty())
    {numList.insertFront(temp1); NotEnoughException e; throw e;}
    int *temp2 = numList.removeFront();
    int *num = new int(*temp2 * *temp1);
    delete temp1;
    delete temp2;
    numList.insertFront(num);
}

void cmd_subtr(Dlist<int> &numList){
    if (numList.isEmpty())
    {NotEnoughException e; throw e;}
    int *temp1 = numList.removeFront();
    if (numList.isEmpty())
    {numList.insertFront(temp1); NotEnoughException e; throw e;}
    int *temp2 = numList.removeFront();
    int *num = new int(*temp2 - *temp1);
    delete temp1;
    delete temp2;
    numList.insertFront(num);
}

void cmd_divide(Dlist<int> &numList){
    if (numList.isEmpty())
    {NotEnoughException e; throw e;}
    int *temp1 = numList.removeFront();
    // 0 cannot be divider
    if (*temp1 == 0)
    {numList.insertFront(temp1); ZeroDividerException e; throw e;}
    if (numList.isEmpty())
    {numList.insertFront(temp1); NotEnoughException e; throw e;}
    int *temp2 = numList.removeFront();
    int *num = new int(*temp2 / *temp1);
    delete temp1;
    delete temp2;
    numList.insertFront(num);
}

int main(){
    char inc;               // carrier for input char if it's a command
    Dlist<int> numList;     // double-ended linked-list as the number stack
    bool num_op;            // false/0 for num-input, true/1 for command input

    while (1) {

        // loop for input, only exits when a valid input
        while (1) {
            string input;
            cin >> input;
            try{
                if (isNum(input)){
                    int *i = new int(str2num(input));
                    numList.insertFront(i);     // insert the number into stack
                    num_op = 0;
                    break;
                } else if (getCmd(input)){
                    inc = getCmd(input);        // save the commander
                    num_op = 1;
                    break;
                } else {
                    BadInputException e; throw e;
                }
            } catch (BadInputException e)
                {cout << "Bad input\n";continue;}
        }

        try {
            if (num_op){
                switch (inc) {
                // negative
                case 'n':
                    cmd_n(numList);
                    break;
                // double
                case 'd':
                    cmd_d(numList);
                    break;
                // reverse
                case 'r':
                    cmd_r(numList);
                    break;
                // print first
                case 'p':
                    cmd_p(numList);
                    break;
                // clear all
                case 'c':
                    numList.~Dlist();
                    break;
                // print all
                case 'a':
                    cmd_a(numList);
                    break;
                // quit
                case 'q':
                    return 0;
                    break;
                // add
                case '+':
                    cmd_add(numList);
                    break;
                // subtract
                case '*':
                    cmd_multi(numList);
                    break;
                // multiply
                case '-':
                    cmd_subtr(numList);
                    break;
                // divide
                case '/':
                    cmd_divide(numList);
                    break;

                default:
                    break;
                }
            }
        }
        catch(NotEnoughException e){cout << "Not enough operands\n"; continue;}
        catch(ZeroDividerException e){cout << "Divide by zero\n"; continue;}
    }

    return 0;
}
