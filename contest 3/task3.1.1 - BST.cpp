/* Task : Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N. 
   Требуется построить бинарное дерево, заданное наивным порядком вставки. Т.е., при добавлении 
   очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое 
   поддерево root; иначе в левое поддерево root. Выведите элементы в порядке in-order (слева направо).
   Рекурсия запрещена.

   developed by Crashdown

*/
#include <iostream>
#include <stack>
#include <utility>
#include <memory>

struct Node{
    int data = 0;
    std::shared_ptr<Node> left = 0;
    std::shared_ptr<Node> right = 0;
    Node(int _data) : data(_data) {}
};

void Insert(std::shared_ptr<Node>& root, std::shared_ptr<Node> node){
    if(root == 0){
        root = node;
        return;
    }
    std::shared_ptr<Node> current = root;
    //ищем куда вставить
    while(true){
        if(node->data < current->data && current->left != 0){
            current = current->left;
            continue;
        }
        if(node->data > current->data && current->right != 0){
            current = current->right;
            continue;
        }
        break;
    }
    //вставляем
    if(node->data < current->data){
        current->left = node;
        return;
    }
    current->right = node;
}

void treePrint(std::shared_ptr<Node> root){
    if(root == 0){
        return;
    }
    //флаг обозначает, надо ли выводить элемент на этой итерации
    //т.е, посещался ли уже левый сын
    std::stack<std::pair<std::shared_ptr<Node>, bool>> recursionStack;
    recursionStack.push(std::make_pair(root, false));

    while(!recursionStack.empty()){
        std::shared_ptr<Node> current = recursionStack.top().first;
        bool currentType = recursionStack.top().second;
        recursionStack.pop();

        if(currentType == false){
            if(current->right != 0){
                recursionStack.push(std::make_pair(current->right, false));
            }

            recursionStack.push(std::make_pair(current, true));

            if(current->left != 0){
                recursionStack.push(std::make_pair(current->left, false));
            }
        }
        if(currentType == true){
            std::cout << current->data << " ";
        }
    }
}

int main()
{
    int n = 0;
    std::cin >> n;
    std::shared_ptr<Node> tree = 0;

    for(int i = 0; i < n; ++i){
        int tmp = 0;
        std::cin >> tmp;
        Insert(tree, std::make_shared<Node>(tmp));
    }
    treePrint(tree);

    return 0;
}
