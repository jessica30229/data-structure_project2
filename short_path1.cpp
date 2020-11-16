#include<iostream>  
#include<queue>  
#include<string>  
using namespace std;
struct point {
	int x;
	int y;
	point *last;//上一步的座標  
};
int main() {
	while (1) {
		int row, col, i, j;
		cout << "請輸入迷宮圖的行數和列數：";
		cin >> row >> col;
		int **a = new int*[row + 2];
		for (i = 0; i < row + 2; ++i) {
			a[i] = new int[col + 2];
		}
		cout << "請輸入迷宮圖（1代表牆壁，0代表通路）：" << endl;
		for (i = 1; i < row + 1; ++i) {
			for (j = 1; j < col + 1; ++j) {
				cin >> a[i][j];
			}
		}
		for (i = 0; i < col + 2; ++i) {//加牆  
			a[0][i] = 1;
			a[row + 1][i] = 1;
		}
		for (i = 1; i < row + 1; ++i) {//加牆  
			a[i][0] = 1;
			a[i][col + 1] = 1;
		}
		queue<point*> q;
		point *start = new point;//起點  
		cout << "請輸入起點座標（範圍1,1到" << row << "," << col << "）：";
		cin >> start->x >> start->y;
		start->last = start;
		q.push(start);


		a[start->x][start->y] = 2;


		point end;//終點  
		cout << "請輸入終點座標（範圍1,1到" << row << "," << col << "）：";
		cin >> end.x >> end.y;
		int aspect[4][2] = { { 0, -1 },{ 0, 1 },{ -1, 0 },{ 1, 0 } };//轉向：上下左右  
		int flag = 0;//是否有路可走的標誌  
		while (!q.empty()) {
			point *front = q.front();
			q.pop();//彈出隊頭  
			if (front->x == end.x && front->y == end.y) {
				flag = 1;
				cout << "成功找到出路." << "最少需要" << a[front->x][front->y] - 2 << "步。如下所示：" << endl;
				a[front->x][front->y] = -6;
				//cout<<"倒退回去："<<(front)->x<<","<<(front)->y;  
				point *lastPoint = front;
				front = front->last;
				while ((front->x != start->x) || (front->y != start->y)) {
					//cout<<"->"<<front->x<<","<<front->y;  
					if (lastPoint->x - front->x == 1) { //front在左
						a[front->x][front->y] = -1;
					}
					else if (lastPoint->x - front->x == -1) { //front在右
						a[front->x][front->y] = -2;
					}
					else if (lastPoint->y - front->y == 1) { //front在上
						a[front->x][front->y] = -3;
					}
					else { //front在下
						a[front->x][front->y] = -4;
					}
					lastPoint = front;
					front = front->last;
				}
				//cout<<"->"<<start->x<<","<<start->y<<endl;  
				a[start->x][start->y] = -5;
				break;
			}
			else {
				for (int i = 0; i < 4; ++i) {
					point *temp = new point;
					temp->x = front->x + aspect[i][0];
					temp->y = front->y + aspect[i][1];
					if (a[temp->x][temp->y] == 0) {
						temp->last = front; 
						q.push(temp);
						a[temp->x][temp->y] = a[front->x][front->y] + 1;
					}
				}
			}
		}
		if (!flag)
			cout << "無路可走！" << endl;
		else {
			for (int i = 1; i <= row; ++i) {
				for (int j = 1; j <= col; ++j) {
					if (a[i][j] <0 ) {
						cout << "(" << i << "," << j << ")";
					}					
				}
				cout << endl;
			}
		}
		system("pause");
	}
}