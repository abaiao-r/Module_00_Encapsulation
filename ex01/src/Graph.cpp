/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:42:52 by andrefranci       #+#    #+#             */
/*   Updated: 2024/07/13 11:47:33 by andrefranci      ###   ########.fr       */
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

void Graph::displayLinesWithPoints() const
{
    // Create a grid with size y+1 by x+1 initialized to '.' if x >= 10 && x < 100 print " " before x
     
    std::vector<std::vector<char> > grid(size.getY() + 1, std::vector<char>(size.getX() + 1, '.'));

    // Draw lines on the grid
    for (std::vector<std::pair<Vector2, Vector2> >::const_iterator it = lines.begin(); it != lines.end(); ++it)
    {
        int x1 = static_cast<int>(it->first.getX());
        int y1 = static_cast<int>(it->first.getY());
        int x2 = static_cast<int>(it->second.getX());
        int y2 = static_cast<int>(it->second.getY());

        // Bresenham's line algorithm to draw lines between points
        int dx = std::abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -std::abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx + dy, e2; // error value e_xy

        for (;;)
        {
            if (grid[y1][x1] != 'o') // Prevent overwriting points
                grid[y1][x1] = 'X'; // Draw the line

            if (x1 == x2 && y1 == y2)
                break;

            e2 = 2 * err;
            if (e2 >= dy)
            {
                err += dy;
                x1 += sx;
            }
            if (e2 <= dx)
            {
                err += dx;
                y1 += sy;
            }
        }
    }

    // Place points on the grid
    for (std::vector<Vector2>::const_iterator it = points.begin(); it != points.end(); ++it)
    {
        int x = static_cast<int>(it->getX());
        int y = static_cast<int>(it->getY());
        grid[y][x] = 'o';
    }

    // Print the grid
    for (int y = size.getY(); y >= 0; --y)
    {
        if (y < 10)
            std::cout << " ";
        std::cout << y << " ";
        for (int x = 0; x <= size.getX(); ++x)
        {
            std::cout << grid[y][x] << "  ";
        }
        std::cout << std::endl;
    }

    // Print the x-axis indices
    std::cout << "   ";
    for (int x = 0; x <= size.getX(); ++x)
    {
        if (x > 0 && x < 10)
            std::cout << " ";
        std::cout << x << " ";
    }
    std::cout << std::endl;
}


void Graph::displayPoints(void) const
{
    for (int y = static_cast<int>(this->size.getY()); y >= 0; y--)
    {
        if (y < 10)
            std::cout << " ";
        std::cout << y << " ";
        for (int x = 0; x <= static_cast<int>(this->size.getX()); x++)
        {
            if (x > 0 )
                std::cout << " ";
            bool found = false;
            for (std::vector<Vector2>::const_iterator it = this->points.begin(); it != this->points.end(); it++)
            {
                if (static_cast<int>(it->getX()) == x && static_cast<int>(it->getY()) == y)
                {
                    std::cout << "o ";
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

    std::cout << "   ";
    for (int x = 0; x <= static_cast<int>(size.getX()); ++x) {
         if (x > 0 && x < 10)
            std::cout << " ";
        std::cout << x << " ";
    }
    std::cout << "\n";
}

void Graph::displayLines() const
{
    // Create a grid with size y+1 by x+1 initialized to '.'
    std::vector<std::vector<char> > grid(size.getY() + 1, std::vector<char>(size.getX() + 1, '.'));

    // Place points on the grid
    for (std::vector<Vector2>::const_iterator it = points.begin(); it != points.end(); ++it)
    {
        int x = static_cast<int>(it->getX());
        int y = static_cast<int>(it->getY());
        grid[y][x] = 'X';
    }

    // Draw lines on the grid
    for (std::vector<std::pair<Vector2, Vector2> >::const_iterator it = lines.begin(); it != lines.end(); ++it)
    {
        int x1 = static_cast<int>(it->first.getX());
        int y1 = static_cast<int>(it->first.getY());
        int x2 = static_cast<int>(it->second.getX());
        int y2 = static_cast<int>(it->second.getY());

        // Bresenham's line algorithm to draw lines between points
        int dx = std::abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = std::abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;

        for (;;)
        {
            grid[y1][x1] = 'X'; // Draw the line

            if (x1 == x2 && y1 == y2)
                break;

            e2 = err;
            if (e2 > -dx)
            {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dy)
            {
                err += dx;
                y1 += sy;
            }
        }
    }

    // Print the grid
    for (int y = size.getY(); y >= 0; --y)
    {
        if (y < 10)
            std::cout << " ";
        std::cout << y << " ";
        for (int x = 0; x <= size.getX(); ++x)
        {
            std::cout << grid[y][x] << "  ";
        }
        std::cout << std::endl;
    }

    // Print the x-axis indices
    std::cout << "   ";
    for (int x = 0; x <= size.getX(); ++x)
    {
         if (x > 0 && x < 10)
            std::cout << " ";
        std::cout << x << " ";
    }
    std::cout << std::endl;
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

