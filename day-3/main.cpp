#include <bits/stdc++.h>
using namespace std;

int dfs(int n, int m, int **matrix, bool **visited, int paths[4][2], int i, int j)
{
    if (i < 0 || i >= n || j < 0 || j >= m or matrix[i][j] == 0 || visited[i][j])
    {
        return 0;
    }
    visited[i][j] = true;
    int res = 0;
    for (int k = 0; k < 4; k++)
    {
        int row = i + paths[k][0], col = j + paths[k][1];
        res += dfs(n, m, matrix, visited, paths, row, col);
    }
    return matrix[i][j] + res;
}

int main()
{
    int n, m;
    cout << "\nEnter the number of rows and columns - ";
    cin >> n >> m;
    int *matrix[n];
    bool *visited[n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[m];
        visited[i] = new bool[m];
    }
    cout << "\nEnter the matrix\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> matrix[i][j];
            visited[i][j] = false;
        }
    }
    int paths[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int groups[n * m];
    int count = 0, leaderGroup = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (matrix[i][j] != 0 && !visited[i][j])
            {
                int res = dfs(n, m, matrix, visited, paths, i, j);
                groups[count] = res;
                count++;
                if (res > leaderGroup)
                {
                    leaderGroup = res;
                }
            }
        }
    }
    cout << "\nNumber of groups - " << count << "\n";
    cout << "The groups are \n";
    for (int i = 0; i < count; i++)
    {
        cout << groups[i] << " ";
    }
    cout << "\nLeader Group - " << leaderGroup << "\n\n";
    return 0;
}