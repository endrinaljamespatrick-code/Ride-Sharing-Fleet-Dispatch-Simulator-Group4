#include <iostream>
#include <string>
using namespace std;

// ===================== ENDRINAL TASK 3: DIJKSTRA’S FASTEST PICK‑UP ROUTE =====================
const int MAX_NODES = 6; // City locations: 0‑5

// Get node name for display
string getNodeName(int node) {
    switch(node) {
        case 0: return "Driver‑Start";
        case 1: return "Downtown (Heavy Traffic)";
        case 2: return "Main Ave";
        case 3: return "Park Road";
        case 4: return "Subway Junction";
        case 5: return "Passenger‑Destination";
        default: return "Unknown";
    }
}

// Manual Dijkstra (NO STL priority queue)
void dijkstra(int graph[MAX_NODES][MAX_NODES], int start, int dest) {
    int dist[MAX_NODES];
    bool visited[MAX_NODES];
    int prev[MAX_NODES]; // For reconstructing route

    // Initialize
    for(int i = 0; i < MAX_NODES; i++) {
        dist[i] = 9999;
        visited[i] = false;
        prev[i] = -1;
    }
    dist[start] = 0;

    for(int count = 0; count < MAX_NODES - 1; count++) {
        // Step 1: Find unvisited node with smallest distance (manual min search)
        int minDist = 9999;
        int u = -1;
        for(int i = 0; i < MAX_NODES; i++) {
            if(!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }
        if(u == -1) break;
        visited[u] = true;

        // Step 2: Relax edges
        for(int v = 0; v < MAX_NODES; v++) {
            if(!visited[v] && graph[u][v] != 0 && dist[u] != 9999 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                prev[v] = u;
            }
        }
    }

    // Reconstruct route
    cout << "\n===== ENDRINAL DIJKSTRA FASTEST PICK‑UP ROUTE =====\n";
    cout << "Start: " << getNodeName(start) << "\n";
    cout << "Destination: " << getNodeName(dest) << "\n\n";

    cout << "Fastest Route: ";
    int curr = dest;
    string routeStr = "";
    while(curr != -1) {
        routeStr = getNodeName(curr) + " → " + routeStr;
        curr = prev[curr];
    }
    // Remove last arrow
    if(routeStr.length() > 4) routeStr = routeStr.substr(0, routeStr.length() - 4);
    cout << routeStr << "\n";
    cout << "Total Estimated Time: " << dist[dest] << " minutes\n";
    cout << "Heavy‑traffic road (Node 0 → Node 1 = 20 min) was automatically bypassed\n";
    cout << "====================================================\n";
}

int main() {
    cout << "===== TASK 3: DIJKSTRA’S SHORTEST PATH (ENDRINAL RIDE‑SHARING) =====\n";

    // Adjacency Matrix: 0 = no road; value = travel time (minutes)
    int cityGraph[MAX_NODES][MAX_NODES] = {
        {0, 20, 5, 0, 0, 0},   // Node 0: Start (Driver) → 1(20 min HEAVY TRAFFIC), 2(5 min)
        {20, 0, 0, 8, 0, 0},   // Node 1: Downtown Heavy Traffic
        {5, 0, 0, 3, 0, 0},    // Node 2: Main Ave
        {0, 8, 3, 0, 4, 0},    // Node 3: Park Road
        {0, 0, 0, 4, 0, 6},    // Node 4: Subway Junction
        {0, 0, 0, 0, 6, 0}     // Node 5: Passenger Destination
    };

    // Example: Closest Driver from Task 2 is at Node 0; Passenger at Node 5
    int driverStartNode = 0;
    int passengerDestNode = 5;

    dijkstra(cityGraph, driverStartNode, passengerDestNode);

    cout << "\n===== TASK 3 COMPLETE =====\n";
    return 0;
}