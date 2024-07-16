/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:42:41 by andrefranci       #+#    #+#             */
/*   Updated: 2024/07/15 18:55:06 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_HPP
# define GRAPH_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib> // for abs
#include <cctype>  // for std::isspace
#include <string>
#include <algorithm>
#include "Vector2.hpp"

/**
 * @class Graph
 * @brief Represents a graph with points and lines.
 * 
 * The Graph class provides functionality to create and manipulate a graph.
 * It allows adding points, lines, and reading points from a file.
 * The graph can be displayed with or without points and lines.
 */
class Graph
{
    private:
        Vector2 size;
        std::vector<Vector2> points;
        std::vector<std::pair<Vector2, Vector2> > lines;

        void validateFile(const std::string &filename);
        void addValidPointsFromFile(const std::string &filename);
        bool validatePointFormat(const std::string &line, int lineNum, float &x, float &y) const;
        void addLine(float x1, float y1, float x2, float y2);
        // static because it doesn't depend on the object.
        static bool compareX(const Vector2 &a, const Vector2 &b);
        void sortPointsByX(void);
        void setSize(void);

    public:
        Graph(void);
        Graph(float width, float height);
        ~Graph(void);
        Graph(const Graph &other);
        Graph &operator=(const Graph &other);

        void addPoint(float x, float y);
        void addLinesFromPoints(void);
        void displayPoints(void) const;
        void displayLines(void) const;
        void displayLinesWithPoints(void) const;
        void readPointsFromFile(const std::string &filename);
};

#endif