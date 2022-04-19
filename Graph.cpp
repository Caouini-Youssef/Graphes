//
// Created by torakun on 16/03/2022.
//

#include "Graph.h"
#define INF INT16_MAX

Graph::Graph(unsigned n, int p)
{
    this->matrix = std::vector<std::vector<int>>(n, std::vector<int>(n));
    this->n = n;
    for(unsigned i = 0; i<n; ++i)
    {
        for(unsigned j = 0; j<n; ++j)
        {
            if(rand()%100 < p)
            {
                matrix[i][j] = 1;
            }
            else
            {
                matrix[i][j] = 0;
            }
        }
    }
}

Graph::Graph(unsigned n, std::vector<std::vector<int>> &matrix)
{
    this->n = n;
    this->matrix = std::vector<std::vector<int>>(n, std::vector<int>(n));
    for(unsigned i = 0; i < n; ++i)
    {
        for(unsigned j = 0; j < n; ++j)
        {
            this->matrix[i][j] = matrix[i][j];
        }
    }
}

Graph::Graph(unsigned int n, unsigned weight)
{
    this->n = n;
    this->matrix = std::vector<std::vector<int>>(n, std::vector<int>(n));
    for(unsigned i = 0; i < n; ++i)
    {
        for(unsigned j = 0; j < n; ++j)
        {
            this->matrix[i][j] = (int)weight;
        }
    }
}

Graph::~Graph(){}


void Graph::print_matrix()
{
    for(unsigned i = 0; i<this->n; ++i)
    {
        for(unsigned j = 0; j<this->n; ++j)
        {
            if (matrix [i][j] == INF)
                std::cout << " |" << "-";
            else
                std::cout << " |" << matrix[i][j];
        }
        std::cout << " |" << std::endl;
    }
}



void Graph::close_matrix()
{
    for(unsigned i = 0; i <this->n; ++i)
    {
        this->matrix[i][i] = 1;
    }
}

void Graph::open_matrix()
{
    for(unsigned i = 0; i <this->n; ++i)
    {
        this->matrix[i][i] = 0;
    }
}

void Graph::non_oriented()
{
    for(unsigned i = 0; i < this->n; ++i)
    {
        for(unsigned j = 0; j < this->n; ++j)
        {
            if(this->matrix[i][j] != 0 && this->matrix[i][j] != INF)
                this->matrix[j][i] = this->matrix[i][j];
        }
    }
}

//function to get the max between two numbers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

Graph Graph::power(int pow) {
    std::vector<std::vector<int>> result = std::vector<std::vector<int>>(this->n, std::vector<int>(this->n));
    result = this->matrix;
     for (unsigned l = 0; l < pow; ++l) {
        for (unsigned i = 0; i < this->n; ++i) {
            for (unsigned j = 0; j < this->n; ++j) {
                for (unsigned k = 0; k < this->n; ++k) {
                    result[i][j] =max(result[i][j], result[i][k] * this->matrix[k][j]);
                }
            }
        }
    }
    return Graph(this->n, result);
}

void Graph::clique_search()
{
    for(unsigned i = 0; i < this->n - 4; ++i)
    {
        for(unsigned j = i+1; j < this->n - 3; ++j)
        {
            if(this->matrix[i][j] != INF && this->matrix[i][j] != 0)
            {
                for(unsigned k = j+1; k < this->n -2; ++k)
                {
                    if((this->matrix[i][k] != INF && this->matrix[i][k] != 0) &&
                       (this->matrix[j][k] != INF && this->matrix[j][k] != 0))
                    {
                        for(unsigned l = k+1; l < this->n-1; ++l)
                        {
                            if((this->matrix[i][l] != INF && this->matrix[i][l] != 0) &&
                               (this->matrix[k][l] != INF && this->matrix[k][l] != 0) &&
                               (this->matrix[j][l] != INF && this->matrix[j][l] != 0))
                            {
                                for(unsigned h = l+1; h < this->n; ++h)
                                {
                                    if((this->matrix[i][h] != INF && this->matrix[i][h] != 0) &&
                                       (this->matrix[j][h] != INF && this->matrix[j][h] != 0) &&
                                       (this->matrix[k][h] != INF && this->matrix[k][h] != 0)&&
                                       (this->matrix[l][h] != INF && this->matrix[l][h] != 0))
                                    {
                                        std::cout << "Il y a une clique 5 tel que : "
                                        << i << " -> "
                                        << j << " -> "
                                        << k << " -> "
                                        << l << " -> "
                                        << h << std::endl;
                                        return;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    std::cout << "Il n'y a pas de clique 5" << std::endl;
}


void Graph::greedy_color() {
    std::vector<int> color(this->n,0);
    unsigned c = 0, j = 0;
    while(j < this->n)
    {
        if(color[j] == 0)
        {
            color[j] = ++c;
            for(unsigned i = 0; i < this->n; ++i)
            {
                if(this->matrix[j][i] != INF && this->matrix[j][i] != 0 && color[i] == 0)
                {
                    color[i] = c;
                }
            }
        }
        ++j;
    }
    for(unsigned i = 0; i < this->n; ++i)
    {
        std::cout << "Le sommet " << i << " est de couleur " << color[i] << std::endl;
    }
}

void Graph::edge_coloring() {
    unsigned k,c;
    std::vector<std::vector<int>> colors(this->n, std::vector<int>(this->n, 0));
    for(unsigned i = 0; i < this->n; ++i)
    {
        for(unsigned j = i; j < this->n; ++j)
        {
            if(this->matrix[i][j] != INF && this->matrix[i][j] != 0)
            {
                c = 0;
                k = 0;
                while(k < this->n)
                {
                    if((colors[i][k] == c) || (colors[j][k] == c))
                    {
                        ++c;
                        k = 0;
                    }
                    else
                    {
                        ++k;
                    }
                }
                colors[i][j] = colors[j][i] = c;
            }
        }
    }
    for(unsigned i = 0; i < this->n; ++i)
    {
        for(unsigned j = i; j < this->n; ++j)
        {
            if (colors[i][j] != 0)
            {
                std::cout << "L'arête " << i << " -> " << j <<" est de couleur " << colors[i][j] << std::endl;
            }
        }
    }
}
