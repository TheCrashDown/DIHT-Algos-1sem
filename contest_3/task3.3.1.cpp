/*	Task : В одной военной части решили построить в одну шеренгу по росту. 
	Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, 
	а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги. 
	Однако солдаты в процессе прихода и ухода должны были всегда быть выстроены 
	по росту – сначала самые высокие, а в конце – самые низкие. За расстановку 
	солдат отвечал прапорщик, который заметил интересную особенность – все 
	солдаты в части разного роста. Ваша задача состоит в том, чтобы помочь 
	прапорщику правильно расставлять солдат, а именно для каждого приходящего 
	солдата указывать, перед каким солдатом в строе он должен становится. 
	Требуемая скорость выполнения команды - O(log n).

	developed by Crashdown

*/
#include <iostream>
#include <stack>
#include <memory>

class AVLTree
{
private:
	struct Node
	{
		int data = 0;
		unsigned char height = 0;
		int count = 1;
		std::shared_ptr<Node> left = nullptr;
		std::shared_ptr<Node> right = nullptr;

		Node(int _data) : data(_data){}
	};

	std::shared_ptr<Node> root = 0;

	void 	rotateRight(std::shared_ptr<Node>& root);
	void 	rotateLeft(std::shared_ptr<Node>& root);
	void 	updateNode(std::shared_ptr<Node>& root);
	void 	balance(std::shared_ptr<Node>& root);
	int 	getHeight(std::shared_ptr<Node> root);
	int 	getCount(std::shared_ptr<Node> root);
	int 	bFactor(std::shared_ptr<Node> root);

	void 	removeMin(std::shared_ptr<Node>& root);
	std::shared_ptr<Node> 	getMin(std::shared_ptr<Node> root);

public:
	AVLTree(){}
	~AVLTree(){}

	std::shared_ptr<Node>& getRoot(){
        return root;
    }

	void 	insert(std::shared_ptr<Node>& root, int key);
	void	remove(std::shared_ptr<Node>& root, int key);
	int 	findKeyByOrder(std::shared_ptr<Node> root, int pos);
	int 	findOrderByKey(std::shared_ptr<Node> root, int key, int pos = 0);
	void 	removeByOrder(std::shared_ptr<Node>& root, int pos);

};

//=============================================================//
//=============================================================//

int main()
{
	AVLTree tree;

	int n = 0;
    std::cin >> n;
    for(int i = 0; i < n; ++i){
        int type = 0;
        int val = 0;
        std::cin >> type >> val;
        if(type == 1){
            tree.insert(tree.getRoot(), val);
            std::cout << tree.findOrderByKey(tree.getRoot(), val) << "\n";
        } else {
            tree.removeByOrder(tree.getRoot(), val);
        }
    }
    return 0;
}

//=============================================================//
//=============================================================//

int AVLTree::getHeight(std::shared_ptr<Node> root){
	if(root == nullptr){
		return 0;
	}
	return root->height;
}

int AVLTree::getCount(std::shared_ptr<Node> root){
	if(root == nullptr){
		return 0;
	}
	return root->count;
}

int AVLTree::bFactor(std::shared_ptr<Node> root){
    if(root == nullptr){
        return 0;
    }
	return getHeight(root->right) - getHeight(root->left);
}

void AVLTree::updateNode(std::shared_ptr<Node>& root){
	root->height = 1 + std::max(getHeight(root->left),
								getHeight(root->right));
	root->count = 1 + getCount(root->left) + getCount(root->right);
}

