#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


vector<int> BFSD_for_weighted_matrix(int s, int* m[], int n);

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
            matrix[i][j] = rand() % 101;
            if (i == j) {
                matrix[i][j] = 0;
            }
            if (matrix[i][j] >= 0 && matrix[i][j] <= 30) {
                matrix[i][j] = 0;
            }
            if (matrix[i][j] >= 31 && matrix[i][j] <= 100) {
                matrix[i][j] = rand() % 20 + 1;
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
    vector<vector<int>> dist_mat;
    dist_mat.resize(n);
    vector<int> mat(n);
    //считываем расстояние для каждой вершины
    for (int i = 0; i < n; i++)
    {
        v = i;
        mat = BFSD_for_weighted_matrix(v, matrix, n);
            dist_mat.push_back(mat);
       
    }
    cout << endl;
   //вывод матрицы расстояний
    for (int i = 0; i < dist_mat.size(); i++)
    {
        for (int j = 0; j < dist_mat[i].size(); j++)
        {
            cout << dist_mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    //////////////////////////////////////////////////////
    //считываем максимальный элемент каждой строки матрицы
    vector<int> max_in_row;
    max_in_row.resize(n);
    int max = -1;
    cout << "Максимальные элементы строк:" << endl;

    for (int i = 0; i < dist_mat.size(); i++)
    {
        max = -1;
       for (int j = 0; j < dist_mat[i].size(); j++)
       {
            if (dist_mat[i][j]>=max) {
                max = dist_mat[i][j];
            }
       }
       max_in_row.push_back(max);
    }
    for (int i = 0; i < max_in_row.size();  i++)
    {
        if (max_in_row[i] == -1 || max_in_row[i] == 0)
        {
            max_in_row.erase(max_in_row.begin()+1);
        }

        cout << max_in_row[i] << " ";
    }
    cout << endl;
    ////Поиск диаметра и радиуса графа////
    cout << endl;
    auto diametre = max_element(max_in_row.begin(), max_in_row.end());
    auto radius = min_element(max_in_row.begin()+n, max_in_row.end());
    cout << "Радиус графа равен: " << *radius << endl;
    cout << "Диаметр графа равен: " << *diametre << endl;

    //////Поиск переферийных и центральных вершин//////
    auto it = find(max_in_row.begin(), max_in_row.end(), *diametre);
    int index_of_per = it - max_in_row.begin();
    cout << "Переферийная вершина:" << index_of_per - n<< endl;
    auto it_for = find(max_in_row.begin(), max_in_row.end(), *radius);
    int index_of_cent = it_for - max_in_row.begin();
    cout << "Центральная вершина:" << index_of_cent - n << endl;
    cout << endl;
    /////Поиск изолированных, концевых и доминирующие вершин////////
    
    int* collection_of_inc_vertex = new int[n];
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        count = 0;
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] > 0)
            {
                count++;
            }
        }
        
        collection_of_inc_vertex[i]=count;
    }
    //cout << count << endl;
    for (int i = 0; i <n; i++)
    {
        if (collection_of_inc_vertex[i]==1)
        {
            cout << "Вершина " << i << " концевая" << endl;
        }
        if (collection_of_inc_vertex[i]==0)
        {
            cout << "Вершина " << i << " изолированная" << endl;
        }
        if (collection_of_inc_vertex[i] == *max_element(collection_of_inc_vertex, collection_of_inc_vertex+n))
        {
            cout << "Вершина " << i << " доминирующая" << endl;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;

    delete[] collection_of_inc_vertex;
    system("pause>nul");
    return 0;
}

vector<int> BFSD_for_weighted_matrix(int s, int* m[], int n) {

    vector<int> dist(n, INT_MAX);
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    //cout << "Порядок обхода:" << endl;
    int vis;
    while (!q.empty()) {
        vis = q.front();

        // Print the current node

        q.pop();

        // For every adjacent vertex to the current vertex
        for (int i = 0; i < n; i++) {
            if (m[vis][i] > 0 && dist[i] > dist[vis] + m[vis][i]) {

                // Push the adjacent node to the queue
                q.push(i);
                dist[i] = dist[vis] + m[vis][i];
            }

        }
    }
  
    return dist;
}