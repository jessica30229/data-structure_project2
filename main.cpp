#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <queue>
#include <stack>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

int row, col, B;
int robot_row, robot_col;
int start_row, start_col;
char floormap[1000][1000];
int max_steps = 0;
int dist_to_charger[1000][1000];

struct point {
	int x;
	int y;
  point(int _x, int _y): x(_x),y(_y) {}
};

vector<point> final_paths;


void calc_charger_dist(){
  queue<point> p;
  p.push(point(robot_row, robot_col));

  while(!p.empty()){
    point c = p.front(); p.pop();
    if(c.x-1 > 0){ //up
      if(dist_to_charger[c.x-1][c.y] == 0 || dist_to_charger[c.x-1][c.y] < dist_to_charger[c.x][c.y]-1){
        dist_to_charger[c.x-1][c.y] = dist_to_charger[c.x][c.y]-1;
        p.push(point(c.x-1, c.x-1));
      }
    }
    if(c.x+1 < row){ //down
      if(dist_to_charger[c.x+1][c.y] == 0 || dist_to_charger[c.x+1][c.y] < dist_to_charger[c.x][c.y]-1){
        dist_to_charger[c.x+1][c.y] = dist_to_charger[c.x][c.y]-1;
        p.push(point(c.x+1, c.y));
      }
    }
    if(c.y-1 > 0){ //left
      if(dist_to_charger[c.x][c.y-1] == 0 || dist_to_charger[c.x][c.y-1] < dist_to_charger[c.x][c.y]-1){
        dist_to_charger[c.x][c.y-1] = dist_to_charger[c.x][c.y]-1;
        p.push(point(c.x, c.y-1));
      }
    }
    if(c.y+1 < col){ //right
      if(dist_to_charger[c.x][c.y+1] == 0){
        dist_to_charger[c.x][c.y+1] = dist_to_charger[c.x][c.y]-1;
        p.push(point(c.x, c.y+1));
      }
    }
    if(dist_to_charger[c.x][c.y]<max_steps)
      max_steps = dist_to_charger[c.x][c.y];
  }
  dist_to_charger[start_row][start_col] = 0;
}

void dump_dist_array(){
  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      cout << dist_to_charger[i][j];
    }
    cout << "\n";
  }
}

void dump_floormap() {
  for(int i=0;i<row;i++) {
    for(int j=0;j<col;j++) {
       cout << floormap[i][j]; 
    }
    cout << endl;
  }
}

// find a path from point 'to' to origin (robot place)
void find_path(vector<point>* s, int r, int c, int max_dist) {
  // check to origin?
  if(r==robot_row && c==robot_col)
    return;

  // get current dist
  int dist = dist_to_charger[r][c];

  // cout << "r=" << r << ", c=" << c << ", dist=" << dist << ", max=" << max_dist << endl;

  // push current point
  s->push_back(point(r,c));

  // set clean mark
  if(floormap[r][c]=='0') {
    floormap[r][c] = '2';
  }

  // dump_floormap();

  // check 4 directions
  int dist_up, dist_down, dist_left, dist_right;
  char t_up, t_down, t_left, t_right;

  dist_up = dist_down = dist_left = dist_right = 0;
  t_up = t_down = t_left = t_right = '1';

  // check up
  if(r>1) {
    dist_up = dist_to_charger[r-1][c];
    t_up = floormap[r-1][c];
    // cout << "up=" << dist_up << "," << t_up << endl;
  }
  // check down
  if(r<row-1) {
    dist_down = dist_to_charger[r+1][c];
    t_down = floormap[r+1][c];
    // cout << "down=" << dist_down << "," << t_down << endl;
  }
  // check left
  if(c>1) {
    dist_left = dist_to_charger[r][c-1];
    t_left = floormap[r][c-1];
    // cout << "left=" << dist_left << "," << t_left << endl;
  }
  // check right
  if(c<col-1) {
    dist_right = dist_to_charger[r][c+1];
    t_right = floormap[r][c+1];
    // cout << "right=" << dist_right << "," << t_right << endl;
  }
  
  int next_r = 0, next_c = 0;

  // find dist+1 and not cleaned first
  // e.g.1 dist = -10, max_dist = -10 --> dist_up = -9 and type='0', is ok
  // e.g.2 dist = -10, max_dist = -20 --> dist_up >= max_dist+1 and type='0'
  bool found = false;
  // find unclean frist
  if(dist_up>=max_dist+1 && t_up=='0') {
    next_r = r-1; next_c = c; found = true;
  }
  if(!found && dist_down>=max_dist+1 && t_down=='0') {
    next_r = r+1; next_c = c; found = true;
  }
  if(!found && dist_left>=max_dist+1 && t_left=='0') {
    next_r = r; next_c = c-1; found = true;
  }
  if(!found && dist_right>=max_dist+1 && t_right=='0') {
    next_r = r; next_c = c+1; found = true;
  }
  // not found unclean, find shortest
  if(!found) {
    if(dist_up==dist+1) {
      next_r = r-1; next_c = c; found = true;
    }
    if(!found && dist_down==dist+1) {
      next_r = r+1; next_c = c; found = true;
    }
    if(!found && dist_left==dist+1) {
      next_r = r; next_c = c-1; found = true;
    }
    if(!found && dist_right==dist+1) {
      next_r = r; next_c = c+1; found = true;
    }
  }

  find_path(s, next_r, next_c, max_dist+1);
}

