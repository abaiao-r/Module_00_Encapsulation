/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:57:45 by andrefranci       #+#    #+#             */
/*   Updated: 2024/07/13 00:00:37 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Vector2.hpp"

// Default constructor
Vector2::Vector2(float xCoord, float yCoord) : x(xCoord), y(yCoord)
{
}

// Destructor
Vector2::~Vector2(void)
{
}

// Copy constructor
Vector2::Vector2(const Vector2 &other)
{
    *this = other;
}

// Assignment operator
Vector2 &Vector2::operator=(const Vector2 &other)
{
    if (this != &other)
    {
        this->x = other.x;
        this->y = other.y;
    }
    return (*this);
}

float Vector2::getX(void) const
{
    return (this->x);
}

float Vector2::getY(void) const
{
    return (this->y);
}

void Vector2::setX(float xCoord)
{
    this->x = xCoord;
}

void Vector2::setY(float yCoord)
{
    this->y = yCoord;
}
