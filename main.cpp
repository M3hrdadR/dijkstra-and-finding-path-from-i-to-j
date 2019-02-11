#include <iostream>
using namespace std;

class Graph{
public:
    Graph();
    int Min_dis(int *S, int *D);
    int get_number_of_vertices(){
        return n;
    }
    void graph_read(int n);
    void dijkstra(int first);
private:
    int ** G;
    int n;
};

Graph::Graph() {
    cout << "Enter the number of vertices :" << endl;
    cin >> n;
    G = new int *[n];
    for (int i = 0; i < n; i++){
        G[i] = new int [n];
    }
    cout << "Fill the adjacency matrix : " << endl;
    graph_read(n);
}

void Graph::graph_read(int n) {
    int tmp = 0;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; ++j) {
            cout << "Enter Weight between "<< i+1 << " and " << j+1 << " or 0 if they are not connected: " << endl;
            cin >> tmp;
            if(tmp == 0)
                G[i][j] = 2000;
            else
                G[i][j] = tmp;
        }
    }
}

void Graph::dijkstra(int first) {
    int index = 0;
    int **Path = new int *[n];
    int *D = new int [n];
    int *S = new int [n];
    for (int k = 0; k < n; ++k) {
        S[k] = 0;
        Path[k] = new int[n];
        Path[k][0] = first;
    }
    S[first] = 1;
    for (int i = 0; i < n; ++i) {
        D[i] = G[first][i];
    }

    for (int j = 1; j < n; ++j) {
        index = Min_dis(S, D);
        S[index] = 1;
        for (int i = 0; i < n; ++i) {
            if (S[i] == 0) {
                D[i] = min(D[i], D[index] + G[index][i]);
            }
            if (D[i] == D[index] + G[index][i]) {
                if (G[Path[i][j - 1]][index] != 2000)
                    Path[i][j] = index;
                else {
                    for (int h = 0; h <= j - 1; h++)
                        Path[i][h] = Path[index][h];
                    Path[i][j] = index;
                }
            }
            else {
                Path[i][j] = Path[i][j - 1];
            }
        }
    }
    cout << "Distance from "<< first + 1 << " vertex :" << endl;
    for (int l = 0; l < n; ++l) {
        if (l != first) {
            cout << "vertex : " << l + 1 << " = " << D[l] << endl;
        }
    }
    cout << endl;
    cout << "Path from " << first + 1 << " vertex" <<endl;
    for (int m = 0; m < n; ++m) {
        if (m != first) {
            cout << "vertex: " << m + 1 << endl;
            cout << first + 1 << " " ;
            for (int i = 1; i < n; ++i) {
                cout << Path[m][i] + 1 << " ";
            }
            cout << endl;
        }
    }
}

int Graph::Min_dis(int *S, int * D) {
    int min = INT8_MAX;
    int index = 0;
    for (int i = 0; i < n; i++){
        if (S[i] == 0 and D[i] < min){
            min = D[i];
            index = i;
        }
    }
    return index;
}

int main() {
    Graph graph;
    int n = graph.get_number_of_vertices();
    for (int i = 0; i < n; ++i) {
        graph.dijkstra(i);
    }
    return 0;
}