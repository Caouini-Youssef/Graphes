#include <iostream>
#include <queue>

#include "Graph.h"

using namespace std;
#define INF INT16_MAX


namespace {
    Graph floyd_warshall(Graph &my_graph) {
        Graph result_graph = Graph(my_graph.n, my_graph.matrix);
        int cpt = 0;
        for (unsigned k = 0; k < my_graph.n; ++k) {
            for (unsigned i = 0; i < my_graph.n; ++i) {
                for (unsigned j = 0; j < my_graph.n; ++j) {
                    ++cpt;
                    if (i == j)
                        result_graph.matrix[i][j] = 0;
                    else if (result_graph.matrix[i][j] > (result_graph.matrix[i][k] + result_graph.matrix[k][j]) &&
                             result_graph.matrix[i][k] != INF && result_graph.matrix[k][j] != INF) {
                        result_graph.matrix[i][j] = (result_graph.matrix[i][k] + result_graph.matrix[k][j]);
                    }

                }
            }
        }
        cout << "cpt : " << cpt << endl;
        return result_graph;
    }

    bool onList(std::vector<int> &my_vector, int my_sommet) {
        if (my_vector.empty())
            return false;
        for (int i: my_vector)
            if (i == my_sommet)
                return true;
        return false;
    }

    void bfs_connectivity(Graph &my_graph) {
        std::vector<int> open_list;
        std::vector<int> closed_list;
        int current;
        int connex_number = 0;
        for (int i = 0; i < my_graph.n; ++i) {
            for (int j = 0; j < my_graph.n; ++j) {
                open_list.erase(open_list.begin(), open_list.end());
                if (!onList(closed_list, i)) {
                    open_list.push_back(i);
                    cout << "Le sommet " << i << " fait partie d'une composante connexe" << endl;
                    ++connex_number;
                } else if (!onList(closed_list, j)) {
                    open_list.push_back(j);
                    cout << "Le sommet " << j << " fait partie d'une composante connexe" << endl;
                    ++connex_number;
                }
                while (!open_list.empty()) {
                    current = open_list.back();
                    open_list.pop_back();
                    closed_list.push_back(current);
                    for (int k = 0; k < my_graph.n; ++k) {
                        if (my_graph.matrix[current][k] != 0 && !onList(closed_list, k)) {
                            open_list.insert(open_list.begin(), k);
                        }
                    }
                }
            }
        }
        cout << "La matrice a donc " << connex_number << " composantes connexes" << endl;
    }


    Graph bfs_weight(Graph &my_graph, int vertice) {
        Graph result_graph = Graph(my_graph.n);
        std::vector<int> open_list;
        std::vector<int> closed_list;
        int current;
        int cpt = 0;
        open_list.erase(open_list.begin(), open_list.end());
        open_list.push_back(vertice);
        while (!open_list.empty()) {
            current = open_list.back();
            open_list.pop_back();
            closed_list.push_back(current);
            for (int k = 0; k < my_graph.n; ++k) {
                ++cpt;
                if (my_graph.matrix[current][k] != INF && !onList(closed_list, k)) {
                    open_list.insert(open_list.begin(), k);
                    closed_list.push_back(k);
                    result_graph.matrix[current][k] = 1;
                }
            }
        }
        cout << "cpt = " << cpt << endl;
        return result_graph;
    }

    //Dijkstra algorithm to find all the shortest paths
    Graph dijkstra(Graph &my_graph, int vertice) {
        Graph result_graph = Graph(my_graph.n);
        std::vector<int> open_list;
        std::vector<int> closed_list;
        std::vector<int> weight_list(my_graph.n);
        std::vector<int> previous_list(my_graph.n);
        int current, min, j;

        for (unsigned i = 0; i < my_graph.n; ++i) {
            //open_list.push_back((int)i);
            weight_list[i] = INF;
            previous_list[i] = -1;
        }
        open_list.push_back(vertice);
        weight_list[vertice] = 0;
        previous_list[vertice] = vertice;
        while (!open_list.empty()) {
            current = open_list[0];
            min = weight_list[open_list[0]];
            j = 0;
            for (unsigned i = 0; i < open_list.size() - 1; ++i) {
                if (min > weight_list[open_list[i]]) {
                    min = weight_list[open_list[i]];
                    current = open_list[i];
                    j = (int) i;
                }
            }
            open_list.erase(open_list.begin() + j);
            closed_list.push_back(current);
            for (int k = 0; k < my_graph.n; ++k) {
                if (my_graph.matrix[current][k] != INF && !onList(closed_list, k)) {
                    if (weight_list[k] > weight_list[current] + my_graph.matrix[current][k]) {
                        weight_list[k] = weight_list[current] + my_graph.matrix[current][k];
                        previous_list[k] = current;
                        open_list.push_back(k);
                    }
                }
            }

        }
        for (unsigned i = 0; i < my_graph.n; ++i) {
            if (previous_list[i] != -1)
                result_graph.matrix[previous_list[i]][i] = weight_list[i];
        }
        return result_graph;
    }

