#include<iostream>
using namespace std;

typedef struct{
    int location;     //(x-1)*3+y 
int parent;       //記錄上一個節點即路徑中前驅節點，方便最後輸出
}QueueNode;

void Maze_Shortest(int maze[][5],point &start,point &des)
{
    queue Queue;
    InitializeQueue(Queue);
    EnterQueue(Queue,(start.x-1)*5+start.y,Queue.head);
    
    int direction;
    bool FindFlag=false;  
    int dir[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

    while (!EmptyQueue(Queue)&&!FindFlag)
    {
        int curX=Queue.array[Queue.head].location/3+1;
        int curY=Queue.array[Queue.head].location%3;

        for (direction=0;direction<4;direction++)          //遍歷該點四周四個鄰接點
        {
            int nextX=curX+dir[direction][0];
            int nextY=curY+dir[direction][1];
            if (!maze[nextX][nextY])                                     //如果為0 排除了牆和已經踩過的路
            {
                EnterQueue(Queue,(nextX-1)*3+nextY,Queue.head);     //入隊，入隊元素是對映後節點！
                if (nextX==des.x&&nextY==des.y)
                {
                    FindFlag=true;
                    break;
                }
            }
        }
        Queue.head++;
    }
    if (EmptyQueue(Queue))
    {
        printf("找不到路徑 ");
    }
    if(FindFlag)
    {
        int pre=Queue.array[--Queue.rear].parent;
        Queue.array[1].parent=0;
        printf("%d<- ",Queue.array[Queue.rear].location);
        while (pre)                                                   //迭代輸出路徑，可惜是逆向輸出，不過可以用棧解決
        {
            printf("%d<- ",Queue.array[pre].location);
            pre=Queue.array[pre].parent;
        }
    
    }
}