#include <bits/stdc++.h>
#include "passenger.cpp"
using namespace std;

class Compare
{
public:
    bool operator()(Passenger &a, Passenger &b)
    {
        return b.getAge() > a.getAge();
    }
};

class HyperLoopBooking
{
    bool isInitialized;
    vector<vector<pair<int, int>>> graph;
    priority_queue<Passenger, vector<Passenger>, Compare> queue;
    vector<int> parent;
    vector<string> paths;

    int getKey(char node)
    {
        return tolower(node) - 'a';
    }
    char getNode(int node)
    {
        return char('A' + node);
    }
    bool isDestinationValid(int destination)
    {
        return destination >= 0 && destination < graph.size();
    }
    void computeShortestPath()
    {
        int n = graph.size();
        vector<bool> visited(n);
        for (int i = 0; i < n; i++)
        {
            parent.push_back(-1);
        }
        vector<int> distance(n, INT_MAX);
        distance[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minQueue;
        minQueue.push({0, 0});
        while (!minQueue.empty())
        {
            pair<int, int> pair = minQueue.top();
            minQueue.pop();
            int curr = pair.first, currDistance = pair.second;
            if (visited[curr])
            {
                continue;
            }
            visited[curr] = true;
            for (const auto &adjacentPair : graph[curr])
            {
                int adjacent = adjacentPair.first, adjacentDistance = adjacentPair.second;
                if (!visited[adjacent] && distance[curr] + adjacentDistance < distance[adjacent])
                {
                    distance[adjacent] = distance[curr] + adjacentDistance;
                    minQueue.push({adjacent, distance[adjacent]});
                    parent[adjacent] = curr;
                }
            }
        }

        // Construct the shortest paths for each node.
        for (int i = 0; i < n; i++)
        {
            paths.push_back(constructPath(i));
        }
    }
    string constructPath(int destination)
    {
        string path;
        int index = destination;
        while (index >= 0)
        {
            path += getNode(index);
            index = parent[index];
        }
        reverse(path.begin(), path.end());
        return path;
    }
    string getPath(int destination)
    {
        return paths[destination];
    }

public:
    HyperLoopBooking() : isInitialized(false) {}
    void init()
    {
        if (!isInitialized)
        {
            isInitialized = true;

            cout << "\nEnter the number of stations - ";
            int n;
            cin >> n;

            // Initialize the graph.
            for (int i = 0; i < n; i++)
            {
                vector<pair<int, int>> adjacent;
                graph.push_back(adjacent);
            }

            cout << "\nEnter the number of routes and starting station - ";
            int e;
            char source;
            cin >> e >> source;

            cout << "\nEnter the routes and their distance\n";
            for (int i = 0; i < e; i++)
            {
                char a, b;
                int dist;
                cin >> a >> b >> dist;

                // Update the graph.
                int keyA = getKey(a), keyB = getKey(b);
                graph[keyA].push_back({keyB, dist});
                graph[keyB].push_back({keyA, dist});
            }

            // Compute the shortest path from source to all other stations.
            computeShortestPath();
        }
        else
        {
            cout << "\nHyper loop already initialized\n";
        }
    }
    void addPassenger()
    {
        if (isInitialized)
        {
            cout << "\nEnter the number of passengers to add - ";
            int n;
            cin >> n;
            cout << "\nEnter name, age and destination for all the passengers\n";
            for (int i = 0; i < n; i++)
            {
                string name;
                int age;
                char destination;
                cin >> name >> age >> destination;
                if (isDestinationValid(getKey(destination)))
                {
                    Passenger p(name, age, destination);
                    queue.push(p);
                }
                else
                {
                    cout << "\nInvalid destination\n";
                }
            }
        }
        else
        {
            cout << "\nHyper loop not yet initialized\n";
        }
    }
    void startPod()
    {
        if (isInitialized)
        {
            cout << "\nEnter the number of passengers - ";
            int n;
            cin >> n;
            if (n > 0 && n <= queue.size())
            {
                for (int i = 0; i < n; i++)
                {
                    Passenger p = queue.top();
                    queue.pop();
                    string path = getPath(getKey(p.getDestination()));
                    cout << "\nName - " << p.getName() << "\n";
                    cout << "Path - " << path << "\n";
                }
            }
            else
            {
                cout << "\nInvalid number of passengers\n";
            }
        }
        else
        {
            cout << "\nHyper loop not yet initialized\n";
        }
    }
    void printQueue()
    {
        if (isInitialized)
        {
            if (queue.size() > 0)
            {
                cout << "\nNumber of passengers - " << queue.size() << "\n";
                priority_queue<Passenger, vector<Passenger>, Compare> tempQueue;
                while (!queue.empty())
                {
                    Passenger top = queue.top();
                    queue.pop();
                    top.printDetails();
                    tempQueue.push(top);
                }
                while (!tempQueue.empty())
                {
                    queue.push(tempQueue.top());
                    tempQueue.pop();
                }
            }
            else
            {
                cout << "\nThe queue is empty\n";
            }
        }
        else
        {
            cout << "\nHyper loop not yet initialized\n";
        }
    }
};