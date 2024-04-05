# Kosaraju

## Sobre

O algoritmo de Kosaraju é utilizado para encontrar de maneira eficiente componentes fortemente conexos (SCC) em um digrafo. É um algoritmo muito interessante em seu funcionamento, no início ele percorre os arcos do digrafo invertendo suas direções, obtendo um grafo direcionado ``G_R`` que é o inverso do digrafo original ``G``. Em seguida é feita uma busca em profundidade (DFS) em ``G_R`` que tem a função de calcular uma permutação em pós-ordem dos vértices de ``G_R``. A permutação pós-ordem é calculada no algoritmo de Kosaraju para garantir que cada componente fortemente conectado seja visitado “de cima para baixo”. Em outras palavras, se tivermos um SCC ``A`` que pode alcançar outro SCC ``B``, queremos processar ``A`` antes de ``B``. Após a primeira etapa, dâ-se início a outra DFS mas agora no digrafo original ``G``, onde se analisará cada vértice com base na pós-ordem calculada anteriormente em ``G_R``. Cada nova etapa se inícia no vértice de maior prioridade que ainda não foi visitado. O conjunto de vértices localizados em cada etapa caracteriza um componente fortemente conexo no digrafo ``G``.

## Exemplo

```c++
#include <bits/stdc++.h>
using namespace std;

vector<int> pre;
vector<int> post;
int contador_1 = 0;
int contador_2 = 0;

vector<vector<int>> reverse(vector<vector<int>> &adj_list) {
    int size = adj_list.size();
    vector<vector<int>> reversed(size);

    for(int u = 0; u < size; u++){
        for(auto v: adj_list[u]) {
            reversed[v].push_back(u);
        }
    }
    return reversed;
}
void dfs_recursiva(vector<vector<int>> &adj_list, int i) {
    pre[i] = ++contador_1;
    for(auto j: adj_list[i]) {
        if(!pre[j]){
            dfs_recursiva(adj_list, j);
        }
    }
    post[i] = contador_2++;
}
void dfs_pos(vector<vector<int>> &adj_list){
    int size = adj_list.size();
    for(int i = 0; i < size; i++){
        if(!pre[i]) {
            dfs_recursiva(adj_list, i);
        }
    }
}
void sort_pos_vector(){
    int size = post.size();
    vector<int> aux(size);

    for(int i = 0; i < size; i++) {
        aux[post[i]] = i;
    }
    post = aux;
}

void dfs_pre_recursao(vector<vector<int>> &adj_list, int i, vector<int> &scc) {
    pre[i] = ++contador_1;
    scc.push_back(i);
    for(auto j: adj_list[i]) {
        if(!pre[j]) {
            dfs_pre_recursao(adj_list, j, scc);
        }
    }
}
vector<vector<int>> dfs_pre(vector<vector<int>> &adj_list){
    vector<vector<int>> sccs;
    pre.assign(adj_list.size(), 0);
    contador_1 = 0;
    int size = post.size();
    sort_pos_vector();
    for(int i = size - 1; i >= 0; i--) {
        if(!pre[post[i]]) {
            vector<int> scc;
            dfs_pre_recursao(adj_list, post[i], scc);
            sccs.push_back(scc);
        }
    }
    return sccs;
}