void AVLTree::balance(std::shared_ptr<Node>& root){
    if(root == nullptr){
        return;
    }
	updateNode(root);
	//bigLeftRotate
	if(bFactor(root) == 2){
		if(bFactor(root->right) < 0){
			rotateRight(root->right);#include <iostream>
#include <stack>
#include <memory>

class AVLTree
{
private:
	struct Node
	{
		int data = 0;
		unsigned char height = 0;
		int count = 1;
		std::shared_ptr<Node> left = nullptr;
		std::shared_ptr<Node> right = nullptr;

		Node(int _data) : data(_data){}
	};

	std::shared_ptr<Node> root = 0;

	void 	rotateRight(std::shared_ptr<Node>& root);
	void 	rotateLeft(std::shared_ptr<Node>& root);
	void 	updateNode(std::shared_ptr<Node>& root);
	void 	balance(std::shared_ptr<Node>& root);
	int 	getHeight(std::shared_ptr<Node> root);
	int 	getCount(std::shared_ptr<Node> root);
	int 	bFactor(std::shared_ptr<Node> root);

	void 	removeMin(std::shared_ptr<Node>& root);
	std::shared_ptr<Node> 	getMin(std::shared_ptr<Node> root);

public:
	AVLTree(){}
	~AVLTree(){}

	std::shared_ptr<Node>& getRoot(){
        return root;
    }

	void 	insert(std::shared_ptr<Node>& root, int key);
	void	remove(std::shared_ptr<Node>& root, int key);
	int 	findKeyByOrder(std::shared_ptr<Node> root, int pos);
	int 	findOrderByKey(std::shared_ptr<Node> root, int key, int pos = 0);
	void 	removeByOrder(std::shared_ptr<Node>& root, int pos);

};

//=============================================================//
//=============================================================//

int main()
{
	AVLTree tree;

	int n = 0;
    std::cin >> n;
    for(int i = 0; i < n; ++i){
        int type = 0;
        int val = 0;
        std::cin >> type >> val;
        if(type == 1){
            tree.insert(tree.getRoot(), val);
            std::cout << tree.findOrderByKey(tree.getRoot(), val) << "\n";
        } else {
            tree.removeByOrder(tree.getRoot(), val);
        }
    }
    return 0;
}

//=============================================================//
//=============================================================//

int AVLTree::getHeight(std::shared_ptr<Node> root){
	if(root == nullptr){
		return 0;
	}
	return root->height;
}

int AVLTree::getCount(std::shared_ptr<Node> root){
	if(root == nullptr){
		return 0;
	}
	return root->count;
}

int AVLTree::bFactor(std::shared_ptr<Node> root){
    if(root == nullptr){
        return 0;
    }
	return getHeight(root->right) - getHeight(root->left);
}

void AVLTree::updateNode(std::shared_ptr<Node>& root){
	root->height = 1 + std::max(getHeight(root->left),
								getHeight(root->right));
	root->count = 1 + getCount(root->left) + getCount(root->right);
}

void AVLTree::balance(std::shared_ptr<Node>& root){
    if(root == nullptr){
        return;
    }
	updateNode(root);
	//bigLeftRotate
	if(bFactor(root) == 2){
		if(bFactor(root->right) < 0){
			rotateRight(root->right);
		}
		rotateLeft(root);
	}
	//bigLeftRotate
	if(bFactor(root) == -2){
		if(bFactor(root->left) > 0){
			rotateLeft(root->left);
		}
		rotateRight(root);
	}
}

void AVLTree::rotateRight(std::shared_ptr<Node>& root){
	if(root->left == nullptr){
		return;
	}
	std::shared_ptr<Node> tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	updateNode(root);
	updateNode(tmp);
	root = tmp;
}

void AVLTree::rotateLeft(std::shared_ptr<Node>& root){
	if(root->right == nullptr){
		return;
	}
	std::shared_ptr<Node> tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	updateNode(root);
	updateNode(tmp);
	root = tmp;
}

void AVLTree::insert(std::shared_ptr<Node>& root, int key){
	if(root == nullptr){
		root = std::make_shared<Node>(key);
		return;
	}
	if(key < root->data){
		insert(root->left, key);
	} else {
		insert(root->right, key);
	}
	balance(root);
}

std::shared_ptr<AVLTree::Node> AVLTree::getMin(std::shared_ptr<Node> root){
	if(root->left == nullptr){
		return root;
	}
	return getMin(root->left);
}

void AVLTree::removeMin(std::shared_ptr<Node>& root){
	if(root->left == nullptr){
		root = root->right;
		return;
	}
	removeMin(root->left);
	balance(root);
}

void AVLTree::remove(std::shared_ptr<Node>& root, int key){
	if(root == nullptr){
		return;
	}
	if(key < root->data){
		remove(root->left, key);
	} else if(root->data < key){
		remove(root->right, key);
	} else {
		std::shared_ptr<Node> left = root->left;
		std::shared_ptr<Node> right = root->right;
		if(right == nullptr){
			root = left;
			return;
		}
		std::shared_ptr<Node> minChild = getMin(right);
		removeMin(right);
		minChild->right = right;
		minChild->left = left;
		balance(minChild);
		root = minChild;
		return;
	}
	balance(root);
}

void AVLTree::removeByOrder(std::shared_ptr<Node>& root, int pos){
	if(root == nullptr){
		return;
	}
	remove(root, findKeyByOrder(root, pos));
}

int AVLTree::findKeyByOrder(std::shared_ptr<Node> root, int pos){
	if(root == nullptr || pos > root->count - 1){
		return 0;
	}
	if(pos == getCount(root->right)){
		return root->data;
	}
	if(pos < getCount(root->right)){
		return findKeyByOrder(root->right, pos);
	}
	return findKeyByOrder(root->left, pos - getCount(root->right) - 1);
}

int AVLTree::findOrderByKey(std::shared_ptr<Node> root, int key, int pos){
	if(root == nullptr){
		return 0;
	}
	if(root->data == key){
		return pos + getCount(root->right);
	}
	if(key < root->data){
		return findOrderByKey(root->left, key, pos + getCount(root->right) + 1);
	}
	return findOrderByKey(root->right, key, pos);
}

		}
		rotateLeft(root);
	}
	//bigLeftRotate
	if(bFactor(root) == -2){
		if(bFactor(root->left) > 0){
			rotateLeft(root->left);
		}
		rotateRight(root);
	}
}

