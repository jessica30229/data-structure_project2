#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;

int row, col, B;
// char **floormap;
char floormap[1000][1000];
int final_steps = 0;
int final_path[1000][2];

void start(){

}

int main (int argc, char *argv[]) {
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
    }
    cout << "\n";
  }
  fin.close();

  // cout << "row=" << row << ", col=" << col << ", B=" << B << "\n";
  if(row > 1000 || col > 1000){
    printf("invalid testcase.\n");
  }
  else{
    start();
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
