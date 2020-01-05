#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using namespace std;

/*
***2:The Peanuts******
***输入
The first line of input contains the test case number T (1 <= T <= 20).
For each test case, the first line contains three integers, M, N and K (1 <= M,
N <= 50, 0 <= K <= 20000). Each of the following M lines contain N integers.
None of the integers will exceed 3000. (M * N) describes the peanut field. The
j-th integer X in the i-th line means there are X peanuts on the point (i, j).
K means Dodo must return to the road in K units of time.
输出
For each test case, print one line containing the amount of peanuts Dodo can
pick.
*/

//判断在一定时间内可以获得花生的最大数目
class Peanut {
public:
  int num; //花生数目
  int x;   //花生位置
  int y;
  Peanut(int _num, int _x, int _y) : num(_num), x(_x), y(_y){};
};

//从大到小int
void mySort(vector<Peanut> &array) {
  int n = array.size();
  for (int i = 0; i < n; i++) {
    int p = i; //选择最大的num的索引
    for (int j = i + 1; j < n; j++) {
      if (array[j].num > array[p].num) {
        p = j;
      }
    }
    //交换数组
    Peanut temp = array[i];
    array[i] = array[p];
    array[p] = temp;
  }
}


int main() {
  int T = 0; //表示实例的数目
  cin >> T;
  while (T > 0) {
    int M, N, K; //分别定义行、列和限时
    cin >> M >> N >> K;
    int temp;
    vector<Peanut> Peanuts;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        cin >> temp;
        if (temp > 0) {
          Peanuts.push_back(Peanut(temp, i, j));
        }
      }
    }
    //如何在规定时间内获取最大的花生数目？注意题目，每次选择最大数目的花生
    //这里可以直接使用sort，为了训练目的，自己写了一个简单选择排序
    mySort(Peanuts);
    int res = 0;                  //
    int x = -1, y = Peanuts[0].y; //
    for (int i = 0; i < Peanuts.size(); i++) {
      int temp_x = Peanuts[i].x;
      int temp_y = Peanuts[i].y;

      int dist1 = abs(temp_x - x) + abs(temp_y - y) +
                  1;          //到达目的地的距离加获取花生的时间
      int dist2 = temp_x + 1; //返程距离
      if (dist1 + dist2 <= K) {
        res += Peanuts[i].num;
        K -= dist1;
        x = temp_x;
        y = temp_y;
      } else {
        break; //返回跳出
      }
    }

    cout << res << endl;
    T--;
  }

  return 0;
}
