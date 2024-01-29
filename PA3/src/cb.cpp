#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef struct edge {
    int u;
    int v;
    int weight;
} edge;

typedef struct DisjointSets { 
    int *parent, *rank; 
    int n; 
  
    DisjointSets(int n) { 
        this->n = n; 
        parent = new int[n+1]; 
        rank = new int[n+1]; 
  
        for (int i = 0; i <= n; i++) { 
            rank[i] = 0; 
            parent[i] = i; 
        } 
    } 
  
    int find(int u) { 
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    void merge(int x, int y) { 
        x = find(x); 
        y = find(y); 
  
        if (rank[x] > rank[y]) 
            parent[y] = x; 
        else 
            parent[x] = y; 
            if (rank[x] == rank[y]) 
                rank[y]++; 
    } 
} DisjointSets; 

edge* counting_sort(edge* edge_set, int M, int N) {
 
    int* countArray = new int[M + 1];
    for (int i=0 ; i<M+1 ; ++i){
        countArray[i] = 0;
    }
 
    for (int i = 0; i < N; i++) {
        countArray[edge_set[i].weight + (M/2)]++;
    }
 
    for (int i = 1; i <= M; i++) {
        countArray[i] += countArray[i - 1];
    }
 
    edge* sort_edge_set = new edge[N];
 
    for (int i = N - 1; i >= 0; i--) {
        sort_edge_set[countArray[edge_set[i].weight + (M/2)]- 1] = edge_set[i];
        countArray[edge_set[i].weight + (M/2)]--;
    }
 
    return sort_edge_set;
}

vector<edge> kruskalMST(edge* edge_set, int V, int E) { 
    int mst_weight = 0;
  
    edge* sort_edge_set = counting_sort(edge_set, 200, E);
  
    DisjointSets ds(V); 

    vector<edge> remove_edge;
    vector<edge> mst_edge;
    int total_weight = 0;
    int num_remove_edge = 0;
  
    for (int i=0 ; i<E ; ++i) { 
        int set_u = ds.find(sort_edge_set[i].u); 
        int set_v = ds.find(sort_edge_set[i].v); 

        edge e;
        e.u = sort_edge_set[i].u;
        e.v = sort_edge_set[i].v;
        e.weight = sort_edge_set[i].weight * (-1);
   
        if (set_u != set_v) {  
            ds.merge(set_u, set_v); 
            mst_edge.push_back(e);
        } else {
            remove_edge.push_back(e);
            total_weight += e.weight;
            num_remove_edge += 1;
        }
    }
 
    vector<edge> final_edge;
    final_edge.insert(final_edge.end(),remove_edge.begin(),remove_edge.end());
    final_edge.insert(final_edge.end(),mst_edge.begin(),mst_edge.end());

    edge e;
    e.u = num_remove_edge;
    e.v = 0;
    e.weight = total_weight;
    final_edge.push_back(e);
    return final_edge; 
} 

bool DFS_recursive(vector<vector<int>>& graph, vector<char>& colors, int u) {
    colors[u] = 'g';
    for (int v = 0; v < graph[u].size(); v++) {
        if (colors[graph[u][v]] == 'g')
            return true;
        if (colors[graph[u][v]] == 'w' && DFS_recursive(graph, colors, graph[u][v]))
            return true;
    }
    colors[u] = 'b';
    return false;
}

bool DFS(vector<vector<int>>& graph) {
    vector<char> colors(graph.size(), 'w');
    for (int i = 0; i < graph.size(); i++) {
        if (colors[i] == 'w') {
            if (DFS_recursive(graph, colors, i))
                return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]){
    ifstream infile;
    ofstream outfile;

    infile.open(argv[1]);
    outfile.open(argv[2]);

    char type;
    int V , E;
    infile >> type >> V >> E;

    edge* edge_set = new struct edge[E];

    vector<vector<int>> adj_list(V);

    int u, v, weight;
    for (int i=0 ; i<E ; ++i){
        infile >> u >> v >> weight;
        edge_set[i].u = u;
        edge_set[i].v = v;
        edge_set[i].weight = weight * (-1);
    }

    vector<edge> remove_edge;

    if (type == 'u'){
        remove_edge = kruskalMST(edge_set, V, E);
    } else {
        remove_edge = kruskalMST(edge_set, V, E);
        vector<edge> final_remove_edge;
        int total_weight = 0;
        int num_remove_edge = 0;
        for (int i=remove_edge[remove_edge.size()-1].u ; i<remove_edge.size()-1 ; ++i){
            adj_list[remove_edge[i].u].push_back(remove_edge[i].v);
        }

        for (int i=0 ; i<remove_edge[remove_edge.size()-1].u ; ++i){
            edge e;
            e.u = remove_edge[i].u;
            e.v = remove_edge[i].v;
            e.weight = remove_edge[i].weight;
            if (e.weight >= 0) {
                vector<vector<int>> add_graph = adj_list;
                add_graph[e.u].push_back(e.v);
                if (DFS(add_graph)){
                    final_remove_edge.push_back(e);
                    total_weight += e.weight;
                    num_remove_edge += 1;
                } else {
                    adj_list = add_graph;
                }
            } else {
                final_remove_edge.push_back(e);
                total_weight += e.weight;
                num_remove_edge += 1;
            } 
        }

        edge e;
        e.u = num_remove_edge;
        e.v = 0;
        e.weight = total_weight;
        final_remove_edge.push_back(e);
        remove_edge = final_remove_edge;
    }
    
    outfile << remove_edge[remove_edge.size()-1].weight  << "\n";  
    for (int i=0 ; i<remove_edge[remove_edge.size()-1].u ; ++i){
        outfile << remove_edge[i].u << " " << remove_edge[i].v << " " << remove_edge[i].weight  << "\n";  
    }

    infile.close();
    outfile.close();
    return 0;
}