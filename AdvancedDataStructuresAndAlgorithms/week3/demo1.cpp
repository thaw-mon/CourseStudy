#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <vector>
#include <algorithm>

using namespace std;

/*
##### 1:牛的选举 ######
描述
现在有N（1<=N<=50000）头牛在选举它们的总统，
选举包括两轮：第一轮投票选举出票数最多的K（1<=K<=N）头牛进入第二轮；第二轮对K头牛重新投票，票数最多的牛当选为总统。
现在给出每头牛i在第一轮期望获得的票数Ai（1<=Ai<=1,000,000,000），以及在第二轮中（假设它进入第二轮）期望获得的票数Bi（1<=Bi<=1,000,000,000），
请你预测一下哪头牛将当选总统。幸运的是，每轮投票都不会出现票数相同的情况。  
输入
第1行：N和K
第2至N+1行：第i+1行包括两个数字：Ai和Bi
输出
当选总统的牛的编号（牛的编号从1开始）
*/

class wolf{
public:
    int no;
    int a;
    int b;
    wolf(int _no,int _a, int _b):no(_no),a(_a),b(_b){};
};

bool compareFirst(wolf &w1, wolf &w2){
    return w1.a > w2.a;
}

//从大到小排序
void mySort(vector<wolf> &array) {
  int n = array.size();
  for (int i = 0; i < n; i++) {
    int p = i; //选择最大的a的索引
    for (int j = i + 1; j < n; j++) {
      if (array[j].a > array[p].a) {
        p = j;
      }
    }
    //交换数组
    wolf temp = array[i];
    array[i] = array[p];
    array[p] = temp;
  }
}

int main(){
    int n,k;
    cin >> n >> k;
    int a,b;
    vector<wolf> wolfs;
    for(int i=1;i<=n;i++){
        cin >> a >>b;
        wolfs.push_back(wolf(i,a,b));
    }
    mySort(wolfs);
     //sort(wolfs.begin(),wolfs.end(),compareFirst);
    int no = -1,v = wolfs[0].b-1;
    for(int i=0;i<k;i++){
        if(wolfs[i].b > v){
            v = wolfs[i].b;
            no = wolfs[i].no;
        }
    }
    cout << no << endl;
    return 0;
}