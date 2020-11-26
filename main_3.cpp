#include <iostream>
#include <fstream>
#include <climits>
#define infinity 2147483647

using namespace std;
int step = 0;
struct node{
    int row;
    int col;
};
node ans[1000000];


class stack_{
public:
    node capacity[1000000];
    int t;
    stack_(){t = -1;};
    node top();
    void push(node a);
    void pop();
    bool empty();
    void print();

};
void stack_::print(){
    for(int i=0;i<=t;i++)
        cout<<"("<<capacity[i].row<<","<<capacity[i].col<<")";
    cout<<endl;
}
node stack_::top(){
    return capacity[t];
}

void stack_::push(node num){
    t++;
    capacity[t].col = num.col;
    capacity[t].row = num.row;
}

bool stack_::empty(){
    if(t == -1)
        return true;
    else
        return false;
}

void stack_::pop(){
    if(!empty()){
        t--;
    }
}

stack_ s;

void print_2d(int** mat, int r, int c){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cout << mat[i][j] << " ";
        }
        cout<<endl;
    }
    cout<<endl;
}



bool expand_finish(int **bg,int r,int c){
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(bg[i][j]==-2)
                return false;
        }
    }
    return true;
}
int choose(int **bg,int r,int c, int row,int col){
    int up = 1000001;
    int down = 1000001;
    int left = 1000001;
    int right = 1000001;
    int ans;
    if(row-1>=0 && bg[row-1][col]>=0)
        up=bg[row-1][col];
    if(row+1<r && bg[row+1][col]>=0)
        down=bg[row+1][col];
    if(col-1>=0 && bg[row][col-1]>=0)
        left=bg[row][col-1];
    if(col+1<c && bg[row][col+1]>=0)
        right=bg[row][col+1];
    int comp1 = up<down ? up:down;
    int comp2 = left<right ? left:right;
    ans = comp1<comp2 ? comp1:comp2;
    if(ans==1000001)
        return bg[row][col];
    else
        return ans+1;

}


void expand_Map(int **bg,int r,int c){
    if(expand_finish(bg,r,c))
        return;
    else{
        int **new_bg = new int*[r];
        for(int i=0;i<r;i++)
            new_bg[i] = new int[c];
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                if(bg[i][j]==-2)
                    new_bg[i][j]=choose(bg,r,c, i, j);
                else
                    new_bg[i][j]=bg[i][j];
            }
        }

        for(int i=0;i<r;i++)
            delete[] bg[i];
        for(int i=0;i<r;i++)
            bg[i] = new_bg[i];
        expand_Map(bg,r,c);

    }
}

int find_direction(int **bg,int r,int c,int row,int col){
    if(row-1>=0 && bg[row-1][col] == bg[row][col]-1)
        return 1;
    if(row+1<r && bg[row+1][col] == bg[row][col]-1)
        return 2;
    if(col-1>=0 && bg[row][col-1]== bg[row][col]-1)
        return 3;
    if(col+1<c && bg[row][col+1]== bg[row][col]-1)
        return 4;


   return -1;
}

void storestack(int** done, int r, int c){
    stack_ copy;
    while(!s.empty()){
        ans[step] = s.top();
        done[s.top().row][s.top().col] = 0;
        step++;
        copy.push(s.top());
        s.pop();
    }
    copy.pop();
    while(!copy.empty()){
        ans[step] = copy.top();
        step++;
        copy.pop();
    }
    step--;
}


void print_path(int **bg,int**done,int r,int c,int row,int col){
    node start;
    start.row = row;
    start.col = col;
    s.push(start);
    //s.print();

    if(bg[row][col]==0){
        storestack(done,r,c);
        return;
    }

    int dir = find_direction(bg,r, c, row, col);
    if(dir==1)
        print_path(bg,done,r,c,row-1,col);
    else if(dir==2)
        print_path(bg,done,r,c,row+1,col);
    else if(dir==3)
        print_path(bg,done,r,c,row,col-1);
    else if(dir==4)
        print_path(bg,done,r,c,row,col+1);
}


bool Find_Path(int **bg, int r,int c, int battery){
    int **done = new int*[r];
    for(int i=0;i<r;i++)
        done[i] = new int[c];

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(bg[i][j]>0)
                done[i][j]=1;
            else
                done[i][j]=0;
        }
    }

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(done[i][j]>0){
                if(bg[i][j]>battery/2){
                    return false;
                }
                print_path(bg,done,r,c,i,j);
            }
        }
    }
    return true;
}
/*
bool check_step(){
  for(int i = 1; i <= step; i++){
    int one_per_step = (ans[i].row-ans[i-1].row)+(ans[i].col-ans[i-1].col);
    if(one_per_step!=1 && one_per_step!=-1){
      return false;
    }
  }
  return true;
}
bool check_ans(int**bg, int r, int c){

  int** answer = new int*[r];
  for(int i=0;i<r;i++){
    answer[i] = new int[c];
  }

  for(int i=0;i<r;i++){
      for(int j=0;j<c;j++){
          if(bg[i][j]==-1)
            answer[i][j]=1;
          else
            answer[i][j]=0;
      }
  }

  if(!check_step())
    return false;
  for(int i = 0; i <= step; i++){
    if(bg[ans[i].row][ans[i].col]!=-1)
      answer[ans[i].row][ans[i].col]=1;
  }

  for(int i=0;i<r;i++){ 
    for(int j=0;j<c;j++){
      if(answer[i][j]!=1){
        for(int ii=0;ii<r;ii++){
          delete[] answer[ii];
        }
        delete[] answer;
        cout<<"wrong step:"<<i<<","<<j<<endl;
        return false;
      }
    }
  }
  for(int i=0;i<r;i++){
      delete[] answer[i];
  }   
      delete[] answer;
  return true;
}
*/
int main(){
    int **bg;
    int c, r;
    int battery = 0;
    node R;

    fstream file;
    file.open("floor1.data",ios::in);
    if(!file){
        cout<<"open file failed!"<<endl;
    }
    file >> r >> c >> battery;

    bg = new int*[r];
    for(int i=0;i<r;i++){
      bg[i] = new int[c];
    }

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            char input;
            file >> input;
            if(input == 'R'){
                R.row = i;
                R.col = j;
                bg[i][j] = 0;
            }
            else if(input == '1')
                bg[i][j] = -1;
            else if(input == '0')
                bg[i][j] = -2;
            else
                cout<<"Illegal case"<<endl;
        }
    }
    file.close();

    //print_2d(bg,r,c);
    expand_Map(bg,r,c);                                //從起點開始計算到每一格要走多少步,可打開前後兩行print_2d看看bg發生了什麼變化

    //cout<<"-----------------------"<<endl;
    //print_2d(bg,r,c);

    //cout<<"R : "<<R.row<<" , "<<R.col<<endl;

    if(Find_Path(bg,r,c,battery)){                    //有了每格距離起點幾步距離後開始print每一條path出來
        fstream file;
        file.open("floor.final",ios::out);
        if(!file){
             cout<<"open file failed!"<<endl;
        }
        else{
             file << step << endl;
             for(int i = 0; i < step; i++){
                file << ans[i].row << " " << ans[i].col << endl;
             }
             file << R.row <<" " << R.col << endl;
             /*
             if(check_ans(bg,r,c))
                cout << "Correct!" <<endl;
             else
                cout << "Wrong" << endl;
                */
        }
    }
    else
        cout << "Illegal battery" << endl;
    file.close();
    return 0;
}
