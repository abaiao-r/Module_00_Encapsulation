/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:58:50 by guest             #+#    #+#             */
/*   Updated: 2024/07/08 14:09:56 by guest            ###   ########.fr       */
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
    Account *newAccount = new Account();
    this->clientAccounts.push_back(newAccount);
    std::cout << GREEN << "Account " << newAccount->getId() << " created" << RESET << std::endl;
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
            int bankFee = amount * 0.05;
            int netAmount = amount - bankFee;
            (*it)->addValue(netAmount);
            this->liquidity += bankFee;
            break;
        }
    }
}

void Bank::giveLoan(int id, int amount)
{
    if (liquidity < amount)
    {
        std::cout << RED << "Bank has insufficient liquidity" << RESET << std::endl;
        return;
    }

    for (std::vector<Account *>::iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++)
    {
        if ((*it)->getId() == id)
        {
            (*it)->addValue(amount);
            this->liquidity -= amount;
            break;
        }
    }

    std::cout << GREEN << "Loan of " << amount << " granted to account " << id << RESET << std::endl;
}

std::vector<Account *> &Bank::getAccounts(void)
{
    return (this->clientAccounts);
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

