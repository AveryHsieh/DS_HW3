#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_set>
using namespace std;


//HashTableTest
int main() {
    srand(time(NULL));

    int start, end, repeat;
    cin >> start >> end >> repeat;

    cout << "重複 " << repeat << " 次取平均" << "\n";
    for (int k = start; k < (end + 1); k++)
    {
        double addTotalSpendTime = 0;
        double searchTotalSpendTime = 0;
        for (int n = 0; n < repeat; n++)
        {
            std::unordered_set<int> myHashTable;//initial Hash Table
            double START, END;
            START = clock();
            for (int i = 0; i < pow(2, k); i++)
            {
                myHashTable.insert(rand() % 1073741824 + 1);//update Hash Table
            }
            END = clock();

            addTotalSpendTime += ((END - START) / CLOCKS_PER_SEC);


            double search_START, search_END;
            search_START = clock();
            int sum = 0;
            for (int i = 0; i < pow(10, 5); i++)
            {
                myHashTable.find(rand() % 1073741824 + 1);//search in Hash Table
            }
            search_END = clock();
            searchTotalSpendTime += ((search_END - search_START) / CLOCKS_PER_SEC);
        }
        double addAvrgSpendTime = addTotalSpendTime / repeat;
        double searchAvrgSpendTime = searchTotalSpendTime / repeat;
        cout << endl << "Hash Table新增2^" << k << "個隨機數所需的時間:" << addAvrgSpendTime << " sec" << endl;
        cout << endl << "在存了2^" << k << "筆資料的Hash Table中搜尋十萬筆資料所需的時間:" << searchAvrgSpendTime << " sec" << endl << endl;
    }

}

