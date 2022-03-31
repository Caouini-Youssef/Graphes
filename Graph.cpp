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
            if(this->matrix[i][j] == 1)
                this->matrix[j][i] = 1;
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