/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:58:55 by guest             #+#    #+#             */
/*   Updated: 2024/09/16 20:27:34 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bank.hpp"
#include "../includes/colours.hpp"

/**
 * @brief The next available ID for a Bank Account.
 * 
 * This static member variable keeps track of the next available ID for a Bank Account.
 * Each time a new Bank Account is created, this ID is incremented by 1.
 * 
 * @note This variable is specific to the Bank::Account class and is shared among all instances of the class.
 */
int Bank::Account::nextId = 0;


/**
 * @brief Constructs a new Account object.
 * 
 * This constructor initializes the Account object with a unique ID and a value of 0.
 * If the ID exceeds the maximum limit, an exception is thrown.
 */
Bank::Account::Account(void) : id(nextId), value(0)
{
    if (nextId > INT_MAX)
    {
        throw std::runtime_error("Error: Account ID overflow due to too many accounts");
    }
    nextId++;
}


/**
 * @brief Constructs a new Account object by copying the values from another Account object.
 *
 * @param src The Account object to be copied.
 */
Bank::Account::Account(const Account &src) : id(src.id), value(src.value)
{
}


/**
 * Assignment operator overload.
 * Assigns the values of the source account to the current account.
 * 
 * @param src The source account to copy from.
 * @return A reference to the current account after assignment.
 */
Bank::Account &Bank::Account::operator=(const Account &src)
{
    if (this != &src)
    {
        this->id = src.id;
        this->value = src.value;
    }
    return (*this);
}

/**
 * @brief Destructor for the Bank::Account class.
 * 
 * This destructor is responsible for closing the account and printing a message indicating that the account has been closed.
 */
Bank::Account::~Account(void)
{
    std::cout << YELLOW << "Account " << this->id << " closed" << RESET << std::endl;
}

/**
 * @brief Get the ID of the account.
 * 
 * @return int The ID of the account.
 */
const int &Bank::Account::getId(void) const
{
    return (this->id);
}

/**
 * @brief Get the value of the account.
 * 
 * @return int The value of the account.
 */
const int &Bank::Account::getValue(void) const
{
    return (this->value);
}


