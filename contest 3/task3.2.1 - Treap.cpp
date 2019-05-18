/* Task : Дано число N < 106 и последовательность пар целых 
   чисел из [-231, 231] длиной N.
   Построить декартово дерево из N узлов, характеризующихся парами 
   чисел (Xi, Yi). Каждая пара чисел (Xi, Yi) определяет ключ Xi и 
   приоритет Yi в декартовом дереве.
   Добавление узла в декартово дерево выполняйте следующим образом: 
   При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим 
   приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в 
   первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два 
   дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P.
   Построить также наивное дерево поиска по ключам Xi.
   Т.е., при добавлении очередного числа K в наивное дерево с корнем root, 
   если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
   Вычислить разницу глубин наивного дерева поиска и декартового дерева. 
   Разница может быть отрицательна, необходимо вывести модуль разности.

   developed by Crashdown

*/
#include <iostream>
#include <memory>

class BinarySearchTree
{
private:
    struct Node
    {
        int data = 0;
        std::shared_ptr<Node> left = 0;
        std::shared_ptr<Node> right = 0;
        Node(int _data) : data(_data) {}
    };

    std::shared_ptr<Node> root = 0;

public:
    BinarySearchTree(){}
    ~BinarySearchTree(){}

    std::shared_ptr<Node>& getRoot(){
        return root;
    }

    int depthCount(std::shared_ptr<Node> root, int depth = 0){
        if(root == 0){
            return 0;
        }
        return 1 + std::max(depthCount(root->left, depth), depthCount(root->right, depth));
    }

    void push(std::shared_ptr<Node>& root, int data){
        std::shared_ptr<Node> node = std::make_shared<Node>(data);
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
};

class Treap{
private:
    struct Node
    {
        int data = 0;
        int depth = 0;
        std::shared_ptr<Node> left = 0;
        std::shared_ptr<Node> right = 0;
        Node(int _data, int _depth) : data(_data), depth(_depth) {}
    };

    void split(std::shared_ptr<Node> root, std::shared_ptr<Node>& left, std::shared_ptr<Node>& right, int key){
        if (root == 0){
            left = 0;
            right = 0;
            return;
        }
        if(key < root->data){
            split(root->left, left, root->left, key);
            right = root;
            return;
        }
        split(root->right, root->right, right, key);
        left = root;
     }

     std::shared_ptr<Node> root = 0;

public:
    std::shared_ptr<Node>& getRoot(){
        return root;
    }

    std::shared_ptr<Node> makeNode (int key, int depth){
        return std::make_shared<Node> (key, depth);
    }

     void push(std::shared_ptr<Node>& root, int key, int depth){
        std::shared_ptr<Node> node = std::make_shared<Node>(key, depth);
        if(root == 0){
            root = node;
            return;
        }
        if(node->depth < root->depth){
            if(node->data < root->data){
                push(root->left, key, depth);
                return;
            }
            push(root->right, key, depth);
            return;
        }
        split(root, node->left, node->right, node->data);
        root = node;
     }

     int depthCount(std::shared_ptr<Node> root, int depth = 0){
        if(root == 0){
            return 0;
        }
        return 1 + std::max(depthCount(root->left, depth), depthCount(root->right, depth));
     }
};

 int main()
 {
 	BinarySearchTree tree;
    Treap treap;
 	int n = 0;
 	std::cin >> n;
 	for (int i = 0; i < n; ++i)
 	{
 		int key = 0;
 		int depth = 0;
 		std::cin >> key >> depth;
        tree.push(tree.getRoot(), key);
        treap.push(treap.getRoot(), key, depth);
 	}
    std::cout << std::abs(tree.depthCount(tree.getRoot()) - treap.depthCount(treap.getRoot()));

    return 0;
 }