void do_cleaning(vector<point>& places) {

  // init final paths
  final_paths.clear();
  final_paths.push_back(point(robot_row, robot_col));

  for(int i=0;i<places.size();i++) {
    point p = places[i];
    
    if(floormap[p.x][p.y]=='2') { // already clean
      continue;
    }

    vector<point> v;
    // find path to p (shortest)
    int dist = dist_to_charger[p.x][p.y];
    find_path(&v, p.x, p.y, dist);
    for(int i=v.size()-1;i>=0;i--) {
      final_paths.push_back(v[i]);
    }
    // backward to origin
    v.clear();
    find_path(&v, p.x, p.y, -B-dist); // use negative number
    for(int i=1;i<v.size();i++) {
      final_paths.push_back(v[i]);
    } 
    final_paths.push_back(point(robot_row, robot_col));

    // dump_floormap();    
  }
}

int sort_point(point& a, point& b)
{
  int dist_a = dist_to_charger[a.x][a.y];
  int dist_b = dist_to_charger[b.x][b.y];

  return dist_a < dist_b;
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

  for(int i = 0; i < row; i++){
    for(int j = 0; j < col; j++){
      fin >> floormap[i][j];
      // cout << floormap[i][j];
      if(floormap[i][j] == 'R'){
        //final_path[0][0] = 
        start_row = i;
        //final_path[0][1] = 
        start_col = j;
        dist_to_charger[i][j] = 0;
      }else if(floormap[i][j] == '0'){
        //uncleaned_places += 1;
        dist_to_charger[i][j] = 0;
      }else
        dist_to_charger[i][j] = 1;
    }
    //cout << "\n";
  }
  fin.close();


  // cout << "row=" << row << ", col=" << col << ", B=" << B << "\n";
  if(row > 1000 || col > 1000){
    printf("invalid testcase.\n");
  }
  else{
    calc_charger_dist();
    //cout << "max_steps=" << -max_steps << endl;
    if(-max_steps > B/2) {
       cout << "floormap invalid due to robot cannot reach farest place" << endl;
     }
    // dump_dist_array();

    vector<point> places;
    // sort unclean place by dist
    for(int i=0;i<row;i++) {
      for(int j=0;j<col;j++) {
          if(floormap[i][j]=='0') {
            places.push_back(point(i,j));
          }
      }
    }
    sort(places.begin(), places.end(), sort_point);

    // do cleaning
    do_cleaning(places);
  }

  //ouput the file

  ofstream fout;
  fout.open("final.path", ios::out);
  if(!fout){
	  cout << "Fail to open file: " << "final.path" << endl;
  }

  //output content
  fout << final_paths.size()-1 << "\n";
  for(int i = 0; i < final_paths.size(); i++){
    point p = final_paths[i];
    fout << p.x << " " << p.y << "\n";
  }
  fout.close();

  return 0;
}
