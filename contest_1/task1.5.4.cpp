/*Дано выражение в инфиксной записи. Вычислить его, используя перевод выражения
в постфиксную запись.
Выражение не содержит отрицительных чисел. Количество операций ≤ 100.

Выполнил : Lev "Crashdown" Vinokurov

*/
#include <iostream>

using namespace std;


struct MyStack{
    int tail;
    int capacity;
    int* buffer;

    MyStack(){
        tail = 0;
        capacity = 8;
        buffer = new int[capacity];
    }
    ~MyStack(){
        delete[] buffer;
    }

    bool isEmpty(){
        return tail==0;
    }

    void push (int val){
        if(tail == capacity - 1){
            int* temp = new int[capacity * 2];
            for(int i = 0; i < capacity; ++i){
                temp[i] = buffer[i];
            }
            delete[] buffer;
            buffer = temp;
            capacity *= 2;
        }
        buffer[tail] = val;
        tail++;
    }

    int pop() {
        if(isEmpty()){
            return -1;
        }
        int res = buffer[--tail];
        return res;
    }

    int peek() {
        if(isEmpty()){
            return -1;
        }
        return buffer[tail - 1];
    }
};

int getPriority (int action){
    /*
    action : id

    + : -1
    - : -2
    * : -3
    / : -4
    ( : -5
    ) : -6

    */
    switch (action){
        case -1 : return 1;
        case -2 : return 1;
        case -3 : return 2;
        case -4 : return 2;
    }
    return 0;
}

int charToInt (char c){

    switch (c){
            case '+' :
                return -1;
            case '-' :
                return -2;
            case '*' :
                return -3;
            case '/' :
                return -4;
            case '(' :
                return -5;
            case ')' :
                return -6;
            default :
                return c - (int)'0';
        }
}

int postfixCount(int* postfix, int postfixCapacity){
    //стек для чисел
    MyStack* numbers = new MyStack();
    int current = 0;
    for(int i = 0; i < postfixCapacity; i++){
        current = postfix[i];
        if(current >= 0){
            // если "1234567890"
            numbers->push(current);
        }
        else{
            //иначе выполняем действие и запихиваем
            //результат обратно в стек
            int num1 = numbers->pop();
            int num2 = numbers->pop();
            int res = 0;
            switch(current){
                case -1 :
                    res = num1 + num2;
                    break;
                case -2 :
                    res = num2 - num1;
                    break;
                case -3 :
                    res = num1 * num2;
                    break;
                case -4 :
                    res = num2 / num1;
                    break;
            }
            numbers->push(res);
        }
    }
    int res =  numbers->pop();
    delete numbers;
    return res;
}

int infixToPostfix(string str){
    //стек для операторов
    MyStack* actions = new MyStack();
    int length = str.size();
    int* postfix = new int[length];
    int posString = 0;
    int postfixCapacity = 0;
    int currInt = 0;
    while(posString < length){

        currInt = charToInt(str[posString]);

        //посимвольное считывание многозначного числа
        if(currInt >= 0){
            int i = 1;
            while(posString + i < length && isdigit(str[posString + i])){
                currInt = currInt * 10 + charToInt(str[posString + i]);
                i++;
            }
            posString += i - 1;
        }


        if(currInt >= 0){
            // если "1234567890"
            postfix[postfixCapacity++] = currInt;
        } else if(currInt == -5){
            // если "("
            actions->push(currInt);
        } else if(currInt == -6){
            // если ")"
            int upAction = actions->pop();
            while(upAction != -5){
                postfix[postfixCapacity++] = upAction;
                upAction = actions->pop();
            }
        } else {
            // если " +*-/ "
            while(!actions->isEmpty()){
                    //выталкиваем операторы с бОльшим приоритерот
                    if(getPriority(actions->peek()) < getPriority(currInt)){
                        break;
                    }
                    postfix[postfixCapacity++] = actions->pop();
            }
            actions->push(currInt);
        }

        posString++;
    }
    //выталкиваем что осталось
    while(!actions->isEmpty()){
            postfix[postfixCapacity++] = actions->pop();
        }

    delete actions;

    return postfixCount(postfix, postfixCapacity);

}


int main(){

    string str;
    cin >> str;
    cout << infixToPostfix(str);

    return 0;
}
