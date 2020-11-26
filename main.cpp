#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <queue>
#include <stack>
using namespace std;

int row, col, B;
// char **floormap;
char floormap[1000][1000];
int final_steps = 0, uncleaned_places = 0, chargepath = 0;
int final_path[1000][2];
// bool flag_charged = false;
int direction[4][2] = {{-1,0},{0,-1},{1,0},{0,1}}; //left,up,right,down(西北東南方)

struct point {
	int x;
	int y;
  int dir; //記錄你的前方是哪方
  /*
    1
  0   2
    3
  */
	point *last; //last point  
};

void find_shortpath(point* cur){

}

void visited(point* cur){
  final_steps++;
  final_path[final_steps][0] = cur->x;
  final_path[final_steps][1] = cur->y;
  floormap[cur->x][cur->y] = '2'; 
}

void cleaning(){
  //if(uncleaned_place>B) flag_charged = true;
  point* start = new point;
  start->x = final_path[0][0];
  start->y = final_path[0][1];
  start->last = start;
  if(start->x==row-1) start->dir = 1; //邊界下
  else if(start->y==col-1) start->dir = 0; //邊界右
  else if(start->x==0) start->dir = 3; //邊界上
  else if(start->y==0) start->dir = 2; //邊界左
  else start->dir = 0;//未在邊界(left) 
  stack<point*> s;
  s.push(start);
  point* cur = start;
  while (!s.empty())
  {
    cur = s.top();s.pop();
    if(B == chargepath){
      
    }
    if(floormap[cur->x][cur->y]=='0'||floormap[cur->x][cur->y]=='R'){
      //find next step
      /*
      my priority:
      1.)右轉:前方有1、左方為0&&右方為1
      2.)直行+左轉+直行:(如下示意)
                 x    x
        11x -> 11 -> 11
         1      1     1
        (cur) (next) (next2)
      3.)直行:左方有1、無牆
      */
      int frontside = cur->dir, rightside = (cur->dir+1)%4, leftside = cur->dir-1;
      if(leftside<0) leftside = leftside+4;
      if(floormap[cur->x + direction[frontside][0]][cur->y + direction[frontside][1]]=='1') //前方有1
        cur->dir =  rightside; //turn right
      else if(floormap[cur->x + direction[leftside][0]][cur->y + direction[leftside][1]]=='1'){ //左方有1 //2.)直行
        point* next = new point;
        next->x = cur->x + direction[cur->dir][0];
        next->y = cur->y + direction[cur->dir][1];
        next->dir = cur->dir;
        next->last = cur;
        visited(next);
        s.push(next);
        if(floormap[cur->x + 2*direction[leftside][0]][cur->y + 2*direction[leftside][1]]=='1'){ //3.)+左轉+直行
          point* next2 = new point;
          next2->x = next->x + direction[leftside][0];
          next2->y = next->y + direction[leftside][1];
          next2->dir = leftside;
          next2->last = next;
          visited(next2);
          s.push(next2);
        }
      }else if(floormap[cur->x + direction[leftside][0]][cur->y + direction[leftside][1]]=='0'&&floormap[cur->x + direction[rightside][0]][cur->y + direction[rightside][1]]=='1')
        cur->dir =  rightside; //turn right
      else{
        point* next = new point;
        next->x = cur->x + direction[cur->dir][0];
        next->y = cur->y + direction[cur->dir][1];
        next->dir = cur->dir;
        next->last = cur;
        visited(next);
        s.push(next);
      }
    }
  }
  while (cur!=NULL){
    point* tmp = cur;
    cur = cur->last;
    delete [] tmp;
  } 
}

int main (int argc, char *argv[]){
  if (!argc) {
    printf("usage: .exe filename\n");
    exit(-1);
  }

  //read the file

  ifstream fin;
  
  fin.open(argv[1], ios::in);
  if(!fin){
    cout <<"Fail to open file: " << argv[1]<<endl;
  }

  fin >> row >> col >> B;
  // *floormap = new char[row];
  // for(int i = 0; i < row; i++){
  //   floormap[i] = new char[col];
  // }

  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      fin >> floormap[i][j];
      // cout << floormap[i][j];
      if(floormap[i][j] == 'R'){
        final_path[0][0] = i;
        final_path[0][1] = j;
      }
      if(floormap[i][j] == '0')
        uncleaned_places += 1;
    }
    cout << "\n";
  }
  fin.close();

  // cout << "row=" << row << ", col=" << col << ", B=" << B << "\n";
  if(row > 1000 || col > 1000){
    printf("invalid testcase.\n");
  }
  else{
    cleaning();
  }

  //ouput the file

  ofstream fout;
  fout.open("final.path", ios::out);
  if(!fout){
	  cout << "Fail to open file: " << "final.path" << endl;
  }

  //delete floormap
  // for(int i = 0; i < row; i++){
  //   delete [] floormap[i];
  // }
  // delete [] floormap;

  //output content
  fout << final_steps << "\n";
  for(int i = 0; i < final_steps + 1; i++){
    fout << final_path[i][0] << " " << final_path[i][1] << "\n";
  }
  fout.close();

  return 0;
}
