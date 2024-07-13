/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:42:52 by andrefranci       #+#    #+#             */
/*   Updated: 2024/07/13 01:37:42 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Graph.hpp"

// Parameterized constructor
Graph::Graph(float width, float height) : size(width, height)
{
}

// Destructor
Graph::~Graph(void)
{
}

// Copy constructor
Graph::Graph(const Graph &other)
{
    *this = other;
}

// Assignment operator
Graph &Graph::operator=(const Graph &other)
{
    if (this != &other)
    {
        this->size = other.size;
        this->points = other.points;
        this->lines = other.lines;
    }
    return (*this);
}

void Graph::addPoint(float x, float y)
{
    if (x >= 0 && x <= this->size.getX() && y >= 0 && y <= this->size.getY())
    {
        this->points.push_back(Vector2(x, y));
    }
    else
    {
        std::cerr << "Error: Point out of bounds" << std::endl;
    }
}

void Graph::addLine(float x1, float y1, float x2, float y2)
{
    lines.push_back(std::make_pair(Vector2(x1, y1), Vector2(x2, y2)));
}

void Graph::addLinesFromPoints() {
    lines.clear(); // Clear existing lines

    // Connect all points with lines
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            addLine(points[i].getX(), points[i].getY(), points[j].getX(), points[j].getY());
        }
    }
}

void Graph::displayPoints(void) const
{
    for (int y = static_cast<int>(this->size.getY()); y >= 0; y--)
    {
        std::cout << y << " ";
        for (int x = 0; x <= static_cast<int>(this->size.getX()); x++)
        {
            bool found = false;
            for (std::vector<Vector2>::const_iterator it = this->points.begin(); it != this->points.end(); it++)
            {
                if (static_cast<int>(it->getX()) == x && static_cast<int>(it->getY()) == y)
                {
                    std::cout << "X ";
                    found = true;
                    continue;
                }
            }
            if (!found)
            {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }

    std::cout << "  ";
    for (int x = 0; x <= static_cast<int>(size.getX()); ++x) {
        std::cout << x << " ";
    }
    std::cout << "\n";
}


void Graph::readPointsFromFile(const std::string& filename) {
    validateFile(filename);
    addValidPointsFromFile(filename);
}

void Graph::validateFile(const std::string& filename) {
    std::ifstream infile(filename.c_str());
    if (!infile) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string line;
    int lineNum = 0;
    bool allLinesValid = true; // Flag to track if all lines are valid

    while (std::getline(infile, line)) {
        ++lineNum;
        float x, y;
        if (!validatePointFormat(line, lineNum, x, y)) {
            allLinesValid = false;
        }
    }

    infile.close();

    if (!allLinesValid) {
        throw std::runtime_error("Invalid lines in file: " + filename);
    }
}

void Graph::addValidPointsFromFile(const std::string& filename) {
    std::ifstream infile(filename.c_str());
    if (!infile) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    std::string line;
    int lineNum = 0;

    while (std::getline(infile, line)) {
        ++lineNum;
        float x, y;
        if (validatePointFormat(line, lineNum, x, y)) {
            addPoint(x, y);
        }
    }

    infile.close();
}

bool Graph::validatePointFormat(const std::string& line, int lineNum, float& x, float& y) const {
    std::istringstream iss(line);
    char separator;

    // Try to read x and y coordinates
    if (!(iss >> x >> separator >> y) || !(separator == '/' || separator == ',' || separator == '\\' || separator == '|' || std::isspace(separator))) {
        std::cerr << "Invalid format in line " << lineNum << ": " << line << "\n";
        return false;
    }

    // Check for trailing characters
    std::string trailing;
    if (iss >> trailing) {
        std::cerr << "Invalid format in line " << lineNum << ": " << line << "\n";
        return false;
    }

    return true;
}

