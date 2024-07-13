/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:42:41 by andrefranci       #+#    #+#             */
/*   Updated: 2024/07/13 10:38:08 by andrefranci      ###   ########.fr       */
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
#include "Vector2.hpp"

class Graph
{
    private:
        Vector2 size;
        std::vector<Vector2> points;
        std::vector<std::pair<Vector2, Vector2> > lines;

        void validateFile(const std::string& filename);
        void addValidPointsFromFile(const std::string& filename);
        bool validatePointFormat(const std::string& line, int lineNum, float& x, float& y) const;
        void addLine(float x1, float y1, float x2, float y2);

    public:
        Graph(float width, float height);
        ~Graph(void);
        Graph(const Graph &other);
        Graph &operator=(const Graph &other);

        void addPoint(float x, float y);
        void addLinesFromPoints();
        void displayPoints(void) const;
        void displayLines(void) const;
        void displayLinesWithPoints(void) const;
        void readPointsFromFile(const std::string& filename);
        //void drawToPNG(const std::string& filename) const;
};

#endif