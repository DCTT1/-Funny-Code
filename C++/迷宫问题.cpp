#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<queue>
#include<stack>
#include<time.h>
#include<set>
#include<windows.h>

using namespace std;

struct Node{
    int x,y,g,h;
    bool walked;
    int f;      //f = g+h
    Node *parents;
};

int main(){
    int qiang = 0;
    vector< vector<Node> > migong;      //创建迷宫二维数组
    for (int i = 0; i < 5; i++)
    {
        vector<Node> hang;
        for (int j = 0; j < 5; j++)
        {
            int ii;
            cin >> ii;
            if(ii)
                qiang ++;
            Node node{i,j,ii};
            hang.push_back(node);
        }
        migong.push_back(hang);
    }
    int a[10002];
    int i = 0;
    double run_time;
    _LARGE_INTEGER time_start;      //开始时间
    _LARGE_INTEGER time_over;        //结束时间
    double dqFreq;      //计时器频率
    LARGE_INTEGER ff;
    QueryPerformanceFrequency(&ff);
    dqFreq = (double)ff.QuadPart;
    QueryPerformanceCounter(&time_start);

    //*******************DFS************************//
    vector< vector<Node> >migong2 = migong;
    stack<Node*> f;
    f.push(&migong2[0][0]);
    migong2[0][0].walked = true;
    while (! f.empty())
    {
        Node *vt = f.top();
        bool can = true;

        if(vt ->x >= 1){
            Node *vf = &migong2[vt->x - 1][vt->y];
            if(vf ->walked == false){
                vf->parents = vt;
                vf->walked = true;
                if(vf == &migong2[4][4]){ break;}
                f.push(vf);
                can = false;
            }
        }

        if (vt->x <= 3)
        {
            Node *vf = &migong2[vt->x +1][vt->y +1];
            if (vf->walked == false)
            {
                vf->parents = vt;
                vf->walked = true;
                if(vf == &migong2[4][4]){ break;}
                f.push(vf);
                can = false;
            } 
        }
        
        if(vt->y >= 1){
            Node *vf = &migong2[vt->x][vt->y - 1];
            if (vf->walked == false)
            {
                vf->parents = vt;
                vf->walked = true;
                if(vf == &migong2[4][4]){ break;}
                f.push(vf);
                can = false;
            }   
        }

        if(vt->y <= 3){
            Node *vf = &migong2[vt->x][vt->y + 1];
            if (vf->walked == false)
            {
                vf->parents = vt;
                vf->walked = true;
                if(vf == &migong2[4][4]){ break; }
                f.push(vf);
                can = false;
            }
        }

        if(can){
            f.pop();
        }
    }
    
    QueryPerformanceCounter(&time_over);        //计时结束
    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart)/ dqFreq;
    float time1 = run_time;

    QueryPerformanceFrequency(&ff);
    dqFreq = (double)ff.QuadPart;
    QueryPerformanceCounter(&time_start);


    //**************************BFS**********************//
    int ax[4] = {-1,1,0,0};
    int by[4] = {0,0,1,-1};

    queue<Node*> bfs;
    bfs.push(&migong[0][0]);        //先将起点推进去//
    migong[0][0].walked = true;

    Node *vt;       //等下指向父节点的指针
    Node *vf;       //等下指向父节点引申出的子节点//

    while (! bfs.empty())
    {
        vt = bfs.front();
        bfs.pop();

        if ((*vt).x >= 1)       //询问左节点是否可以
        {
            vf = &migong[(*vt).x + ax[0]][(*vt).y + by[0]];
            if (! (*vf).walked && ! (*vf).walked)
            {
                bfs.push(vf);
                (*vf).walked = true;
                (*vf).parents = vt;      //子节点指向父节点
                if((*vf).x == 4 && (*vf).y == 4)   
                    break;      //如果是终点节点，结束寻找，跳出循环
            }
        }
        
        if ((*vt).x <= 3)       //查询右节点是否可以
        {
            vf = &migong[(*vt).x + ax[2]][(*vt).y + by[2]];
            if (! (*vf).walked && ! (*vf).walked)
            {
                bfs.push(vf);
                (*vf).walked = true;
                (*vf).parents = vt;
                if((*vf).x == 4 && (*vf).y == 4)    break;

            }  
        }
        
        if ((*vt).y >= 1) {     //查询上节点是否可以
            vf = &migong[(*vt).x + ax[3]][(*vt).y + by[3]];
            if (!(*vf).walked && !(*vf).walked) {
                bfs.push(vf);
                (*vf).walked = true;
                (*vf).parents = vt;
                if ((*vf).x == 4 && (*vf).y == 4) break;
            }
        }
    }
    
    QueryPerformanceCounter(&time_over);     //及时结束
    run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart)/dqFreq;
    float time2 = run_time;

    //******************** A  *******************//
    vector< vector<Node> >migong3 = migong;
    set<Node*> openNodes;
    set<Node*> closeNodes;
    openNodes.insert(&migong3[0][0]);

    //************************结束*********************//
    vector<Node*> fin;
    Node *aa = &migong[4][4];
    while (true)
    {
        fin.push_back(aa);
        if(aa == &migong[0][0])
            break;
        aa = aa->parents;
    }
    vector<Node*> fin2;
    Node *bb = &migong2[4][4];
    while (true){
        fin.push_back(bb);
        if(bb == &migong[0][0])
            break;
        bb = bb->parents;
    }   

    cout << "bfs 运行后的矩阵 " << endl;
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << migong[i][j].walked ;
            if(migong[i][j].walked)
                count ++;
        }
        count ++;
    }
    reverse(fin.begin(), fin.end());

    cout << "dfs运行后矩阵" << endl;
    int count2 = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << migong2[i][j].walked;
            if (migong2[i][j].walked)count2++;
        }
        cout << endl;
    }
    reverse(fin2.begin(), fin2.end());


    for(int i=0; i< fin.size(); i++)
        cout << fin[i]->x << " " << fin[i]->y << endl;

    cout << "Total Time of dfs: " <<time1 << "s" << endl;
    cout << "Total Time of bfs: " <<time2 << "s" << endl;
    cout << "bfs共搜索过的节点数: " << count-qiang << endl;
    cout << "dfs共搜索过的节点数: " << count2-qiang << endl;

    return 0;
}
