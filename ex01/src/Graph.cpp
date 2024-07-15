/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:42:52 by andrefranci       #+#    #+#             */
/*   Updated: 2024/07/15 18:54:19 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Graph.hpp"

// Default constructor
Graph::Graph(void) : size(0, 0)
{
}

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

void Graph::setSize(void)
{
    // Check max value of vector2 points and set size + OFFSET
    const float OFFSET = 5.0f;
    float maxX = 0;
    float maxY = 0;

    for (std::vector<Vector2>::const_iterator it = points.begin(); it != points.end(); ++it)
    {
        if (it->getX() > maxX)
            maxX = it->getX();
        if (it->getY() > maxY)
            maxY = it->getY();
    }

    size = Vector2(maxX + OFFSET, maxY + OFFSET);
}

void Graph::addPoint(float x, float y)
{
    if (size.getX() != 0 && size.getY() != 0)
    {
        if (x >= 0 && y >= 0 && x <= size.getX() && y <= size.getY())
        {
            this->points.push_back(Vector2(x, y));
        }
        else
        {
            std::cerr << "Error: Point out of bounds" << std::endl;
        }
    }
    else if (x >= 0 && y >= 0)
    {
        this->points.push_back(Vector2(x, y));
    }
    else
    {
        std::cerr << "Error: Point out of bounds" << std::endl;
    }
    /* if (x >= 0 && y >= 0)
    {
        this->points.push_back(Vector2(x, y));
    }
    else
    {
        std::cerr << "Error: Point out of bounds" << std::endl;
    } */
}

void Graph::addLine(float x1, float y1, float x2, float y2)
{
    lines.push_back(std::make_pair(Vector2(x1, y1), Vector2(x2, y2)));
}

bool Graph::compareX(const Vector2& a, const Vector2& b)
{
    return a.getX() < b.getX();
}

void Graph::sortPointsByX()
{
    std::sort(points.begin(), points.end(), compareX);
}

void Graph::addLinesFromPoints() {
    lines.clear(); // Clear existing lines

    // sort points by x coordinate c++98 no lambda
    sortPointsByX();

    // Connect each point to the next one in the sequence
    for (size_t i = 1; i < points.size(); ++i) {
        addLine(points[i-1].getX(), points[i-1].getY(), points[i].getX(), points[i].getY());
    }
}