    Graph AR_search(Graph &my_graph) {
        Graph result_graph = Graph(my_graph.n, 0);
        result_graph = bfs_weight(my_graph, 0);
        result_graph.non_oriented();
        return result_graph;
    }

    //use Prim algorithm to find the minimum spanning tree
    Graph prim(Graph &my_graph) {
        Graph result_graph = Graph(my_graph.n, 0);
        std::vector<int> open_list;
        std::vector<int> closed_list;
        std::vector<int> weight_list(my_graph.n);
        std::vector<int> previous_list(my_graph.n);
        int current, min, j, cpt=0;

        for (unsigned i = 0; i < my_graph.n; ++i) {
            //open_list.push_back((int)i);
            weight_list[i] = INF;
            previous_list[i] = -1;
        }
        open_list.push_back(0);
        weight_list[0] = 0;
        previous_list[0] = 0;
        while (!open_list.empty()) {
            current = open_list[0];
            min = weight_list[open_list[0]];
            j = 0;
            for (unsigned i = 0; i < open_list.size() - 1; ++i) {
                if (min > weight_list[open_list[i]]) {
                    min = weight_list[open_list[i]];
                    current = open_list[i];
                    j = (int) i;
                }
            }
            open_list.erase(open_list.begin() + j);
            closed_list.push_back(current);
            for (int k = 0; k < my_graph.n; ++k) {
                ++cpt;
                if (my_graph.matrix[current][k] != INF && !onList(closed_list, k)) {
                    if (weight_list[k] > my_graph.matrix[current][k]) {
                        weight_list[k] = my_graph.matrix[current][k];
                        previous_list[k] = current;
                        open_list.push_back(k);
                    }
                }
            }

        }
        for (unsigned i = 0; i < my_graph.n; ++i) {
            ++cpt;
            if (previous_list[i] != -1)
                result_graph.matrix[previous_list[i]][i] = weight_list[i];
        }
        cout << "Compteur d'it??rations Prim : " << cpt << endl;
        return result_graph;
    }

    //use Kruskal algorithm to find the minimum spanning tree
    Graph kruskal(Graph &my_graph) {
        Graph result_graph = Graph(my_graph.n, 0);
        std::vector<int> closed_list;
        std::vector<int> weight_list(my_graph.n);
        std::vector<int> previous_list(my_graph.n);
        int current, min, j, cpt = 0;
        std::vector<int> edge_list;
        for (unsigned i = 0; i < my_graph.n; ++i) {
            weight_list[i] = INF;
            previous_list[i] = -1;
            for (unsigned j = 0; j < my_graph.n; ++j) {
                ++cpt;
                if (my_graph.matrix[i][j] != INF) {
                    edge_list.push_back(i);
                    edge_list.push_back(j);
                    edge_list.push_back(my_graph.matrix[i][j]);
                }
            }
        }

        //std::sort(edge_list.begin(), edge_list.end(), [](int a, int b) {
        //    return a < b;
        //});
        for (unsigned i = 0; i < edge_list.size(); i += 3) {
            ++cpt;
            weight_list[edge_list[i + 1]] = edge_list[i + 2];
            previous_list[edge_list[i + 1]] = edge_list[i];
        }
        for (unsigned i = 0; i < my_graph.n; ++i) {
            ++cpt;
            if (previous_list[i] != -1)
                result_graph.matrix[previous_list[i]][i] = weight_list[i];
        }
        my_graph.print_matrix();
        result_graph.print_matrix();
        cout << "Compteur d'it??rations Kruskal : " << cpt << endl;
        return result_graph;
    }

}