void AVLTree::rotateRight(std::shared_ptr<Node>& root){
	if(root->left == nullptr){
		return;
	}
	std::shared_ptr<Node> tmp = root->left;
	root->left = tmp->right;
	tmp->right = root;
	updateNode(root);
	updateNode(tmp);
	root = tmp;
}

void AVLTree::rotateLeft(std::shared_ptr<Node>& root){
	if(root->right == nullptr){
		return;
	}
	std::shared_ptr<Node> tmp = root->right;
	root->right = tmp->left;
	tmp->left = root;
	updateNode(root);
	updateNode(tmp);
	root = tmp;
}

void AVLTree::insert(std::shared_ptr<Node>& root, int key){
	if(root == nullptr){
		root = std::make_shared<Node>(key);
		return;
	}
	if(key < root->data){
		insert(root->left, key);
	} else {
		insert(root->right, key);
	}
	balance(root);
}

std::shared_ptr<AVLTree::Node> AVLTree::getMin(std::shared_ptr<Node> root){
	if(root->left == nullptr){
		return root;
	}
	return getMin(root->left);
}

void AVLTree::removeMin(std::shared_ptr<Node>& root){
	if(root->left == nullptr){
		root = root->right;
		return;
	}
	removeMin(root->left);
	balance(root);
}

void AVLTree::remove(std::shared_ptr<Node>& root, int key){
	if(root == nullptr){
		return;
	}
	if(key < root->data){
		remove(root->left, key);
	} else if(root->data < key){
		remove(root->right, key);
	} else {
		std::shared_ptr<Node> left = root->left;
		std::shared_ptr<Node> right = root->right;
		if(right == nullptr){
			root = left;
			return;
		}
		std::shared_ptr<Node> minChild = getMin(right);
		removeMin(right);
		minChild->right = right;
		minChild->left = left;
		balance(minChild);
		root = minChild;
		return;
	}
	balance(root);
}

void AVLTree::removeByOrder(std::shared_ptr<Node>& root, int pos){
	if(root == nullptr){
		return;
	}
	remove(root, findKeyByOrder(root, pos));
}

int AVLTree::findKeyByOrder(std::shared_ptr<Node> root, int pos){
	if(root == nullptr || pos > root->count - 1){
		return 0;
	}
	if(pos == getCount(root->right)){
		return root->data;
	}
	if(pos < getCount(root->right)){
		return findKeyByOrder(root->right, pos);
	}
	return findKeyByOrder(root->left, pos - getCount(root->right) - 1);
}

int AVLTree::findOrderByKey(std::shared_ptr<Node> root, int key, int pos){
	if(root == nullptr){
		return 0;
	}
	if(root->data == key){
		return pos + getCount(root->right);
	}
	if(key < root->data){
		return findOrderByKey(root->left, key, pos + getCount(root->right) + 1);
	}
	return findOrderByKey(root->right, key, pos);
}
