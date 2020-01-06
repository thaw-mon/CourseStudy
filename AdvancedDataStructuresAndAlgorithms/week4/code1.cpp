#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//1. 置换选择排序
//Link: http://dsalgo.openjudge.cn/201409week11/1/

//进行置换选择
/**
 * input : num(输入置换数字) minSatck(小根堆)
 * output : res(置换出来的数字 :小根堆的栈顶元素) 
 * 
**/

class MinStack{
public:
    MinStack(){
        size = 0;
    }
    deque<int> v; //堆栈数据区

    int size;
    int getTop(){
        if(size > 0) return v.front();
        return -1;
    }
    //增加一个节点
    void addNode(int value){
        v.push_back(value);
        
        size++;
        int current = size-1;  //当前值的指针
        while (current > 0 && v[(current-1) / 2] > value)
        {
            /* code */
            v[current] = v[(current-1) / 2];
            current = (current-1) / 2;
        }
        v[current] = value;
    }

    //顶点出栈:不能直接出栈
    void pop(){
        v[0] = v[size-1];
        v.pop_back();
        update(0);
    }
    //使用value更新top值
    void updateTop(int value){
        v[0] = value;
        update(0);
    }
    //修改top值重新更新栈
    void update(int index){
        int value = v[index];
        int current = index; //判断当前节点是否为叶子节点
        while(true){
            if( current * 2 + 1 >= size) break; // 已经是叶子节点
            int minChildPoint = current * 2 + 1; 
            if(minChildPoint + 1 < size && v[minChildPoint] > v[minChildPoint+1]){ //存在右节点
                minChildPoint +=1; //指向右节点
            }
            //父节点大于子节点： swap
            if(value > v[minChildPoint]){
                v[current] = v[minChildPoint];
                current = minChildPoint;
            }
            else { //终止循环
                break;
            }
        }
        v[current] = value;
    }
};

void displacceSelectSort(vector<int> num,MinStack &minStack){
    for(int i=0;i<num.size(); i++){
        int top = minStack.getTop();
        if(num[i] > top){
            minStack.updateTop(num[i]);
        }else{
            minStack.pop();  //栈顶出栈
        }
        cout << top;
        if(i < num.size()-1)
            cout << " ";
    }
    cout << endl;
    
}

int main(){
    int m,n;
    cin >> m >> n;
    vector<int> v(m);
    //获取顺序串
    for(int i=0;i<m;i++){
        int temp;
        cin >> temp;
        v[i] = temp;
    }
    
    //获取排好序的小根堆
    MinStack minStack = MinStack();
    for(int i=0;i<n;i++){
        int temp;
        cin >> temp;
        minStack.addNode(temp);
    }

    //置换选择排序
    displacceSelectSort(v,minStack);
    return 0;
}