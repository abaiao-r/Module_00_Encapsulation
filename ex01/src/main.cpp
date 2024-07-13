/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:39:57 by andrefranci       #+#    #+#             */
/*   Updated: 2024/07/13 11:20:41 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../includes/Graph.hpp"

int main(int argc, char **argv)
{
/*     (void)argv;
    (void)argc; */
    if (argc != 2)
    {
        std::cerr << "Usage: ./ex01 [filename]" << std::endl;
        return (1);
    }

    Graph graph(20, 70);

    try
    {
        graph.readPointsFromFile(argv[1]);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << "\n";
        return(1);
    }

    graph.addLinesFromPoints();
    std::cout << "\n\nGraph with points('o'):\n" << std::endl;
    graph.displayPoints();

    std::cout << "\n\nGraph with lines('x'):\n" << std::endl;
    graph.displayLines();
    
    std::cout << "\n\nGraph with points('o') and lines('x'):\n" << std::endl;
    graph.displayLinesWithPoints();

    // Graph graph(10, 10);
/*     Graph graph(5, 5);

    graph.addPoint(0, 0);
    graph.addPoint(2, 2);
    graph.addPoint(4, 2);
    graph.addPoint(2, 4);

    graph.displayPoints(); */
    
    return (0);
}
