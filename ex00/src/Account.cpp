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
int Bank::Account::getId(void) const
{
    return (this->id);
}

/**
 * @brief Get the value of the account.
 * 
 * @return int The value of the account.
 */
int Bank::Account::getValue(void) const
{
    return (this->value);
}

/**
 * @brief Adds a specified amount to the account value.
 *
 * This function adds the specified amount to the current value of the account.
 * It performs checks for underflow and overflow to ensure that the account value
 * remains within the valid range. If an underflow or overflow occurs, an exception
 * is thrown with an appropriate error message.
 *
 * @param amount The amount to be added to the account value.
 *
 * @throws std::runtime_error if the account value would result in an underflow.
 * @throws std::overflow_error if the account value would result in an overflow.
 */
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

/**
 * Deducts the specified amount from the account value.
 * Throws an exception if the account has insufficient funds,
 * or if the deduction would result in an underflow or overflow.
 *
 * @param amount The amount to be deducted from the account value.
 * @throws std::runtime_error if the account has insufficient funds,
 *         or if the deduction would result in an underflow or overflow.
 */
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


