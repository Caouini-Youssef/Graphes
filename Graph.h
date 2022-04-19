//
// Created by torakun on 16/03/2022.
//

#ifndef CLION_GRAPH_H
#define CLION_GRAPH_H


#include <iostream>
#include <vector>
#include <random>

class Graph
{
public:
    unsigned n;
    std::vector<std::vector<int>> matrix;
    explicit Graph(unsigned int n = 8, unsigned weight = 0);
    explicit Graph(unsigned n, int p);
    Graph(unsigned n, std::vector<std::vector<int>> &matrix);
    ~Graph();
    void print_matrix();
    void close_matrix();
    void open_matrix();
    void non_oriented();
    Graph power(int pow);
    void clique_search();
    void greedy_color();
    void edge_coloring();
};


#endif //CLION_GRAPH_H
