/*	Task :
    Дано невзвешенное дерево. Расстоянием между двумя вершинами будем называть
	количество ребер в пути, соединяющем эти две вершины. Для каждой вершины
	определите сумму расстояний до всех остальных вершин. Время работы должно быть O(n).

    developed by Crashdown
    
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

struct Node
{
	int data = 0;
	//	сумма расстояний до листьев в поддереве
	int sumDist = 0;
	//	кол-во листьев в поддереве
	int count = 0;

	std::vector<int> children;

	int parent;

	Node(){}
	Node(int _data) : data(_data) {}
};


void dfs(std::vector< std::shared_ptr<Node> >& tree, int pos){

	int count = 1;
	int sumDist = 0;

	if(tree[pos]->children.size() == 0){
        tree[pos]->count = 1;
        tree[pos]->sumDist = 0;
        return;
	}

	for(auto child : tree[pos]->children){
		dfs(tree, child);

		count += tree[child]->count ;
		sumDist += tree[child]->sumDist;
	}


	tree[pos]->count = count;
	tree[pos]->sumDist = sumDist + (count - 1);
}

int main()
{
    int n = 0;
    std::cin >> n;

    std::vector< std::shared_ptr<Node> > tree(n);

    for(int i = 0; i < n; ++i){
        tree[i] = std::make_shared<Node>(i);
    }

    for(int i = 0; i < n - 1; ++i){
    	int a = 0;
    	int b = 0;

    	std::cin >> a >> b;

    	if(a > b){
    		std::swap(a, b);
    	}


    	tree[a]->children.push_back(b);
    	tree[b]->parent = a;
    }

    dfs(tree, 0);

    std::vector<int> dist(n);
    dist[0] = tree[0]->sumDist;

    for(int i = 1; i < n; ++i){
    	dist[i] = dist[tree[i]->parent] - tree[i]->count + (n - tree[i]->count);
    }

    for(int i = 0; i < n; ++i){
    	std::cout << dist[i] << "\n";
    }

    return 0;
}
