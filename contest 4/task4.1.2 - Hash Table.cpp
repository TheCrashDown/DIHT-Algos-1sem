/* Task :
   Реализуйте структуру данных типа “множество строк” на основе динамической
   хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из
   строчных латинских букв. Хеш-функция строки должна быть реализована с помощью
   вычисления значения многочлена методом Горнера.
   Начальный размер таблицы должен быть равным 8-ми.
   Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент
   заполнения таблицы достигает 3/4.
   Структура данных должна поддерживать операции добавления строки в множество,
   удаления строки из множества и проверки принадлежности
   данной строки множеству.

   Для разрешения коллизий используйте двойное хеширование.

   developed by Crashdown
    
*/
#include <iostream>
#include <vector>
#include <string>
#include <memory>

class HashTable
{
private:

	struct Node
	{
		std::string str = "";
		bool deleted = false;

		Node(std::string& _str) : str(_str), deleted(false){}

	};

	const int CONST_HASH1 = 733;
	const int CONST_HASH2 = 311;
	const float OVERLOAD = 0.75;
	const int START_SIZE = 8;

	int hash1(std::string& str);
	int hash2(std::string& str);

	void reHash();

	//	вместимость таблицы
	int capacity = 0;
	//	реальный размер таблицы
	int tableSize = 0;

	std::vector< std::shared_ptr<Node> > data;

public:

	bool find(std::string& str);
	bool insert(std::string& str);
	bool remove(std::string& str);

	HashTable() : capacity(START_SIZE) {
		data.resize(capacity, nullptr);
	}

	~HashTable(){}
};

//==================================MAIN==================================//

int main()
{
	HashTable hashTable = HashTable();

	char type = 0;
	std::string str = "";

	std::cin >> type >> str;

	while(!std::cin.eof()){

		bool doneClear = false;

		switch(type){
			case '+' :
				doneClear = hashTable.insert(str);
				break;
			case '-' :
				doneClear = hashTable.remove(str);
				break;
			case '?' :
				doneClear = hashTable.find(str);
				break;
		}

		if(doneClear){
			std::cout << "OK\n";
		} else {
			std::cout << "FAIL\n";
		}

		std::cin >> type >> str;
	}

    return 0;
}


//========================================================================//


int HashTable::hash1(std::string& str){
	long long hash = 0;
	for(int i = 0; i < str.size(); ++i){
		hash = (hash * CONST_HASH1 + str[i]) % capacity;
	}
	return hash;
}


int HashTable::hash2(std::string& str){
	long long hash = 0;
	for(int i = 0; i < str.size(); ++i){
		hash = (hash * CONST_HASH2 + str[i]) % capacity;
	}
	return (hash * 2 + 1) % capacity;
}

bool HashTable::insert(std::string& str){
	if(find(str)){
		return false;
	}

    ++tableSize;

	if(tableSize >= (int)(OVERLOAD * capacity)){
		reHash();
	}

	int hashed1 = hash1(str);
	int hashed2 = hash2(str);

	int pos = hashed1;

	while(data[pos] != nullptr && data[pos]->deleted != true){
		pos = (pos + hashed2) % capacity;
	}

	data[pos] = std::make_shared<Node> (str);

	return true;
}


bool HashTable::find(std::string& str){
	int hashed1 = hash1(str);
	int hashed2 = hash2(str);

	int pos = hashed1;

	while(data[pos] != nullptr){
		if(data[pos]->str == str && !data[pos]->deleted){
			return true;
		}
		pos = (pos + hashed2) % capacity;
	}

	return false;
}


bool HashTable::remove(std::string& str){
	if(!find(str)){
		return false;
	}

	int hashed1 = hash1(str);
	int hashed2 = hash2(str);

	int pos = hashed1;

	while(data[pos]->str != str){
		pos = (pos + hashed2) % capacity;
	}

	data[pos]->str = "";
	data[pos]->deleted = true;

	return true;
}


void HashTable::reHash(){
	std::vector<std::string> tmp;

	for(int i = 0; i < capacity; ++i){
		if(data[i] != nullptr && !data[i]->deleted){
			tmp.push_back(data[i]->str);
		}
	}

	data.clear();

    capacity *= 2;

    tableSize = 0;

	data.resize(capacity, nullptr);

	for(int i = 0; i < tmp.size(); ++i){
		insert(tmp[i]);
	}