int main()
{
    srand (time(NULL));
    Graph my_graph = Graph(8, 35);
    Graph my_graph_2 = Graph(8,15);
//    my_graph_2.open_matrix();
//    my_graph_2.non_oriented();
    my_graph.print_matrix();
    cout << endl << "2??me matrice" << endl;
    my_graph_2.print_matrix();

    //cout << endl << "produit" << endl;
    //my_graph = compute_product(my_graph, my_graph_2);
    //my_graph.print_matrix();

    cout << endl << "power 8" << endl;
    my_graph = my_graph_2.power(8);
    my_graph.print_matrix();

    cout << endl << "power 7" << endl;
    my_graph = my_graph_2.power(7);
    my_graph.print_matrix();



    std::vector<std::vector<int>> matrix  =
            {{INF, INF, 36, INF, INF, 19, INF, INF},
             {INF, INF, INF, INF, INF, INF, 50, 43},
             {36, INF, INF, 56, 55, 31, INF, 36},
             {INF, INF, 56, INF, INF, INF, 15, INF},
             {INF, INF, 55, INF, INF, INF, INF, INF},
             {19, INF, 31, INF, INF, INF, 37, 52},
             {INF, 50, INF, 15, INF, 37, INF, INF},
             {INF, 43, 36, INF, INF, 52, INF, INF}};

    std::vector<std::vector<int>> matrix_k5  =
            {{INF, 1, 1, 1, 1,INF},
             {1, INF, 1, 1, 1,INF},
             {1, 1, INF, 1, 1,1},
             {1, 1, 1, INF, 1,INF},
             {1, 1, 1, 1, INF,INF},
             {1, 1, 1, 1, INF,INF}};

    std::vector<std::vector<int>> matrix_M  =
            {{INF, 10, 18, 8, 13, 15},
             {10, INF, 12, 13, 16, 11},
             {18, 12, INF, 17, 15, 7},
             {8, 13, 17, INF, 6, 12},
             {13, 16, 15, 6, INF, 8},
             {15, 11, 7, 12, 8, INF}};
    Graph my_graph3 = Graph(8, matrix);
    cout << endl << "3??me matrice" << endl;
    my_graph3.print_matrix();

    Graph my_graph4 = Graph(6, matrix_M);
    cout << endl << "4??me matrice" << endl;
    my_graph4.print_matrix();

    cout << endl << "Coloriage Glouton" << endl;
    my_graph3.greedy_color();

    cout << endl << "Coloriage des ar??tes" << endl;
    my_graph3.edge_coloring();


    cout << endl << "Floyd Warshall" << endl;
    my_graph = floyd_warshall(my_graph3);
    my_graph.print_matrix();

    cout << endl << "BFS connexite" << endl;
    bfs_connectivity(my_graph_2);

    cout << endl << "BFS chemin" << endl;
    my_graph = bfs_weight(my_graph3,0);
    my_graph.print_matrix();

    cout << endl << "UCS" << endl;
    my_graph = dijkstra(my_graph3,7);
    my_graph.print_matrix();

    cout << endl << "Recherche de clique 5" << endl;
    my_graph3 = Graph(6,matrix_k5);
    my_graph3.print_matrix();
    my_graph3.clique_search();
    cout << endl;

    my_graph3 = Graph(8,matrix);

    my_graph = AR_search(my_graph3);
    cout << endl << "Arbre de Recouvrement" << endl;
    my_graph.print_matrix();

    my_graph = prim(my_graph3);
    my_graph.non_oriented();
    cout << endl << "Prim Graphe G" << endl;
    my_graph.print_matrix();

    my_graph = prim(my_graph4);
    my_graph.non_oriented();
    cout << endl << "Prim Graphe M" << endl;
    my_graph.print_matrix();

    my_graph = kruskal(my_graph3);
    //my_graph.non_oriented();
    cout << endl << "Kruskal" << endl;
    my_graph.print_matrix();
    return 0;
}
