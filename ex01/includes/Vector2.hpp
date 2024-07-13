/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:53:21 by andrefranci       #+#    #+#             */
/*   Updated: 2024/07/12 23:58:00 by andrefranci      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <iostream>
#include <vector>

class Vector2
{
    private:
        float x;
        float y;

    public:
        Vector2(float x = 0, float y = 0);
        ~Vector2(void);
        Vector2(const Vector2 &other);
        Vector2 &operator=(const Vector2 &other);

        float getX(void) const;
        float getY(void) const;

        void setX(float x);
        void setY(float y);


};

#endif
