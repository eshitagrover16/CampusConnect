
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>
#include "ui.h"
#include <algorithm>
using namespace std;

class CampusNavigation {
private:
    string locations[6] = {
        "Main Gate",
        "Academic Block",
        "Library",
        "Computer Lab",
        "Hostel",
        "Canteen"
    };

    // Each edge stores {destination, distance}
    vector<pair<int, int>> graph[6];

public:
    // Connect two campus locations
    void addPath(int u, int v, int distance) {
        graph[u].push_back({v, distance});
        graph[v].push_back({u, distance});
    }

    // Display campus locations
    void showLocations() {
        cout << "\nCampus Locations:\n";

        for (int i = 0; i < 6; i++) {
            cout << i << ". " << locations[i] << endl;
        }
    }

    // BFS: Check reachability and show a path
    void BFS(int start, int destination) {
        bool visited[6] = {false};
        int parent[6];

        fill(parent, parent + 6, -1);

        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (current == destination)
                break;

            for (auto edge : graph[current]) {
                int next = edge.first;

                if (!visited[next]) {
                    visited[next] = true;
                    parent[next] = current;
                    q.push(next);
                }
            }
        }

        if (!visited[destination]) {
            cout << "Destination is not reachable.\n";
            return;
        }

        vector<int> path;

        for (int v = destination; v != -1; v = parent[v]) {
            path.push_back(v);
        }

        reverse(path.begin(), path.end());

        cout << "Reachable! BFS path: ";

        for (int i = 0; i < (int)path.size(); i++) {
            cout << locations[path[i]];

            if (i != (int)path.size() - 1)
                cout << " -> ";
        }

        cout << "\n";
    }

    // DFS: Explore connected locations
    void DFS(int current, bool visited[]) {
        visited[current] = true;
        cout << locations[current] << endl;

        for (auto edge : graph[current]) {
            int next = edge.first;

            if (!visited[next]) {
                DFS(next, visited);
            }
        }
    }

    void exploreCampus(int start) {
        bool visited[6] = {false};

        cout << "\nLocations explored using DFS:\n";
        DFS(start, visited);
    }

    // Dijkstra: Find the shortest-distance route
    void dijkstra(int start, int destination) {
        int dist[6];
        int parent[6];

        fill(dist, dist + 6, INT_MAX);
        fill(parent, parent + 6, -1);

        // Min heap: {distance, location}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        dist[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int distance = pq.top().first;
            int current = pq.top().second;
            pq.pop();

            if (distance != dist[current])
                continue;

            for (auto edge : graph[current]) {
                int next = edge.first;
                int weight = edge.second;

                if (dist[current] + weight < dist[next]) {
                    dist[next] = dist[current] + weight;
                    parent[next] = current;

                    pq.push({dist[next], next});
                }
            }
        }

        if (dist[destination] == INT_MAX) {
            cout << "No route available.\n";
            return;
        }

        vector<int> path;

        for (int v = destination; v != -1; v = parent[v]) {
            path.push_back(v);
        }

        reverse(path.begin(), path.end());

        cout << "\nShortest route:\n";

        for (int i = 0; i < (int)path.size(); i++) {
            cout << locations[path[i]];

            if (i != (int)path.size() - 1)
                cout << " -> ";
        }

        cout << "\nTotal distance: "
             << dist[destination] << " metres\n";
    }
};

int  runModule5() {
    CampusNavigation campus;

    // Add campus paths and distances in metres
    campus.addPath(0, 1, 200); // Gate - Academic Block
    campus.addPath(0, 4, 300); // Gate - Hostel
    campus.addPath(1, 2, 100); // Academic Block - Library
    campus.addPath(1, 3, 150); // Academic Block - Computer Lab
    campus.addPath(2, 3,  50); // Library - Computer Lab
    campus.addPath(2, 5, 120); // Library - Canteen
    campus.addPath(4, 5, 180); // Hostel - Canteen

    int choice;

    do {
        cout << "\n===== CAMPUSCONNECT NAVIGATION =====\n";
        cout << "1. Show Campus Locations\n";
        cout << "2. Check Reachability (BFS)\n";
        cout << "3. Explore Campus (DFS)\n";
        cout << "4. Find Shortest Route (Dijkstra)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            campus.showLocations();
        }
        else if (choice >= 2 && choice <= 4) {
            campus.showLocations();

            int start, destination;

            cout << "Enter starting location ID: ";
            cin >> start;

            if (start < 0 || start >= 6) {
                cout << "Invalid starting location!\n";
                continue;
            }

            if (choice == 3) {
                campus.exploreCampus(start);
                continue;
            }

            cout << "Enter destination location ID: ";
            cin >> destination;

            if (destination < 0 || destination >= 6) {
                cout << "Invalid destination!\n";
                continue;
            }

            if (choice == 2)
                campus.BFS(start, destination);
            else
                campus.dijkstra(start, destination);
        }
        else if (choice != 0) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
