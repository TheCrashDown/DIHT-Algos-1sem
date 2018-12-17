/* Task :
   Реализовать очередь с динамическим зацикленным буфером.
   Обрабатывать команды push back и pop front.
   
   developed by Crashdown

*/
#include <cassert>
#include <iostream>

using namespace std;


struct MyQueue {
    int qMaxSize;
    int head;
    int tail;
    int* buffer;

    MyQueue(){
        qMaxSize = 8;
        head = 0;
        tail = 0;
        buffer = new int[qMaxSize];
    }
    ~MyQueue(){
        delete[] buffer;
    }

    void qPushBack (int val){
        if (head == (tail + 1) % qMaxSize){
            int* tmp = new int[qMaxSize * 2];
            for (int i = 0; i < qMaxSize - 1; ++i){
                tmp[i] = buffer[head];
                head = (head + 1) % qMaxSize;
            }
            delete[] buffer;
            buffer = tmp;
            head = 0;
            tail = qMaxSize - 1;
            qMaxSize *= 2;

        }
        buffer[tail] = val;
        tail = (tail + 1) % qMaxSize;
    }

    int qPopFront (){
        if(qEmpty()){
            return -1;
        }
        int res = buffer[head];
        head = (head + 1) % qMaxSize;
        return res;
    }

    bool qEmpty(){
        return head == tail;
    }

    int qSize(){
        if(tail > head){
            return qMaxSize + tail - head;
        }
        return tail - head;
    }

};


int main(){

    MyQueue myQueue;

    int n;
    cin >> n;

    int type = 0;
    int val = 0;

    bool flag = true;

    for(int i = 0; i < n; i++){
        cin >> type >> val;

        if(type == 3){
            myQueue.qPushBack(val);
        }
        else{
            int tmp = myQueue.qPopFront();
            if(tmp != val) {
                flag = false;
            }
        }
    }
    if(flag){
        cout << "YES";
    }
    else{
        cout << "NO";
    }

    return 0;
}
