#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <climits>

using namespace std;
class node{
  public:
    int tempo;
    int preco;
    int dist;
    node(int tempo, int preco, int dist){ //node com os 3 pesos
      this->tempo = tempo;
      this->preco = preco;
      this->dist = dist;
  }
};

class grafo{
  int num_vertices;
  vector<list<pair<int, node>>> adjlista; //adjlista recebe um par, com o destino e os pesos
  public:
    grafo(int n) : num_vertices(n), adjlista(n) {}
    void aresta(int fonte, int destino, int tempo, int preco, int dist);
    void djikstrapreco(int source, int dest);
    void djikstratempo(int source, int dest);
    void djikstradistancia(int source, int dest);
};

void grafo::aresta(int fonte, int destino, int tempo, int preco, int dist){
  if (fonte >= adjlista.size()) {
    adjlista.resize(fonte + 1);
}
  adjlista[fonte].emplace_back(destino, node(tempo, preco, dist));
  adjlista[destino].emplace_back(fonte, node(tempo, preco, dist));
}

void grafo::djikstrapreco(int source, int dest){
  int dist[10];
  int visited[10];
  int parent[10];

  //priority queue que ordena os elementos em ordem crescente, com base no primeiro valor do par
  //Cada elemento da fila é um par e esta fila é implementada com um vetor
  priority_queue<pair<int,int>, vector<pair<int, int> >, greater<pair<int, int>>> pq; 
  for (int i = 0; i < 10; i++){ //prepara as variaveis
    dist[i] = INT_MAX;
    visited[i] = false;
    parent[i] = -1;
  }
  dist[source] = 0; //Coloca a fonte como zero
  pq.push(make_pair(dist[source], source)); //Cria um par para colocar na pq com a distancia do nó e o nó
  
  //Aplicacao do dijkstra
  while(!pq.empty()){
    pair<int, int> p = pq.top();
    int u = p.second;
    pq.pop();
    
    if(visited[u] == false){
      if(u == dest) break;
      visited[u] = true;
      list<pair<int, node> >::iterator it; //Cria uma iterador para o modelo da adjlista
      for(it = adjlista[u].begin(); it != adjlista[u].end(); it++){
        int v = it->first;
        int cost = it->second.preco;
        //Relaxamento
        if(dist[v] > dist[u] + cost){
          dist[v] = dist[u] + cost;
          parent[v] = u;
          pq.push(make_pair(dist[v], v));
        }
      }
    }
  }
  cout << "Custo: R$ " << dist[dest] << endl;
  if(parent[dest] == -1)
    cout << "Nao ha caminho\n";
  /*else{ //print de caminho
    vector<int> route;
    int current = dest;
    while(current!= -1){
      route.push_back(current);
      current = parent[current];
    }
    cout << "Rota: ";
    for(int i = route.size() -1; i>= 0; i--){
      cout << route[i];
      if(i > 0){
        cout << " -> ";
      }
    }
    cout << endl;
  }*/
}

void grafo::djikstratempo(int source, int dest){
int dist[10];
  int visited[10];
  int parent[10];

  priority_queue<pair<int,int>, vector<pair<int, int> >, greater<pair<int, int>>> pq;
  for (int i = 0; i < 10; i++){
    dist[i] = INT_MAX;
    visited[i] = false;
    parent[i] = -1;
  }
  dist[source] = 0;
  pq.push(make_pair(dist[source], source));
  

  while(!pq.empty()){
    pair<int, int> p = pq.top();
    int u = p.second;
    pq.pop();
    
    if(visited[u] == false){
      if(u == dest) break;
      visited[u] = true;
      list<pair<int, node> >::iterator it;
      for(it = adjlista[u].begin(); it != adjlista[u].end(); it++){
        int v = it->first;
        int cost = it->second.tempo;

        if(dist[v] > dist[u] + cost){
          dist[v] = dist[u] + cost;
          parent[v] = u;
          pq.push(make_pair(dist[v], v));
        }
      }
    }
  }
  cout << "Tempo: " << dist[dest] << "minutos ";
  if(parent[dest] == -1)
    cout << "Nao ha caminho\n";
  /*else{
    vector<int> route;
    int current = dest;
    while(current!= -1){
      route.push_back(current);
      current = parent[current];
    }
    cout << "Rota: ";
    for(int i = route.size() -1; i>= 0; i--){
      cout << route[i];
      if(i > 0){
        cout << " -> ";
      }
    }
    cout << endl;
  }*/

}

void grafo::djikstradistancia(int source, int dest){
int dist[10];
  int visited[10];
  int parent[10];

  priority_queue<pair<int,int>, vector<pair<int, int> >, greater<pair<int, int>>> pq;
  for (int i = 0; i < 10; i++){
    dist[i] = INT_MAX;
    visited[i] = false;
    parent[i] = -1;
  }
  dist[source] = 0;
  pq.push(make_pair(dist[source], source));
  

  while(!pq.empty()){
    pair<int, int> p = pq.top();
    int u = p.second;
    pq.pop();
    
    if(visited[u] == false){
      if(u == dest) break;
      visited[u] = true;
      list<pair<int, node> >::iterator it;
      for(it = adjlista[u].begin(); it != adjlista[u].end(); it++){
        int v = it->first;
        int cost = it->second.dist;

        if(dist[v] > dist[u] + cost){
          dist[v] = dist[u] + cost;
          parent[v] = u;
          pq.push(make_pair(dist[v], v));
        }
      }
    }
  }
  cout << "Distância: " << dist[dest] <<"km ";
  if(parent[dest] == -1)
    cout << "Nao ha caminho\n";
  /*else{
    vector<int> route;
    int current = dest;
    while(current!= -1){
      route.push_back(current);
      current = parent[current];
    }
    cout << "Rota: ";
    for(int i = route.size() -1; i>= 0; i--){
      cout << route[i];
      if(i > 0){
        cout << " -> ";
      }
    }
    cout << endl;
  }*/

}

int main(){
  grafo g(10);
  //Source, destino, tempo, preco, dist
  g.aresta(0, 1, 18, 6, 12);
  g.aresta(0, 2, 35, 10, 25);
  g.aresta(1, 3, 25, 8, 18);
  g.aresta(1, 4, 40, 12, 30);
  g.aresta(2, 4, 28, 9, 20 );
  g.aresta(2, 5, 20, 7, 15);
  g.aresta(3, 6, 30, 9, 22 );
  g.aresta(4, 6, 22, 6, 16);
  g.aresta(4, 7, 45, 15, 35);
  g.aresta(5, 7, 32, 10, 25);
  g.aresta(6, 8, 27, 8, 20);
  g.aresta(7, 8, 24, 7, 18);
  g.aresta(7, 9, 38, 14, 30);
  g.aresta(8, 9, 20, 5, 15);

  char fonte, destino;
  int src, dest;
  cin >> fonte >> destino;
  if(fonte > 'Z')
    fonte -= 32;
  if(destino > 'Z')
    destino -= 32;
  src = (int)(fonte) - 'A';
  dest = (int)(destino) - 'A';
 
  g.djikstradistancia(src,dest);
  g.djikstratempo(src,dest);
  g.djikstrapreco(src, dest);
  
  while(cin >> fonte >> destino){
    if(fonte > 'Z')
      fonte -= 32;
    if(destino > 'Z')
      destino -= 32;
    src = (int)(fonte) - 'A';
    dest = (int)(destino) - 'A';
   
    g.djikstradistancia(src,dest);
    g.djikstratempo(src,dest);
    g.djikstrapreco(src, dest);
  }


  return 0;

}
