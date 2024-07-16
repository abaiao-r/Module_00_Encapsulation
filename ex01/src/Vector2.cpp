/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:57:45 by andrefranci       #+#    #+#             */
/*   Updated: 2024/07/15 15:41:23 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Vector2.hpp"

/**
 * @brief Constructs a new Vector2 object with the specified x and y coordinates.
 *
 * @param xCoord The x-coordinate of the vector.
 * @param yCoord The y-coordinate of the vector.
 */
Vector2::Vector2(float xCoord, float yCoord) : x(xCoord), y(yCoord)
{
}


/**
 * @brief Destructor for the Vector2 class.
 * 
 * This destructor is responsible for cleaning up any resources
 * allocated by the Vector2 class.
 */
Vector2::~Vector2(void)
{
}


/**
 * @brief Constructs a new Vector2 object by copying another Vector2 object.
 *
 * @param other The Vector2 object to be copied.
 */
Vector2::Vector2(const Vector2 &other)
{
    *this = other;
}

// Assignment operator
/**
 * @brief Assignment operator overload for Vector2 class.
 * 
 * This function assigns the values of another Vector2 object to the current object.
 * 
 * @param other The Vector2 object to be assigned.
 * @return A reference to the current Vector2 object after assignment.
 */
Vector2 &Vector2::operator=(const Vector2 &other)
{
    if (this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    return (*this);
}

/**
 * @brief Get the value of the x-coordinate.
 * 
 * @return const float& The value of the x-coordinate.
 */
const float &Vector2::getX(void) const
{
    return (this->x);
}

/**
 * @brief Get the value of the y-coordinate.
 * 
 * @return const float& The value of the y-coordinate.
 */
const float &Vector2::getY(void) const
{
    return (this->y);
}

/**
 * @brief Sets the x-coordinate of the Vector2 object.
 * 
 * @param xCoord The new value for the x-coordinate.
 */
void Vector2::setX(float xCoord)
{
    this->x = xCoord;
}

/**
 * @brief Sets the y-coordinate of the Vector2 object.
 * 
 * @param yCoord The new y-coordinate value.
 */
void Vector2::setY(float yCoord)
{
    this->y = yCoord;
}