void Graph::displayLinesWithPoints()
{
    // check if there is size
    if (this->size.getX() == 0 && this->size.getY() == 0)
        setSize();
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


void Graph::displayPoints(void)
{
    // check if there is size
    if (this->size.getX() == 0 && this->size.getY() == 0)
        setSize();
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

void Graph::displayLines()
{
    // check if there is size
    if (this->size.getX() == 0 && this->size.getY() == 0)
        setSize();
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

    // Validate the file type (.txt or .csv)
    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    if (extension != "txt" && extension != "csv") {
        throw std::runtime_error("Invalid file type: " + extension);
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
    if (!(iss >> x >> separator >> y) || !(separator == '/' || separator == ',' || separator == '\\' || separator == '|' || std::isspace(separator)))
    {
        std::cerr << "Invalid format in line " << lineNum << ": " << line << "\n";
        return false;
    }

    // Check for trailing characters
    std::string trailing;
    if (iss >> trailing)
    {
        std::cerr << "Invalid format in line " << lineNum << ": " << line << "\n";
        return false;
    }

    return true;
}

/* // CRC32 calculation
unsigned int Graph::crc32(unsigned char* buf, unsigned int len) const {
    static const unsigned int crcTable[256] = {
        0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
        0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
        0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
        0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
        0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
        0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
        0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
        0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
        0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
        0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
        0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
        0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
        0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
        0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
        0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
        0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
        0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
        0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
        0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
        0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
        0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
        0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
        0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
        0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
        0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
        0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
        0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
        0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
        0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
        0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
        0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
        0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
        0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
        0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
        0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
        0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
        0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
        0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
        0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
        0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
        0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
        0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
        0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
    };

    unsigned int crc = 0xffffffff;

    for (unsigned int i = 0; i < len; ++i) {
        unsigned char index = (crc ^ buf[i]) & 0xff;
        crc = (crc >> 8) ^ crcTable[index];
    }

    return crc ^ 0xffffffff;
}

void Graph::writeChunk(std::ofstream& file, const char* type, const unsigned char* data, unsigned int length) const {
    unsigned char lengthBytes[4];
    lengthBytes[0] = (length >> 24) & 0xff;
    lengthBytes[1] = (length >> 16) & 0xff;
    lengthBytes[2] = (length >> 8) & 0xff;
    lengthBytes[3] = length & 0xff;

    file.write(reinterpret_cast<const char*>(lengthBytes), 4);
    file.write(type, 4);

    if (data != 0 && length > 0) {
        file.write(reinterpret_cast<const char*>(data), length);
    }

    unsigned char crcData[4 + length];
    for (unsigned int i = 0; i < 4; ++i) {
        crcData[i] = type[i];
    }
    if (data != 0 && length > 0) {
        for (unsigned int i = 0; i < length; ++i) {
            crcData[4 + i] = data[i];
        }
    }

    unsigned int crc = crc32(crcData, 4 + length);
    unsigned char crcBytes[4];
    crcBytes[0] = (crc >> 24) & 0xff;
    crcBytes[1] = (crc >> 16) & 0xff;
    crcBytes[2] = (crc >> 8) & 0xff;
    crcBytes[3] = crc & 0xff;

    file.write(reinterpret_cast<const char*>(crcBytes), 4);
}

void Graph::writePNGHeader(std::ofstream& file) const {
    static const unsigned char pngHeader[8] = {
        0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a
    };

    file.write(reinterpret_cast<const char*>(pngHeader), 8);
}

void Graph::writePNGData(std::ofstream& file, const std::vector<std::vector<unsigned char> >& image) const {
    const int width = static_cast<int>(size.getX());
    const int height = static_cast<int>(size.getY());
    (void)image;

    // Prepare the image data
    std::vector<std::vector<unsigned char> > imageData(height + 1, std::vector<unsigned char>(width + 1, 255)); // Initialize with white

    // Draw lines on the image
    for (std::vector<std::pair<Vector2, Vector2> >::const_iterator it = lines.begin(); it != lines.end(); ++it) {
        int x1 = static_cast<int>(it->first.getX());
        int y1 = static_cast<int>(it->first.getY());
        int x2 = static_cast<int>(it->second.getX());
        int y2 = static_cast<int>(it->second.getY());

        // Bresenham's line algorithm to draw lines between points
        int dx = std::abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -std::abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx + dy, e2;

        for (;;) {
            if (y1 >= 0 && y1 <= height && x1 >= 0 && x1 <= width) {
                imageData[y1][x1] = 0; // Draw the line
            }

            if (x1 == x2 && y1 == y2) break;

            e2 = 2 * err;
            if (e2 >= dy) {
                err += dy;
                x1 += sx;
            }
            if (e2 <= dx) {
                err += dx;
                y1 += sy;
            }
        }
    }

    // Place points on the image
    for (std::vector<Vector2>::const_iterator it = points.begin(); it != points.end(); ++it) {
        int x = static_cast<int>(it->getX());
        int y = static_cast<int>(it->getY());
        if (y >= 0 && y <= height && x >= 0 && x <= width) {
            imageData[y][x] = 0; // Draw the point
        }
    }

    // Convert imageData to flat vector for PNG creation
    std::vector<unsigned char> flatImage;
    for (int y = height; y >= 0; --y) {
        for (int x = 0; x <= width; ++x) {
            flatImage.push_back(imageData[y][x]);
            flatImage.push_back(imageData[y][x]);
            flatImage.push_back(imageData[y][x]);
            flatImage.push_back(255); // Alpha channel, fully opaque
        }
    }

    // IHDR Chunk
    unsigned char ihdrData[13];
    ihdrData[0] = (width >> 24) & 0xff;
    ihdrData[1] = (width >> 16) & 0xff;
    ihdrData[2] = (width >> 8) & 0xff;
    ihdrData[3] = width & 0xff;
    ihdrData[4] = (height >> 24) & 0xff;
    ihdrData[5] = (height >> 16) & 0xff;
    ihdrData[6] = (height >> 8) & 0xff;
    ihdrData[7] = height & 0xff;
    ihdrData[8] = 8;  // Bit depth
    ihdrData[9] = 2;  // Color type (Truecolor)
    ihdrData[10] = 0; // Compression method
    ihdrData[11] = 0; // Filter method
    ihdrData[12] = 0; // Interlace method

    writeChunk(file, "IHDR", ihdrData, 13);

    // IDAT Chunk (PNG data)
    writeChunk(file, "IDAT", &flatImage[0], flatImage.size());

    // IEND Chunk
    writeChunk(file, "IEND", NULL, 0);
}


void Graph::drawToPNG(const std::string& filename) const {
    const int width = static_cast<int>(size.getX());
    const int height = static_cast<int>(size.getY());

    std::vector<std::vector<unsigned char> > image(height, std::vector<unsigned char>(width, 255));

    for (std::vector<Vector2>::const_iterator it = points.begin(); it != points.end(); ++it) {
        int x = static_cast<int>(it->getX());
        int y = static_cast<int>(it->getY());
        image[y][x] = 0;
    }

    for (std::vector<std::pair<Vector2, Vector2> >::const_iterator it = lines.begin(); it != lines.end(); ++it) {
        int x1 = static_cast<int>(it->first.getX());
        int y1 = static_cast<int>(it->first.getY());
        int x2 = static_cast<int>(it->second.getX());
        int y2 = static_cast<int>(it->second.getY());

        int dx = std::abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        int dy = -std::abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int err = dx + dy, e2;

        for (;;) {
            image[y1][x1] = 0;

            if (x1 == x2 && y1 == y2)
                break;

            e2 = 2 * err;
            if (e2 >= dy) {
                err += dy;
                x1 += sx;
            }
            if (e2 <= dx) {
                err += dx;
                y1 += sy;
            }
        }
    }

    std::ofstream file(filename.c_str(), std::ios::binary);
    if (!file.is_open())
        throw std::runtime_error("Could not open file for writing");

    writePNGHeader(file);
    writePNGData(file, image);

    file.close();
} */