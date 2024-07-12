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

#include "../includes/Bank.hpp"
#include "../includes/colours.hpp"

int Bank::Account::nextId = 0;

// how to call this constructor? Bank::Account account;
Bank::Account::Account(void) : id(nextId), value(0)
{
    if (nextId > INT_MAX)
    {
        throw std::runtime_error("Error: Account ID overflow due to too many accounts");
    }
    nextId++;
}

// Copy constructor
Bank::Account::Account(const Account &src) : id(src.id), value(src.value)
{
}

// Assignment operator
Bank::Account &Bank::Account::operator=(const Account &src)
{
    if (this != &src)
    {
        this->id = src.id;
        this->value = src.value;
    }
    return (*this);
}

Bank::Account::~Account(void)
{
    std::cout << YELLOW << "Account " << this->id << " closed" << RESET << std::endl;
}

int Bank::Account::getId(void) const
{
    return (this->id);
}

int Bank::Account::getValue(void) const
{
    return (this->value);
}

void Bank::Account::addValue(int amount)
{
    // Check for underflow
    if (amount < 0 && this->value < INT_MIN - amount)
    {
        throw std::runtime_error("Error: Account value underflow");
    }
    // Check for overflow
    if (amount > 0 && this->value > INT_MAX - amount)
    {
        throw std::overflow_error("Error: Account value overflow");
    }
    this->value += amount;
    std::cout << GREEN << "Account " << this->id << " credited with " << amount << RESET << std::endl;
}

void Bank::Account::deductValue(int amount)
{
    // check if account has sufficient funds
    if (this->value < amount)
    {
        throw std::runtime_error("Error: Account has insufficient funds");
    }
    // Check for underflow
    if (amount < 0 && this->value < INT_MIN - amount)
    {
        throw std::runtime_error("Error: Account value underflow");
    }
    // Check for overflow
    if (amount > 0 && this->value > INT_MAX - amount)
    {
        throw std::runtime_error("Error: Account value overflow");
    }
    this->value -= amount;
    std::cout << RED << "Account " << this->id << " debited with " << amount << RESET << std::endl;
}


