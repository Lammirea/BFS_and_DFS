// lab_7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void BFSD_for_weighted_matrix(int s, int* m[], int n);

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
    cout << "Матрица смежности неориентированного взвешенного графа:" << endl;
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
    cout << "Введите вершину от 0 до " << n-1 << endl;
    cin >> v;
    cout << endl;

    BFSD_for_weighted_matrix(v, matrix, n);
    cout << endl;

    int nd;
    cin >> nd;
    int** matrix_dir = new int* [nd];
    for (int i = 0; i < nd; ++i)
    {
        matrix_dir[i] = new int[nd];
    }

    srand(time(NULL));
    cout << "Матрица смежности ориентированного взвешенного графа:" << endl;
    for (int i = 0; i < nd; i++)
    {
        for (int j = 0; j < nd; j++)
        {
            matrix_dir[i][j] = rand() % 101;
            if (i == j) {
                matrix_dir[i][j] = 0;
            }
            if (matrix_dir[i][j] >= 0 && matrix_dir[i][j] <= 30) {
                matrix_dir[i][j] = 0;
            }
            if (matrix_dir[i][j] >= 31 && matrix_dir[i][j] <= 100) {
                matrix_dir[i][j] = rand() % 20 + 1;
            }

        }
    }
    for (int i = 0; i < nd; i++)
    {
        for (int j = 0; j < nd; j++)
        {
            cout << matrix_dir[i][j] << " ";
        }
        cout << endl;
    }

    int vd;
    cout << "Введите вершину от 0 до " << nd - 1 << endl;
    cin >> vd;
    cout << endl;

    BFSD_for_weighted_matrix(vd, matrix_dir, nd);
    system("pause>nul");
    return 0;
}

void BFSD_for_weighted_matrix(int s, int* m[], int n) {

    vector<int> dist(n, INT_MAX);
    queue<int> q;
    q.push(s);
    dist[s] = 0;

    cout << "Порядок обхода:" << endl;
    int vis;
    while (!q.empty()) {
        vis = q.front();

        // Print the current node

        cout << vis << "\t";
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
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Вершина " << i << "  расстояние:  " << dist[i] << " " << endl;
    }
}

