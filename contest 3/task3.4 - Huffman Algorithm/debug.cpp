/* Task : Алгоритм сжатия данных Хаффмана

   developed by Crashdown
    
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>

#include "Huffman.h"

typedef unsigned char byte;
typedef std::map<byte, std::string> encodeTable;
typedef std::map<std::string, byte> decodeTable;

//======================streams=========================//

struct IInputStream {
    // Возвращает false, если поток закончился
    virtual bool Read(byte& value) = 0;
};

struct IOutputStream {
    virtual void Write(byte value) = 0;
};

struct CInputStream : public IInputStream {
    std::string buffer;
    int pos = 0;
    virtual bool Read(byte& value)
    {
        if (pos < buffer.size()) {
            value = buffer[pos++];
            return true;
        }
        else {
            return false;
        }
    }
};

struct COutputStream : public IOutputStream {
    std::string buffer;

    virtual void Write(byte value)
    {
        buffer += value;
    }
};

//=======================node===========================//
struct Node
{
    byte symb = 0;
    int count = 0;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(byte _symb, int _count) : symb(_symb), count(_count){}
};


bool compareNode(const Node* a, const Node* b){
    return a->count > b->count;
}

//======================coding==========================//

void    Encode(IInputStream& original, IOutputStream& compressed);
void    Decode(IInputStream& compressed, IOutputStream& original);

void    buildTree(std::vector<Node*>& heap, std::map<byte, int> count);
void    buildCodeTable(encodeTable& codeTable, Node* root, std::string code);

void    writeByte(std::string& tree, byte symb);
void    writeInteger(std::string& str, int x);

void    writeTree(Node* root, std::string& tree);
void    writeCompressedFile(std::string& original, std::string& compressed, encodeTable codeTable);
int     fillStringToBytes(std::string& original);
void    writeStringToStream (IOutputStream& compressed, std::string str);
void    writeEncodedToStream(IOutputStream& compressed, int codeTableSize, int filledBits, std::string outString);

int     readIntegerFromStream(IInputStream& stream);
byte    readByte(std::string& str, int& pos);

void    readCodeTable(std::string& input, decodeTable& codeTable, int codeTableSize, int& pos, std::string code);
void    readAndDecodeFile(std::string& input, IOutputStream& decoded, decodeTable& codeTable, int pos, int filledBits);





//======================main==========================//

int main()
{
    setlocale(LC_ALL,"Russian");
    CInputStream in1;
    in1.buffer = "Last night. You see in this world there's two kinds of people my friend - those with loaded guns, and those who dig. You dig.";
    COutputStream out1;
    Encode(in1, out1);

    std::cout << "\n========ez=======\n";
    std::cout << out1.buffer;
    for(int i = 0; i < out1.buffer.size(); ++i){
        std::string tmp = "";
        writeByte(tmp, out1.buffer[i]);
        std::cout << tmp << " ";
    }
    std::cout << "\n========ez=======\n";

    CInputStream in2;
    in2.buffer = out1.buffer;
    COutputStream out2;
    Decode(in2, out2);

    std::cout << "\n========decoded=======\n\n";
    std::cout << out2.buffer << "\n\n";

    std::cout << "ratio: " << 1.0 * out1.buffer.size() / in1.buffer.size() << std::endl;
    std::cout << "is ok: " << (in1.buffer == out2.buffer) << std::endl;



    return 0;
}

//==========================================================================//
//==========================================================================//




void treePrint(Node* root){
    if(root == 0){
        return;
    }
    //  флаг обозначает, надо ли выводить элемент на этой итерации
    //  т.е, посещался ли уже левый сын
    std::stack<std::pair<Node*, bool>> recursionStack;
    recursionStack.push(std::make_pair(root, false));

    while(!recursionStack.empty()){
        Node* current = recursionStack.top().first;
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
                if(current->symb != 0)
            std::cout << "(" << current->symb << ") " << current->count << "\n";
                else
            std::cout << " "<< current->symb << "  " << current->count << "\n";
        }
    }
}


//  функция строит дерево, используя кучу
void buildTree(std::vector<Node*>& heap, std::map<byte, int> count){

    for(auto it = count.begin(); it != count.end(); ++it){
        heap.push_back(new Node(it->first, it->second));
    }
    std::make_heap(heap.begin(), heap.end(), compareNode);

    //  объединяем элементы с наименьшими приоритетами, кидаем их обратно в кучу,
    //  добавляем указатели на потомков
    //  в итоге в куче остается 1 элемент - корень дерева
    while(true){
        /*std::cout << "\n=================\n";
        for(int i = 0; i < heap.size(); i++){
            std::cout << heap[i]->symb << " " << heap[i]->count << "\n";
        }*/
        if(heap.size() == 1){
            break;
        }
        //первый элемент (будущий левый потомок)
        pop_heap(heap.begin(), heap.end(), compareNode);
        Node* left = heap.back();
        heap.pop_back();

        //второй элемент (будущий правый потомок)
        pop_heap(heap.begin(), heap.end(), compareNode);
        Node* right = heap.back();
        heap.pop_back();

        //собираем новый элемент
        Node* tmp = new Node(0, left->count + right->count);
        tmp->left = left;
        tmp->right = right;

        //пихаем его в кучу
        heap.push_back(tmp);
        push_heap(heap.begin(), heap.end(), compareNode);
    }
}


