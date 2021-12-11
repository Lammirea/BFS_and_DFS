// lab_6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

vector<vector<int>> convert(vector<vector<int>> a);
void BFSD_for_matrix(int s, int* m[], int n);
void BFSD_for_list(int ver, int n, vector<vector<int>> AdjList);
//void DFSD_for_matrix(int v, int n, int* M[], int vis[],int res[]);
//void DFS_for_list(int node, int visited[], int vertex, vector<vector<int>> AdjList);
const int N = 1e5 + 2;
vector <int> adj[N];
int main()
{
    setlocale(LC_ALL, "rus");
    int n;
    cin >> n;
    int** matrix = new int* [n];
    for (int i = 0; i < n; ++i)
    {
        matrix[i] = new int[n];
    }

    srand(time(NULL));
    cout << "Матрица смежности:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % 100;
            if (i == j) {
                matrix[i][j] = 0;
            }
            if (matrix[i][j] >= 0 && matrix[i][j] <= 30) {
                matrix[i][j] = 0;
            }
            if (matrix[i][j] >= 31 && matrix[i][j] <= 100) {
                matrix[i][j] = 1;
            }

        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {

            matrix[i][j] = matrix[j][i];
            cout << matrix[i][j] << " ";

        }
        cout << endl;
    }

    int v;
    cout << "Введите вершину от 1 до " << n << endl;
    cin >> v;
    cout << endl;
    cout << "Поиск кратчайшего пути на примере обхода в ширину:" << endl;
    BFSD_for_matrix(v, matrix, n);
    cout << endl;
    vector<vector<int>>a;
    a.resize(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) {
            a[i].push_back(matrix[i][j]);
        }
    }
    cout << "------------------------------------------------" << endl;
    vector<vector<int>> AdjList = convert(a);
    cout << "Список смежности:" << endl;
    for (int i = 0; i < AdjList.size(); i++)
    {
        cout << i;
        for (int j = 0; j < AdjList[i].size(); j++) {
            cout << " -> " << AdjList[i][j];
        }
        cout << endl;
    }
    cout << endl;

    BFSD_for_list(v, n, AdjList);
    cout << "Время работы реализаций алгоритмов поиска расстояний на основе обхода в ширину = " << clock() / 1000.0 << endl; // время работы программы 
    
    //cout << "------------------------------------------------------------" << endl;
    //cout << "Поиск кратчайшего пути на примере обхода в глубину:" << endl;
    //int* vis = new int[v];
    //for (int i = 0; i < n; i++)
    //{
    //    vis[i] = 0;
    //}
    //int* res = new int[n];
    //for (int i = 0; i < n; i++)
    //{
    //    res[i] = 0;
    //}
    ////int count = 0;
    //DFSD_for_matrix(v, n, matrix, vis,res);

    //for (int i = 0; i < n; i++)
    //{
    //    cout << "Вершина " << i << "  расстояние:  " << res[i] << endl;
    //}
    //delete[] res;
    //cout << "Время работы реализаций алгоритмов поиска расстояний на основе обхода в глубину = " << clock() / 1000.0 << endl; // время работы программы  
    system("pause>nul");
    return 0;
}

void BFSD_for_matrix(int s, int* m[], int n) {

    vector<int> visited(n, -1);
    queue<int> q;
    q.push(s);
    visited[s] = 0;

    cout << "Порядок обхода:" << endl;
    int vis;
    while (!q.empty()) {
        vis = q.front();

        // Print the current node
       
        cout << vis << "\t";
        q.pop();

        // For every adjacent vertex to the current vertex
        for (int i = 0; i < n; i++) {
            if (m[vis][i] == 1 && visited[i] == -1) {

                // Push the adjacent node to the queue
                q.push(i);
                visited[i] = visited[vis]+1;
            }
           
        }
    }
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Вершина "<< i << "  расстояние:  " << visited[i] << " " << endl;
    }
}

vector<vector<int>> convert(vector<vector<int>> a)
{
    vector<vector<int>> adjList(a.size());
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            if (a[i][j] == 1)
            {
                adjList[i].push_back(j);
            }
        }
    }
    return adjList;
}

void BFSD_for_list(int ver, int n, vector<vector<int>> AdjList) {

    vector<int> visited(n, -1);
    queue<int> q;
    q.push(ver);
    visited[ver] = 0;

    cout << "Порядок обхода:" << endl;
    int vis;
    while (!q.empty()) {
        vis = q.front();

        // Print the current node

        cout << vis << "\t";
        q.pop();

        // For every adjacent vertex to the current vertex
        for (int i = 0; i < (int)AdjList[vis].size(); i++) {
            int to = AdjList[vis][i];
            if (visited[to]==-1) {
                // Push the adjacent node to the queue
                visited[to] = 1;
                q.push(to);
                visited[to] = visited[vis] + 1;                
            }
        }
    }
    cout << endl;
    for (int i = 0; i < AdjList.size(); i++)
    {
        cout << "Вершина " << i << "  расстояние:  " << visited[i] << " " << endl;
    }
    
}

//void DFSD_for_matrix(int v, int n, int* M[], int vis[],int res[]){
//   
//    int count=0;
//    count++;
//    vis[v] = 1;
//    
//    for(int i=0;i<n;i++)
//    {
//        if (M[v][i] == 1 && vis[i] == -1) {
//            DFSD_for_matrix(i, n, M, vis,res);
//            //count++;
//            //res[i] = count;
//        }
//        if (M[v][i] == 1) {
//            //DFSD_for_matrix(i, n, M, vis,res);
//            //count++;
//            res[i] = count;
//        }
//        count--;
//
//        //count--;
//        if (count>res[i])
//        {
//            return;
//            //res[v] = count;
//        }
//        //count--;
//        
//        res[v] = count;
//
//    }
//    //count--;
//   
//    /*vis[v] = count;
//    printf("%d ", v + 1);
//    for (int i = 0; i < n; i++)
//    {
//        if (M[v][i] == 1 && vis[i] == -1)
//            DFSD_for_matrix(i,n, M, vis, count++);
//        if (M[v][i] == 1 && vis[i] > count)
//            DFSD_for_matrix(i, n, M, vis, count++);
//    }*/
//}
//
//void DFS_for_list(int node, int visited[], int vertex, vector<vector<int>> AdjList){
//
//}
