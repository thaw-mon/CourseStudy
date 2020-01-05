//1. 距离排序

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>

using namespace std;
class node{
public:
	double value;
	int x1,y1,z1;
	int x2,y2,z2;
	//(0,0,0)-(1,1,1)=1.73
	void printResult(){
		cout << fixed << setprecision(2) << "(" << x1 << "," << y1 << "," << z1  << ")-(" << x2 << "," << y2 << "," << z2 << ")=" << value << endl; 
	}
};
int main(){
	vector<int> x_p;
	vector<int> y_p;
	vector<int> z_p;
	int n = 0,x = 0 ,y = 0 ,z = 0; //定义点的数目
	cin >> n;
	for(int i=0;i<n;i++){
		cin >> x >> y >> z;
		x_p.push_back(x);
		y_p.push_back(y);
		z_p.push_back(z);
	}
	node nodes[n * (n-1) / 2];
	int index = 0;
	for(int i=0;i<n;i++){
		for(int j= i+1;j<n;j++){
			node n;
			//计算点i到点j之间的距离
			n.value = sqrt(pow((x_p[i]-x_p[j]),2) + pow((y_p[i]-y_p[j]),2) + pow((z_p[i]-z_p[j]),2));
			n.x1 = x_p[i];  n.y1 = y_p[i];  n.z1 = z_p[i];
			n.x2 = x_p[j];  n.y2 = y_p[j];  n.z2 = z_p[j];
			nodes[index] = n;
			//直接在这里进行插入排序(从大到小)
			int k = index;
			while(k > 0 && n.value > nodes[k-1].value){
				nodes[k] = nodes[k-1];
				k--;
			}
			nodes[k] = n;
			index++;
		}
	}
	//输出排序后的结果
	for(int i=0;i<index;i++)
		nodes[i].printResult();
	
	return 0;
}