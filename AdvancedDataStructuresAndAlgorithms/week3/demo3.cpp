#include <iostream>
#include <string>
#include <vector>

using namespace std;


/*
***3. DNA排序******
描述
现在有一些长度相等的DNA串（只由ACGT四个字母组成），请将它们按照逆序对的数量多少排序。
逆序对指的是字符串A中的两个字符A[i]、A[j]，具有i < j 且 A[i] > A[j] 的性质。
如字符串”ATCG“中，T和C是一个逆序对，T和G是另一个逆序对，这个字符串的逆序对数为2。
***输入
第1行：两个整数n和m，n(0<n<=50)表示字符串长度，m(0<m<=100)表示字符串数量

第2至m+1行：每行是一个长度为n的字符串
输出
按逆序对数从少到多输出字符串，逆序对数一样多的字符串按照输入的顺序输出。
*/

class DNA{
public:
    string str;
    int num; //记录逆序对的数量
    DNA(string _str):str(_str) {
        num = reverseNum(_str);
    };
    //计算逆序对的数量
    int reverseNum(string s){
        int res = 0;
        //优化策略:使用hash表记录不同字符的位置
        int bucket[4] = {0}; //分别对应A,C,G,T

        for(int i = 0; i < s.length();i++){
           switch (s[i]) {
           case 'A':
            bucket[0]++;
            res += bucket[1] + bucket[2] + bucket[3];
            break;
           case 'C':
            bucket[1]++;
            res += bucket[2] + bucket[3];
            break;
           case 'G':
            bucket[2]++;
            res += bucket[3];
            break;
           case 'T':
            bucket[3]++;
            break;
           default:
            break;
           }
        }
        return res;
    }
};


//要使用稳定排序法:选择插入排序
void mySort(vector<DNA> &strs){
    for(int i=1;i<strs.size();i++){
        DNA str = strs[i];
        int j = i-1;
        while (j >= 0 && str.num < strs[j].num) {
            //
            strs[j+1] = strs[j];
            j--;
        }
        strs[j+1] = str;
    }
}
int main(){

    int m = 0, n= 0;
    cin >> n >> m;
    vector<DNA> strs;
    string s;
    for(int i=0;i<m;i++){
        cin >> s;
        strs.push_back(DNA(s));
    }
    //对strs进行排序
    mySort(strs);
    for(int i=0;i<strs.size(); i++){
        cout << strs[i].str << endl;
    }
    return 0;
}