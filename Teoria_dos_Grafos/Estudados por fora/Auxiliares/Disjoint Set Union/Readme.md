# Disjoint Set Union (DSU)

## Sobre

Conhecida como Union Find por conta das suas duas principais funções ``find_set(a)`` e ``union_sets(a,b)`` que são responsáveis por retornar o vétice representante na arvore do conjuto ``a`` e unir dois conjuntos onde o conjunto ``A`` é onde está localizado ``a`` e o conjunto ``B`` é onde está localizado ``b``, respectivamente. É fácil ver que se ``a`` e ``b`` estão no mesmo conjunto ``find_set(a)`` e ``find_set(b)`` retornaram o mesmo representante. 

A função ``find_set`` também utiliza de uma otimização conhecida como ``path compression`` ou compressão de caminho no bom e velho português. Quando você chama a função ``find_set`` para um elemento, ela percorre o caminho do elemento até o representante (ou “pai”) do conjunto. Sem compressão de caminho, cada chamada para ``find_set`` teria que percorrer esse caminho novamente. A compressão de caminho otimiza isso, fazendo com que cada elemento no caminho aponte diretamente para o representante do conjunto. Assim, futuras chamadas de ``find_set`` para esses elementos serão muito mais rápidas, pois o caminho para o representante do conjunto foi “comprimido”.

A estrutura também pode conter a função ``make_set(a)`` que cria um novo conjuto através do vétice ``a``, tornando ``a`` o representante do novo conjunto, geralmente cada elemento começa em seu próprio conjunto.

A versão utilizada no algoritimo de Kruskal é a ``Union by rank`` ou União por rank, essa adaptação passa por três etapas principais. No início, cada elemento é um conjunto separado (ou seja, um conjunto disjunto). O “rank” de cada conjunto é inicialmente 0. Quando dois conjuntos são unidos usando a operação ``union_sets``, a árvore de menor rank se torna uma subárvore da árvore de maior rank. Se ambas as árvores têm o mesmo rank, escolhemos uma delas arbitrariamente e incrementamos o rank da árvore resultante. A união por rank garante que as árvores permaneçam aproximadamente balanceadas, minimizando a altura das árvores. Isso é crucial para garantir que as operações ``find_set`` e ``union_sets()`` possam ser realizadas eficientemente.

Exemplo:
```c++
#include <bits/stdc++.h>
using namespace std;

vector<int> parent(100001), ranks(100001, 0);

void make_set(int v) {
    parent[v] = v;
    ranks[v] = 0;
}
int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (ranks[a] < ranks[b])
            swap(a, b);
        parent[b] = a;
        if (ranks[a] == ranks[b])
            ranks[a]++;
    }
}
int main() {
    for(int i = 0; i < parent.size(); i++) {
        make_set(i);
    }
    union_sets(1, 2);
    union_sets(2, 3);
    union_sets(3, 4);
    cout << find_set(2) << endl;
    return 0;
}