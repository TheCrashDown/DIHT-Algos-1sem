/* Task : Алгоритм сжатия данных Хаффмана

   developed by Crashdown
    
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <memory>

#include "Huffman.h"

typedef unsigned char byte;
typedef std::map<byte, std::string> encodeTable;
typedef std::map<std::string, byte> decodeTable;


//=======================node===========================//
struct Node
{
	//	символ
    byte symb = 0;
    //	число встреч
    int count = 0;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
    Node(byte _symb, int _count) : symb(_symb), count(_count){}
};

bool compareNode(const std::shared_ptr<Node> a, const std::shared_ptr<Node> b){
    return a->count > b->count;
}

//======================coding==========================//

void    Encode(IInputStream& original, IOutputStream& compressed);
void    Decode(IInputStream& compressed, IOutputStream& original);

void    buildTree(std::vector<std::shared_ptr<Node>>& heap, std::map<byte, int> count);
void    buildCodeTable(encodeTable& codeTable, std::shared_ptr<Node> root, std::string code);

void    writeByte(std::string& tree, byte symb);
void    writeInteger(std::string& str, int x);

void    writeTree(std::shared_ptr<Node> root, std::string& tree);
void    writeCompressedFile(std::string& original, std::string& compressed, encodeTable codeTable);
int     fillStringToBytes(std::string& original);
void    writeStringToStream (IOutputStream& compressed, std::string str);
void    writeEncodedToStream(IOutputStream& compressed, int codeTableSize, int filledBits, std::string outString);

int 	readIntegerFromStream(IInputStream& stream);
byte 	readByte(std::string& str, int& pos);

void 	readCodeTable(std::string& input, decodeTable& codeTable, int codeTableSize, int& pos, std::string code);
void 	readAndDecodeFile(std::string& input, IOutputStream& decoded, decodeTable& codeTable, int pos, int filledBits);



//==========================================================================//
//==========================================================================//



//  функция строит дерево, используя кучу
void buildTree(std::vector<std::shared_ptr<Node>>& heap, std::map<byte, int> count){

    for(auto it = count.begin(); it != count.end(); ++it){
        heap.push_back(std::make_shared<Node>(it->first, it->second));
    }
    std::make_heap(heap.begin(), heap.end(), compareNode);

    //  объединяем элементы с наименьшими приоритетами, кидаем их обратно в кучу,
    //  добавляем указатели на потомков
    //  в итоге в куче остается 1 элемент - корень дерева
    while(true){
        if(heap.size() == 1){
            break;
        }
        //первый элемент (будущий левый потомок)
        pop_heap(heap.begin(), heap.end(), compareNode);
        std::shared_ptr<Node> left = heap.back();
        heap.pop_back();

        //второй элемент (будущий правый потомок)
        pop_heap(heap.begin(), heap.end(), compareNode);
        std::shared_ptr<Node> right = heap.back();
        heap.pop_back();

        //собираем новый элемент
        std::shared_ptr<Node> tmp = std::make_shared<Node>(0, left->count + right->count);
        tmp->left = left;
        tmp->right = right;

        //пихаем его в кучу
        heap.push_back(tmp);
        push_heap(heap.begin(), heap.end(), compareNode);
    }
}


//  функция строит таблицу ассоциаций <символ-код> на осове построенного дерева
void buildCodeTable(encodeTable& codeTable, std::shared_ptr<Node> root, std::string code = ""){
    if(root->left == nullptr && root->right == nullptr){
        codeTable[root->symb] = code;
    }
    if(root->left != 0){
        buildCodeTable(codeTable, root->left, code + "0");
    }
    if(root->right != 0){
        buildCodeTable(codeTable, root->right, code + "1");
    }
}


//  функция побитово записывает данный символ в конец строки
void writeByte(std::string& str, byte symb){
    int pos = 0;
    std::string tmp = "";
    while(pos < 8){
        tmp = std::to_string(symb % 2) + tmp;
        symb /= 2;
        pos++;
    }
    str += tmp;
}


//  функция побитово записывает данной число типа int в конец строки
void writeInteger(std::string& str, int x){
    int pos = 0;
    std::string tmp = "";
    while(pos < 32){
        tmp = std::to_string(x % 2) + tmp;
        x /= 2;
        pos++;
    }
    str += tmp;
}


/*  функция записывает таблицу кодов в данную строку

    структура :
        находимся не в узле - печатаем "1"
        находимся в узле    - печатаем "0", затем 8 бит - символ

    для восстановления данных достаточно идти по единицам до
    первого нуля, при встрече нуля - читать следующие 8 бит разом
*/
void writeTree(std::shared_ptr<Node> root, std::string& tree){
    if(root == nullptr){
        return;
    }
    if(root->left == nullptr){
        tree += "0";
        writeByte(tree, root->symb);
    } else {
        tree += "1";
        writeTree(root->left, tree);
        writeTree(root->right, tree);
    }
}


//  функция кодирует строку и записывает в compressed
void writeCompressedFile(std::string& compressed, std::string& original, encodeTable codeTable){
    byte tmp = 0;
    for(int i = 0; i < original.size(); ++i){
        compressed += codeTable[original[i]];
    }
}


