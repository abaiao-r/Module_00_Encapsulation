/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:58:55 by guest             #+#    #+#             */
/*   Updated: 2024/07/08 14:08:42 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Account.hpp"
#include "../includes/colours.hpp"

int Account::nextId = 0;

Account::Account(void) : id(nextId), value(0)
{
    if (nextId > INT_MAX)
    {
        std::cerr << RED << "Error: Account ID overflow" << RESET << std::endl;
        throw std::exception();
    }
    nextId++;
}

// Copy constructor
Account::Account(const Account &src) : id(src.id), value(src.value)
{
}

// Assignment operator
Account &Account::operator=(const Account &src)
{
    if (this != &src)
    {
        this->id = src.id;
        this->value = src.value;
    }
    return (*this);
}

Account::~Account(void)
{
    std::cout << YELLOW << "Account " << this->id << " closed" << RESET << std::endl;
}

int Account::getId(void) const
{
    return (this->id);
}

int Account::getValue(void) const
{
    return (this->value);
}

void Account::addValue(int amount)
{
    if (amount < 0)
    {
        std::cerr << RED << "Error: Cannot credit account " << this->id << " with a negative amount" << RESET << std::endl;
        return;
    }
    try
    {
        if (this->value + amount > INT_MAX)
        {
            throw std::exception();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << RED << "Error: Account " << this->id << " value overflow" << RESET << std::endl;
        return;
    }
    this->value += amount;
    std::cout << GREEN << "Account " << this->id << " credited with " << amount << RESET << std::endl;
}

void Account::deductValue(int amount)
{
    if (amount > 0)
    {
        std::cerr << RED << "Error: Cannot debit account " << this->id << " with a positive amount" << RESET << std::endl;
        return;
    }
    try
    {
        if (this->value - amount < 0)
        {
            throw std::exception();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << RED << "Error: Account " << this->id << " has insufficient funds" << RESET << std::endl;
        return;
    }
    this->value -= amount;
    std::cout << RED << "Account " << this->id << " debited with " << amount << RESET << std::endl;
}

std::ostream &operator<<(std::ostream &p_os, const Account &p_account)
{
    p_os << "Account " << p_account.getId() << " has " << p_account.getValue() << " units";
    return (p_os);
}

