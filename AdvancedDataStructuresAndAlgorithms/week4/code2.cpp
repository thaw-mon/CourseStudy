#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

//2:败方树
//Link : http://dsalgo.openjudge.cn/201409week11/2

template<class T>
class LoserTree{
private:
    int MaxSize; // 最大选手数
    int n; // 当前选手数
    int LowExt; // 最底层外部结点数
    int offset; // 最底层外部结点之上的结点总数
    int * B; // 败方树数组，实际存放的是下标
    T * L; // 元素数组
    void Play(int p,int lc,int rc,int(*winner)(T A[],int b,int c),int(*loser)(T A[], int b, int c));

public:
    LoserTree(int Treesize =  INT_MAX){
        MaxSize = Treesize;
    }
    ~LoserTree(){delete [] B;}

    void Initialize(T A[], int size,int (*winner)(T A[], int b, int c), int(*loser)(T A[], int b, int c)); // 初始化败方树
    
    int Winner(); // 返回最终胜者索引

    void RePlay(int i, int(*winner)(T A[], int b, int c), int (*loser)(T A[], int b, int c));  // 位置 i 的选手改变后重构败方树

    void Display(){
        for(int i=0;i<=offset;i++){
            cout << L[B[i]];
            if(i==offset) cout << endl;
            else cout << " ";
        }
    }
};
// 成员函数Winner，返回最终胜者 B[0] 的索引
template<class T>
int LoserTree<T>::Winner(){
    return (n)?B[0]:0;
}
template<class T> // 初始化败方树
void LoserTree<T>::Initialize(T A[], int size, int(*winner)(T A[], int b, int c), int(*loser)(T A[], int b, int c)) {
    if (size > MaxSize || size < 2) {
        cout<<"Bad Input!"<< endl << endl; 
        return; 
    }
    n = size; L = A; // 初始化成员变量
    int i,s; // 计算s=2^log(n-1)
    for (s = 1; 2*s <= n-1; s+=s);
    
    LowExt = 2 * (n - s); 
    offset = 2 * s - 1;

    B = new int[offset+1];

    for (i = 2; i <= LowExt; i+=2) // 底层外部
        Play((offset+i)/2, i-1, i, winner, loser);

    if (n%2) { 
        // n奇数，内部和外部比赛
        Play(n/2,B[(n-1)/2],LowExt+1,winner,loser); i = LowExt+3;
    } else 
        i = LowExt+2;

    for (; i<=n; i+=2) // 剩余外部结点的比赛
        Play((i-LowExt+n-1)/2, i-1, i, winner, loser);
}
template<class T>
void LoserTree<T>::Play(int p, int lc, int rc, int(* winner)(T A[], int b, int c), int(* loser)(T A[], int b, int c)){
    B[p] = loser(L, lc, rc); // 败者索引放在B[p]
    int temp1, temp2;
    temp1 = winner(L, lc, rc); // p处的胜者索引
    while(p > 1 && p % 2) { // 内部右，要沿路向上比赛
        temp2 = winner(L, temp1, B[p/2]);
        B[p/2] = loser(L, temp1, B[p/2]);
        temp1 = temp2;
        p/=2;
    } 
    // B[p]是左孩子，或者B[1]
    B[p/2] = temp1;
}

template<class T> 
void LoserTree<T>::RePlay(int i, int (*winner)(T A[], int b, int c), int (*loser)(T A[], int b, int c)){
    if (i <= 0 || i > n) {
        cout<<"Out of Bounds!"<<endl<<endl; return; 
    }
    int p;
    if (i <= LowExt) // 确定父结点的位置
        p = (i+offset)/2;
    else 
        p = (i-LowExt+n-1)/2;
    
    B[0] = winner(L, i, B[p]); 
    B[p] = loser(L, i, B[p]);
    for(; (p/2)>=1; p/=2) { // 沿路径向上比赛
        int temp = winner(L,B[p/2], B[0]);
        B[p/2] = loser(L,B[p/2], B[0]);
        B[0] = temp;
    } 
}


template<class T> 
int winner(T A[], int b, int c){
    return A[b] < A[c] ? b : c;
}
template<class T> 
int loser(T A[], int b, int c){
    return A[b] < A[c] ? c : b;
}
int main(){
    int n, m;
    cin >> n >> m;
    int *num = new int[n+1];
    for(int i=1;i <= n;i++){
        cin >> num[i];
    }
    //1.根据数组内容构建拜访树
    LoserTree<int> loserTree(n);
    loserTree.Initialize(num,n,winner,loser);
    loserTree.Display();
    for(int i=0;i<m;i++){
        int index,value;
        cin >> index >> value;
        num[index+1] = value;
        loserTree.RePlay(index+1,winner,loser);
        loserTree.Display();
    }
    return 0;
}