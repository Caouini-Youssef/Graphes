#include <iostream>
#include <queue>

#include "Graph.h"

using namespace std;
#define INF INT16_MAX


namespace  {
    Graph floyd_warshall(Graph &my_graph)
    {
        Graph result_graph = Graph(my_graph.n,my_graph.matrix);
        int cpt = 0;
        for(unsigned k = 0; k < my_graph.n; ++k)
        {
            for(unsigned i = 0; i < my_graph.n; ++i)
            {
                for(unsigned j = 0; j < my_graph.n; ++j)
                {
                    ++cpt;
                    if(i == j)
                        result_graph.matrix[i][j] = 0;
                    else if(result_graph.matrix[i][j] > (result_graph.matrix[i][k] + result_graph.matrix[k][j]) && result_graph.matrix[i][k] != INF && result_graph.matrix[k][j] != INF)
                    {
                        result_graph.matrix[i][j] = (result_graph.matrix[i][k] + result_graph.matrix[k][j]);
                    }

                }
            }
        }
        cout << "cpt : " << cpt << endl;
        return result_graph;
    }

    bool onList(std::vector<int> &my_vector, int my_sommet)
    {
        if(my_vector.empty())
            return false;
        for (int i: my_vector)
            if (i == my_sommet)
                return true;
        return false;
    }

    void bfs_connectivity(Graph &my_graph)
    {
        std::vector<int> open_list;
        std::vector<int> closed_list;
        int current;
        int connex_number = 0;
        for(int i =0; i < my_graph.n; ++i)
        {
            for(int j =0; j < my_graph.n; ++j)
            {
                open_list.erase(open_list.begin(),open_list.end());
                if (!onList(closed_list,i))
                {
                    open_list.push_back(i);
                    cout << "Le sommet " << i << " fait partie d'une composante connexe" << endl;
                    ++connex_number;
                }
                else if (!onList(closed_list,j))
                {
                    open_list.push_back(j);
                    cout << "Le sommet " << j << " fait partie d'une composante connexe" << endl;
                    ++connex_number;
                }
                while(!open_list.empty())
                {
                    current = open_list.back();
                    open_list.pop_back();
                    closed_list.push_back(current);
                    for(int k = 0; k < my_graph.n; ++k)
                    {
                        if(my_graph.matrix[current][k] != 0 && !onList(closed_list,k))
                        {
                            open_list.insert(open_list.begin(),  k);
                        }
                    }
                }
            }
        }
        cout << "La matrice a donc " << connex_number << " composantes connexes" << endl;
    }


    Graph bfs_weight(Graph &my_graph, int vertice)
    {
        Graph result_graph = Graph(my_graph.n);
        std::vector<int> open_list;
        std::vector<int> closed_list;
        int current;
        int cpt = 0;
        open_list.erase(open_list.begin(),open_list.end());
        open_list.push_back(vertice);
        while(!open_list.empty())
        {
            current = open_list.back();
            open_list.pop_back();
            closed_list.push_back(current);
            for(int k = 0; k < my_graph.n; ++k)
            {
                ++cpt;
                if(my_graph.matrix[current][k] != INF && !onList(closed_list,k))
                {
                    open_list.insert(open_list.begin(),k);
                    closed_list.push_back(k);
                    result_graph.matrix[current][k] = 1;
                }
            }
        }
        cout << "cpt = " << cpt << endl;
        return result_graph;
    }

    int min(std::vector<int> &my_vector, std::vector<int> &open_list)
    {
        auto min_iter = my_vector.begin();
        for(auto iter = my_vector.begin();iter != my_vector.end(); ++iter)
        {
            if(*min_iter > *iter)
            {
                min_iter = iter;
            }
        }
        //std::erase(open_list,min_iter.base() - my_vector.begin().base());
        cout << min_iter.base() - my_vector.begin().base() << " / " << *min_iter << endl;
        return 2;
    }

    //Dijkstra algorithm to find all the shortest paths
    Graph dijkstra(Graph &my_graph, int vertice)
    {
        Graph result_graph = Graph(my_graph.n);
        std::vector<int> open_list;
        std::vector<int> closed_list;
        std::vector<int> weight_list(my_graph.n);
        std::vector<int> previous_list(my_graph.n);
        int current, min, j;

        for(unsigned i = 0; i < my_graph.n; ++i)
        {
            //open_list.push_back((int)i);
            weight_list[i] = INF;
            previous_list[i] = -1;
        }
        open_list.push_back(vertice);
        weight_list[vertice] = 0;
        previous_list[vertice] = vertice;
        while(!open_list.empty())
        {
            current = open_list[0];
            min = weight_list[open_list[0]];
            j = 0;
            for(unsigned i = 0; i < open_list.size()-1; ++i)
            {
                if(min > weight_list[open_list[i]])
                {
                    min = weight_list[open_list[i]];
                    current = open_list[i];
                    j = (int)i;
                }
            }
            open_list.erase(open_list.begin() + j);
            closed_list.push_back(current);
            for(int k = 0; k < my_graph.n; ++k)
            {
                if(my_graph.matrix[current][k] != INF && !onList(closed_list,k))
                {
                    if(weight_list[k] > weight_list[current] + my_graph.matrix[current][k])
                    {
                        weight_list[k] = weight_list[current] + my_graph.matrix[current][k];
                        previous_list[k] = current;
                        open_list.push_back(k);
                    }
                }
            }

        }
        for(unsigned i = 0; i < my_graph.n; ++i)
        {
            if(previous_list[i]!=-1)
                result_graph.matrix[previous_list[i]][i] = weight_list[i];
        }
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
    cout << endl << "2ème matrice" << endl;
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

    Graph my_graph3 = Graph(8, matrix);
    cout << endl << "3ème matrice" << endl;
    my_graph3.print_matrix();

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
    return 0;
}