/*	функция наполняет строку в конце незначащими битами до целого числа битов
	и возвращает число добавленных символов
*/
int fillStringToBytes(std::string& original){
    int num = 0;
    while(original.size() % 8 != 0){
        original += "0";
        num++;
    }
    return num;
}


/*  функция записывает строку в поток
        алгоритм :
            * собираем биты в байт
            * отсылаем байт в поток
            * начинаем собирать следующий байт

        pos         -   текущая позиция в строке
        posByte     -   количество собранных битов (если 8, то пора отсылать готовый байт)
*/
void writeStringToStream(IOutputStream& compressed, std::string str){
    int pos = 0;
    int posByte = 0;
    byte tmp = 0;

    while(pos <= str.size()){
        if(posByte < 8){
            tmp *= 2;
            tmp += (str[pos] - '0');
            pos++;
            posByte++;
        } else if(posByte > 0){
            compressed.Write(tmp);
            posByte = 0;
        }
    }
}


//  функция записи в поток вывода
void writeEncodedToStream(IOutputStream& compressed, int codeTableSize, int filledBits, std::string outString){

    //  записываем ведущие байты
    std::string tmp = "";
    writeInteger(tmp, codeTableSize);
    writeInteger(tmp, filledBits);

    writeStringToStream(compressed, tmp);

    //  записываем строку с таблицей и закодированным файлом
    writeStringToStream(compressed, outString);

}


//  функция читает из потока 4 байта и собирает из них int
int readIntegerFromStream(IInputStream& stream){
    int res = 0;
    byte tmp = 0;
    std::string tmpS = "";
    for(int i = 0; i < 4; ++i)
    {
        stream.Read(tmp);
        writeByte(tmpS, tmp);
    }

    for (int i = 0; i < tmpS.size(); ++i)
    {
        res *= 2;
        res += tmpS[i] - '0';
    }

    return res;
}


//  функция читает из строки 8 символов и собирает из них байт
byte readByte(std::string& str, int& pos){
    byte tmp = 0;
    int count = 0;
    while(count < 8){
        tmp *= 2;
        tmp += str[pos] - '0';
        pos++;
        count++;
    }
    return tmp;

}


//  функция читает из входной строки таблицу кодов и пихает их в map-таблицу codeTable
void readCodeTable(std::string& input, decodeTable& codeTable, int codeTableSize, int& pos, std::string code = ""){
    if(pos >= codeTableSize){
        return;
    }
    if(input[pos] == '1'){
        pos++;
        readCodeTable(input, codeTable, codeTableSize, pos, code + "0");
        readCodeTable(input, codeTable, codeTableSize, pos, code + "1");
    } else {
        pos++;
        codeTable[code] = readByte(input, pos);
    }
}


/*  функция читает данные и оставшейся части строки,
    пренебрегая незначащими битами, и декодирует их,
    используя таблицу codeTable
*/
void readAndDecodeFile(std::string& input, IOutputStream& decoded, decodeTable& codeTable, int pos, int filledBits){
    std::string currentCode = "";
    while(pos < input.size() - filledBits){
        currentCode += input[pos];
        if(codeTable.find(currentCode) != codeTable.end()){
            decoded.Write(codeTable[currentCode]);
            currentCode = "";
        }
        pos++;
    }

}

void Encode(IInputStream& original, IOutputStream& compressed)
{
	/*  структура вывода :
            4 байта             ---   размер таблицы с кодами
            4 байта             ---   количество нензачащих битов в конце строки (N)

        в строке outString :
            таблица с кодами
            закодированная строка

        остальное будет занесено в поток вручную перед записью строки
    */


    //  запоминаем входную строку
    std::string input = "";

    //  подсчет количеств вхождений символов
    std::map<byte, int> count;
    byte tmp = 0;
    while(original.Read(tmp)){
        input += tmp;
        count[tmp]++;
    }

    //  строим дерево кодов, используя кучу
    //  наименьшие приоритеты идут наверх
    std::vector<std::shared_ptr<Node>> heap;
    buildTree(heap, count);

    //  строим таблицу с кодами
    encodeTable codeTable;
    buildCodeTable(codeTable, heap[0]);

    //  запись дерева в строку
    std::string outString;
    writeTree(heap[0], outString);

    //  запоминаем размер таблицы кодов в битах
    int codeTableSize = outString.size();

    //  запись последовательности
    writeCompressedFile(outString, input, codeTable);

    //  заполняем стоку до незначащими битами до целого цисла байтов
    int filledBits = fillStringToBytes(outString);

    //  записываем все в поток
    writeEncodedToStream(compressed, codeTableSize, filledBits, outString);
}

void Decode(IInputStream& compressed, IOutputStream& original)
{
    //  читаем ведущие байты
    int codeTableSize = readIntegerFromStream(compressed);
    int filledBits = readIntegerFromStream(compressed);

    //  читаем оставшиеся байты - таблица и файл
    std::string input = "";
    byte tmp = 0;
    while(compressed.Read(tmp)){
        writeByte(input, tmp);
    }

    //  читаем таблицу с кодами
    int pos = 0;
    decodeTable codeTable;
    readCodeTable(input, codeTable, codeTableSize, pos);

    //  читаем + декодируем файл
    pos = codeTableSize;
    readAndDecodeFile(input, original, codeTable, pos, filledBits);
}