//  функция строит таблицу ассоциаций <символ-код> на осове построенного дерева
void buildCodeTable(encodeTable& codeTable, Node* root, std::string code = ""){
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
void writeTree(Node* root, std::string& tree){
    if(root == nullptr){
        return;
    }
    if(root->left == nullptr){
        tree += "0";
        //tree += root->symb;
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


/*  функция наполняет строку в конце незначащими битами до целого числа битов
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
void writeStringToStream (IOutputStream& compressed, std::string str){
    int pos = 0;
    int posByte = 0;
    byte tmp = 0;

    while(pos <= str.size()){
        if(posByte < 8){
            tmp *= 2;
            tmp += (str[pos] - '0');
            pos++;
            posByte++;
        } else if (posByte > 0){
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

    std::cout << "\ntmS :\n" << tmpS << "\n";
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
        //pos++;
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
    //  запоминаем входную строку
    std::string input = "";

    //  подсчет количеств вхождений символов
    std::map<byte, int> count;
    byte tmp = 0;
    while(original.Read(tmp)){
        input += tmp;
        count[tmp]++;
    }
    for(auto it = count.begin(); it != count.end(); ++it){
        std::cout << it->first << " " << it->second << "\n";
    }

    //  строим дерево кодов, используя кучу
    //  наименьшие приоритеты идут наверх
    std::vector<Node*> heap;
    buildTree(heap, count);

    //  строим таблицу с кодами
    encodeTable codeTable;
    buildCodeTable(codeTable, heap[0]);

    std::cout << "\n=================\n";
    std::cout << "\n=================\n";
    std::cout << "\n=================\n";
    for(auto it = codeTable.begin(); it != codeTable.end(); ++it){
        std::cout << "(" << it->first << ") :   " << it->second << "\n";
    }


    //std::cout << "\n=================\n";
    //std::cout << "=================\n";
   // std::cout << "=================\n";
   // //std::cout << "=================\n";
   // treePrint(heap[0]);

    /*std::cout << "\n=================\n";
    std::cout << "=================\n";
    std::cout << "=================\n";
    std::cout << "=================\n";*/

    /*  структура вывода :
            4 байта             ---   размер таблицы с кодами
            4 байта             ---   количество нензачащих битов в конце строки (N)

        в строке outString :
            таблица с кодами
            закодированная строка

        остальное будет занесено в поток вручную перед записью строки
    */

    //  запись дерева в строку
    std::string outString;
    writeTree(heap[0], outString);

    std::cout << "tree : \n\n";

    for(int i = 0; i < outString.size(); ++i){
        if(i % 8 == 0 && i > 0){
            std::cout << " ";
        }
        std::cout << outString[i];
    }
    std::cout << "\n=================\n";


    //  запоминаем размер таблицы кодов в битах
    int codeTableSize = outString.size();

    //  запись последовательности
    writeCompressedFile(outString, input, codeTable);

    //  заполняем стоку до незначащими битами до целого цисла байтов
    int filledBits = fillStringToBytes(outString);
    std::cout << "\n=================\n";


    std::cout << "\ntableSize :  " << codeTableSize << ", filledBits :  " << filledBits;
    std::cout << "\n=================\n";


    std::cout << "tree + encoded : \n\n";
    for(int i = 0; i < outString.size(); ++i){
        if(i % 8 == 0 && i > 0){
            std::cout << " ";
        }
        std::cout << outString[i];
    }
    std::cout << "\n=================\n";


    //  записываем все в поток
    writeEncodedToStream(compressed, codeTableSize, filledBits, outString);
}

void Decode(IInputStream& compressed, IOutputStream& original)
{
    //  читаем ведущие байты
    int codeTableSize = readIntegerFromStream(compressed);
    int filledBits = readIntegerFromStream(compressed);

    std::cout << "\ntableSize :  " << codeTableSize << ", filledBits :  " << filledBits;
    std::cout << "\n=================\n";

    //  читаем оставшиеся байты - таблица и файл
    std::string input = "";
    byte tmp = 0;
    while(compressed.Read(tmp)){
        writeByte(input, tmp);
    }
    std::cout << "\n=======input======\n";
    for(int i = 0; i < input.size(); ++i){
        if(i % 8 == 0 && i > 0){
            std::cout << " ";
        }
        std::cout << input[i];
    }


    //  читаем таблицу с кодами
    int pos = 0;
    decodeTable codeTable;
    readCodeTable(input, codeTable, codeTableSize, pos);

    std::cout << "\n=================\n";
    std::cout << "\n====decodeTable======\n";
    for(auto it = codeTable.begin(); it != codeTable.end(); ++it){
        std::cout << "" << it->first << " :   (" << it->second << ")\n";
    }

    //  читаем + декодируем файл
    pos = codeTableSize;

    readAndDecodeFile(input, original, codeTable, pos, filledBits);


    /*std::cout << "\n=================\n";
    std::string strr = "01101101";
    int qqq = 0;
    byte weeew = readByte(strr, qqq);
    //std::string qweqwe = "";
    //writeByte(qweqwe, weeew);
    std::cout << weeew <<"\n=================\n";*/


}
