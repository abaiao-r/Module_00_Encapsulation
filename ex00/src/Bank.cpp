/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:58:50 by guest             #+#    #+#             */
/*   Updated: 2024/07/09 13:09:33 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bank.hpp"
#include "../includes/colours.hpp"

// Default constructor
Bank::Bank(void) : liquidity(0)
{
}

// Copy constructor
Bank::Bank(const Bank &src) : liquidity(src.liquidity)
{
    for (std::vector<Account *>::const_iterator it = src.clientAccounts.begin(); it != src.clientAccounts.end(); it++)
    {
        this->clientAccounts.push_back(new Account(**it));
    }
}

// Copy assignment operator
Bank &Bank::operator=(const Bank &src)
{
    if (this != &src)
    {
        this->liquidity = src.liquidity;
        for (std::vector<Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++)
        {
            delete *it;
        }
        this->clientAccounts.clear();
        for (std::vector<Account *>::const_iterator it = src.clientAccounts.begin(); it != src.clientAccounts.end(); it++)
        {
            this->clientAccounts.push_back(new Account(**it));
        }
    }
    return (*this);
}

// Destructor
Bank::~Bank(void)
{
    for (std::vector<Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++)
    {
        delete *it;
    }
    this->clientAccounts.clear(); // Clear the vector
}

int Bank::getLiquidity(void) const
{
    return (this->liquidity);
}

void Bank::createAccount(void)
{
    try
    {
        Account *newAccount = new Account();
        this->clientAccounts.push_back(newAccount);
        std::cout << GREEN << "Account " << newAccount->getId() << " created" << RESET << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << RED << "Error: Account creation failed" << RESET << std::endl;
    }
}


void Bank::deleteAccount(int id)
{
    for (std::vector<Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++)
    {
        if ((*it)->getId() == id)
        {
            std::cout << YELLOW << "Account " << id << " deleted" << RESET << std::endl;
            delete *it;
            this->clientAccounts.erase(it);
            return;
        }
    }
    std::cout << RED << "Account " << id << " not found" << RESET << std::endl;
}

void Bank::modifyAccount(int id, int amount)
{
    for (std::vector<Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++)
    {
        if ((*it)->getId() == id)
        {

            if (amount < 0)
            {
                try
                {
                    (*it)->deductValue(amount);
                }
                catch (std::exception &e)
                {
                    // write a error message to the standard error output stream
                    std::cerr << RED << "Error: Account " << id << " value overflow or underflow" << RESET << std::endl;
                    return;
                }
                std::cout << GREEN << "Account " << id << " modified with " << amount << RESET << std::endl;
                return;
            } else if (amount >= 0)
            {
                int bankFee = amount * 0.05;
                int netAmount = amount - bankFee;
                try
                {
                    (*it)->addValue(netAmount);
                }
                catch (std::exception &e)
                {
                    // write a error message to the standard error output stream
                    std::cerr << RED << "Error: Account " << id << " value overflow or underflow" << RESET << std::endl;
                    return;
                }
                this->liquidity += bankFee;
                std::cout << GREEN << "Account " << id << " modified with " << amount << ". The net amount is " << netAmount << " and the bank fee is " << bankFee << RESET << std::endl;
                return;
            }
        }
    }
    std::cout << RED << "Account " << id << " not found" << RESET << std::endl;
}

void Bank::giveLoan(int id, int amount)
{
    std::cout << YELLOW << "Loan of " << amount << " requested by account " << id << RESET << std::endl;
    std::cout << YELLOW << "Bank liquidity : " << this->liquidity << RESET << std::endl;
    if (liquidity < amount)
    {
        std::cout << RED << "Bank has insufficient liquidity" << RESET << std::endl;
        return;
    } else if (amount < 0)
    {
        std::cout << RED << "Error: Cannot grant a negative loan" << RESET << std::endl;
        return;
    } else if (amount == 0)
    {
        std::cout << RED << "Error: Cannot grant a loan of 0" << RESET << std::endl;
        return;
    } else if (amount > INT_MAX)
    {
        std::cout << RED << "Error: Cannot grant a loan greater than INT_MAX" << RESET << std::endl;
        return;
    }

    for (std::vector<Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++)
    {
        if ((*it)->getId() == id)
        {
            (*it)->addValue(amount);
            this->liquidity -= amount;
            std::cout << GREEN << "Loan of " << amount << " granted to account " << id << RESET << std::endl;
            return;
        }
    }
    std::cout << RED << "Account " << id << " not found" << RESET << std::endl;
}

const std::vector<const Account *> &Bank::getAccounts(void) const
{
    // reinterpret_cast is used to convert a pointer to any object type into a pointer to any other type
    // in this case we are converting a pointer to a vector of Account pointers into a pointer to a vector of const Account pointers
    // this is done to prevent the vector from being modified by the caller
    // ex: if the caller tries to push_back a new Account into the vector, the compiler will throw an error. 
    // ex: bank.getAccounts().push_back(new Account());
    // ex: if the caller tries to modify the value of an Account in the vector, the compiler will throw an error 
    // ex: bank.getAccounts().at(0)->addValue(100);
    return reinterpret_cast<const std::vector<const Account *> &>(this->clientAccounts);
}

void Bank::displayAccounts(void) const
{
    for (std::vector<Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++)
    {
        std::cout << **it << std::endl;
    }
}

std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank)
{
    p_os << "Bank informations : " << std::endl;
    p_os << "Liquidity : " << p_bank.getLiquidity() << std::endl;
    p_os << "Accounts : " << std::endl;
    p_bank.displayAccounts();
    return (p_os);
}

