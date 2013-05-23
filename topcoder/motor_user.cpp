#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#define PARENT(i) ((i-1)/2)
#define LEFT(i) (i*2+1)
#define RIGHT(i) (i*2+2)
using std::string;
using std::vector;
using std::min;

class VendingMachine {
private:
    class Node {
    public:
        int price;
        int column;
        bool operator>(Node &b) {
            if (price > b.price || price==b.price && column<b.column) {
                return true;
            }
            return false;
        }
    };
    void modifyHeap(vector<Node> &sorted_pri_pos, int index);
    //build max-heap for sorted_pri_pos and store heap index of column in column-index
    void buildHeap(vector<Node> &sorted_pri_pos, vector<int> &column_index);
    void decreaseKey(vector<Node> &sorted_pri_pos, vector<int> &column_index,
                int column, int decrease_price);
    vector<int> parsePrice(string prices);
    void parsePurchases(string purchase, int &row, int &column , int &time);
public:
    int motorUse(vector<string> prices, vector<string> purchases);

};
vector<int> VendingMachine::parsePrice(string prices) {
    vector<int> result;
    char buff[100];
    strncpy(buff, prices.c_str(), sizeof(buff)-1);
    buff[sizeof(buff)-1] = '\0';
    char *pre, *p;
    pre = buff;
    p = strchr(pre, ' ');
    while (p != NULL) {
        *p = '\0';
        result.push_back(atoi(pre));
        pre = p+1;
        p = strchr(pre, ' ');
    }
    result.push_back(atoi(pre));
    return result;
}
void VendingMachine::parsePurchases(string purchase, int &row, int &column, int &time) {
    char buff[100];
    strncpy(buff, purchase.c_str(), sizeof(buff)-1);
    buff[sizeof(buff)-1] = '\0';
    char *pre, *p;
    pre = buff;
    p = strchr(pre, ',');
    *p = '\0';
    row = atoi(pre);
    pre = p+1;
    p = strchr(pre, ':');
    *p = '\0';
    column = atoi(pre);
    pre = p+1;
    time = atoi(pre);
}
int VendingMachine::motorUse(vector<string> prices, vector<string> purchases){
    int pos=0;
    vector<vector<int> > pri(prices.size());
    int size = prices.size();
    int column_size = 0;
    vector<Node> sorted_pri_pos;
    vector<int> column_index;
    for (pos=0; pos < size; ++pos) {
        pri[pos] = parsePrice(prices[pos]);
    }
    column_size = pri[0].size();
    sorted_pri_pos.resize(column_size, Node());
    column_index.resize(column_size, 0);
    int price=0;
    for (pos=0; pos < column_size; ++pos) {
        price =0;
        for (int row=0; row < size; ++row) {
            price += pri[row][pos];
        }
        sorted_pri_pos[pos].price = price;
        sorted_pri_pos[pos].column = pos;
    }
    int result=0;
    int rotate_time = 0;
    int row, column, time;
    pos = 0;
    buildHeap(sorted_pri_pos, column_index);
    for (vector<string>::iterator it= purchases.begin(); it != purchases.end();
            ++it) {
        parsePurchases(*it, row, column, time);
        std::cout<< row<<','<<column<<':'<<time<<'\t'<<pri[row][column]<<std::endl;

        if (pri[row][column] == 0) {
            return -1;
        }
        if (time >= rotate_time) {
            if (sorted_pri_pos[0].column != pos) {
                //rotate expensive column
                result += min((pos+column_size-sorted_pri_pos[0].column)%column_size, (sorted_pri_pos[0].column+column_size-pos)%column_size);
                pos = sorted_pri_pos[0].column;
            }
        }
        rotate_time = time + 5;
        if (column != pos) { //should rotate and sell item
            result += min((pos+column_size-column)%column_size,
                    (column+column_size-pos)%column_size);
            pos = column;
        }
        decreaseKey(sorted_pri_pos, column_index, column, pri[row][column]);
        pri[row][column] = 0;
    }
    if (sorted_pri_pos[0].column != pos) {
        result += min((pos+column_size-sorted_pri_pos[0].column)%column_size, (sorted_pri_pos[0].column+column_size-pos)%column_size);
        pos = sorted_pri_pos[0].column;
    }
    return result;
}
void VendingMachine::modifyHeap(vector<Node> &sorted_pri_pos, int index) {
    int father=0; 
    int left = 0;
    int right = 0;
    Node tmp;
    father = index;
    int last = PARENT(sorted_pri_pos.size()-1)+1;
    while (father < last) {
        left = LEFT(father);
        right = RIGHT(father);
        index = father;
        if (sorted_pri_pos[left] > sorted_pri_pos[father]) {
            index = left;
        }
        if (sorted_pri_pos[right] > sorted_pri_pos[index]) {
            index = right;
        }
        if (index == father) {
            break;
        } else {
            //swap index father
            tmp = sorted_pri_pos[index];
            sorted_pri_pos[index] = sorted_pri_pos[father];
            sorted_pri_pos[father] = tmp;
            father = index;
        }
    }
}
void VendingMachine::buildHeap(vector<Node> &sorted_pri_pos, vector<int> &column_index) {
    int size = sorted_pri_pos.size();
    for (int index=PARENT(size-1); index>=0; --index) {
        modifyHeap(sorted_pri_pos, index);
    }
    //record column_index
    for (int i=0; i<size; ++i) {
        column_index[sorted_pri_pos[i].column] = i;
    }
}
void VendingMachine::decreaseKey(vector<Node> &sorted_pri_pos, vector<int> &column_index,
            int column, int decrease_price) {
    int father = column_index[column];
    sorted_pri_pos[father].price -= decrease_price;
    int left = 0;
    int right = 0;
    int index = 0;
    int last = PARENT(sorted_pri_pos.size()-1)+1;
    Node tmp;
    while (father < last) {
        left = LEFT(father);
        right = RIGHT(father);
        index = father;
        if (sorted_pri_pos[left] > sorted_pri_pos[index]) {
            index = left;
        }
        if (sorted_pri_pos[right] > sorted_pri_pos[index]) {
            index = right;
        }
        if (index == father) {
            break;
        } else {
            //swap index and father and record the change in column_index
            tmp = sorted_pri_pos[index];
            sorted_pri_pos[index] = sorted_pri_pos[father];
            sorted_pri_pos[father] = tmp;
            column_index[sorted_pri_pos[father].column] = father;
            column_index[sorted_pri_pos[index].column] = index;
        }
    }
}
int main() {

	VendingMachine vm;
	vector<string> prices(1, "100 100 100");
	vector<string> purchases;
	purchases.push_back("0,0:10");
	purchases.push_back("0,0:11");
	int r = vm.motorUse(prices, purchases);
    std::cout << r << std::endl;
    return 0;
}
