#include <bits/stdc++.h>
using namespace std;

class City
{
    int n;
    int m;
    int paths[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

public:
    unique_ptr<unique_ptr<int[]>[]> matrix;
    unique_ptr<unique_ptr<bool[]>[]> visited;
    unique_ptr<int[]> groups;
    unique_ptr<int[]> shortestDist;

    City(int n, int m)
    {
        this->n = n;
        this->m = m;
        this->matrix = make_unique<unique_ptr<int[]>[]>(n);
        this->visited = make_unique<unique_ptr<bool[]>[]>(n);
        this->groups = make_unique<int[]>(n * m);
        this->shortestDist = make_unique<int[]>(n * m);

        for (int i = 0; i < n; i++)
        {
            unique_ptr<int[]> matrixRow = make_unique<int[]>(m);
            unique_ptr<bool[]> visitedRow = make_unique<bool[]>(m);
            for (int j = 0; j < m; j++)
            {
                matrixRow[j] = 0;
                visitedRow[j] = false;
            }
            matrix[i] = move(matrixRow);
            visited[i] = move(visitedRow);
            groups[i] = 0;
            shortestDist[i] = INT_MAX;
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
    }
    int computeGroups(int i, int j, int groupCount)
    {
        if (i < 0 || i >= n || j < 0 || j >= m || matrix[i][j] == 0 || visited[i][j])
        {
            return 0;
        }
        visited[i][j] = true;
        int res = 0;
        for (int k = 0; k < 4; k++)
        {
            int row = i + paths[k][0], col = j + paths[k][1];
            res += computeGroups(row, col, groupCount);
        }
        int currVal = matrix[i][j];
        matrix[i][j] = groupCount;
        return currVal + res;
    }
    void clearVisited()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                visited[i][j] = false;
            }
        }
    }
    void computeShortestDistance(int i, int j, int dist)
    {
        if (i < 0 || i >= n || j < 0 || j >= m || visited[i][j])
        {
            return;
        }
        visited[i][j] = true;
        shortestDist[matrix[i][j] - 1] = min(shortestDist[matrix[i][j] - 1], dist - 1);
        for (int k = 0; k < 4; k++)
        {
            int row = i + paths[k][0], col = j + paths[k][1];
            computeShortestDistance(row, col, dist + 1);
        }
        visited[i][j] = false;
    }
};

int main()
{
    int n, m;
    cout << "\nEnter the number of rows and columns - ";
    cin >> n >> m;
    City city(n, m);
    int count = 0, leaderGroup = 0, leaderGroupIndex = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (city.matrix[i][j] != 0 && !city.visited[i][j])
            {
                int res = city.computeGroups(i, j, count + 1);
                city.groups[count] = res;
                if (res > leaderGroup)
                {
                    leaderGroup = res;
                    leaderGroupIndex = count;
                }
                count++;
            }
        }
    }
    cout << "\nNumber of groups - " << count << "\n";
    cout << "The groups are - ";
    for (int i = 0; i < count; i++)
    {
        cout << city.groups[i] << " ";
    }
    cout << "\nLeader Group - " << leaderGroup << "\n";

    city.clearVisited();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (city.matrix[i][j] == 1 && !city.visited[i][j])
            {
                city.computeShortestDistance(i, j, 0);
            }
        }
    }

    cout << "\nThe shortest distance to each group are\n";
    for (int i = 0; i < count; i++)
    {
        if (i != leaderGroupIndex)
        {
            cout << "{" << city.groups[leaderGroupIndex] << "}"
                 << " to "
                 << "{" << city.groups[i] << "}"
                 << " is " << city.shortestDist[i] << "\n";
        }
    }

    return 0;
}