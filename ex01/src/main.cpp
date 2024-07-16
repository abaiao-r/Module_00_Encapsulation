/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:39:57 by andrefranci       #+#    #+#             */
/*   Updated: 2024/07/15 18:02:53 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/Graph.hpp"

/**
 * @brief The main function of the program.
 * 
 * This function is the entry point of the program.
 * Usage: ./[Name of the program] [filename]
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return int The exit status of the program.
 */
int main(int argc, char **argv)
{

    if (argc != 2)
    {
        std::cerr << "Usage: ./ex01 [filename]" << std::endl;
        return (1);
    }

    Graph graph;

    try
    {
        graph.readPointsFromFile(argv[1]);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << "\n";
        return(1);
    }

    std::cout << "\n\nGraph with points('o'):\n" << std::endl;
    graph.displayPoints();

    std::cout << "\n\nGraph with lines('x'):\n" << std::endl;
    graph.displayLines();
    
    std::cout << "\n\nGraph with points('o') and lines('x'):\n" << std::endl;
    graph.displayLinesWithPoints();

    // Graph graph(10, 10);
    std::cout << "\n\n Test with parametric construtor \n" << std::endl;
    Graph graph2(5, 5);

    graph2.addPoint(0, 0);
    graph2.addPoint(2, 2);
    graph2.addPoint(4, 2);
    graph2.addPoint(2, 4);
    graph2.addLinesFromPoints();

    std::cout << "\n\nGraph with points('o'):\n" << std::endl;
    graph2.displayPoints();

    std::cout << "\n\nGraph with lines('x'):\n" << std::endl;
    graph2.displayLines();
    
    std::cout << "\n\nGraph with points('o') and lines('x'):\n" << std::endl;
    graph2.displayLinesWithPoints();
    
    return (0);
}
