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
    for (std::map<int, Account *>::const_iterator it = src.clientAccounts.begin(); it != src.clientAccounts.end(); it++)
    {
        this->clientAccounts[it->first] = new Account(*(it->second));
    }
}

// Copy assignment operator
Bank &Bank::operator=(const Bank &src)
{
    if (this != &src)
    {
        liquidity = src.liquidity;
        // Delete existing accounts
        for (std::map<int, Account *>::iterator it = clientAccounts.begin(); it != clientAccounts.end(); ++it)
        {
            delete it->second;
        }
        clientAccounts.clear();
        // Copy new accounts
        for (std::map<int, Account *>::const_iterator it = src.clientAccounts.begin(); it != src.clientAccounts.end(); ++it)
        {
            clientAccounts[it->first] = new Account(*(it->second));
        }
    }
    return (*this);
}

// Destructor
Bank::~Bank(void)
{
    for (std::map<int, Account *>::iterator it = clientAccounts.begin(); it != clientAccounts.end(); ++it)
    {
        delete it->second;
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
        this->clientAccounts[newAccount->getId()] = newAccount;
        std::cout << GREEN << "Account " << newAccount->getId() << " created" << RESET << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << RED << "Error: Account creation failed" << RESET << std::endl;
    }
}


void Bank::deleteAccount(int id)
{
    std::map<int, Account *>::iterator it = this->clientAccounts.find(id);
    if (it != this->clientAccounts.end())
    {
        std::cout << YELLOW << "Account " << id << " deleted" << RESET << std::endl;
        delete it->second;
        this->clientAccounts.erase(it);
        return;
    }
    std::cout << RED << "Account " << id << " not found" << RESET << std::endl;
}


void Bank::deposit(int id, int amount)
{
    try {
        if (amount < 0)
        {
            throw std::invalid_argument("Error: Cannot deposit a negative amount");
        }
        else if (amount == 0)
        {
            throw std::invalid_argument("Error: Cannot deposit an amount of 0");
        }
        else if (amount > INT_MAX)
        {
            throw std::invalid_argument("Error: Cannot deposit an amount greater than INT_MAX");
        }
    }
    catch (std::exception &e)
    {
        std::cerr << YELLOW << e.what() << RESET << std::endl;
        return;
    }
    std::map<int, Account *>::iterator it = this->clientAccounts.find(id);
    if (it != this->clientAccounts.end())
    {
        int bankFee = amount * 0.05;
        int netAmount = amount - bankFee;
        try
        {
            it->second->addValue(netAmount);
        }
        catch (std::exception &e)
        {
            std::cerr << YELLOW << e.what() << RESET << std::endl;
            return;
        }
        this->liquidity += bankFee;
        
        std::cout << GREEN << "Deposit of " << amount << " made to account " << id << RESET << std::endl;
        return;    
    }
    std::cout << RED << "Account " << id << " not found" << RESET << std::endl;
}


void Bank::withdraw(int id, int amount)
{
    try {
        if (amount < 0)
        {
            throw std::invalid_argument("Error: Cannot withdraw a negative amount");
        }
        else if (amount == 0)
        {
            throw std::invalid_argument("Error: Cannot withdraw an amount of 0");
        }
        else if (amount > INT_MAX)
        {
            throw std::invalid_argument("Error: Cannot withdraw an amount greater than INT_MAX");
        }
    }
    catch (std::exception &e)
    {
        std::cerr << YELLOW << e.what() << RESET << std::endl;
        return;
    }
    std::map<int, Account *>::iterator it = this->clientAccounts.find(id);
    if (it != clientAccounts.end())
    {
        try
        {
            it->second->deductValue(amount);
        }
        catch (std::exception &e)
        {
            std::cerr << YELLOW << e.what() << RESET << std::endl;
            return;
        }
        std::cout << GREEN << "Withdrawal of " << amount << " made from account " << id << RESET << std::endl;
    }
    else
    {
        std::cout << RED << "Account " << id << " not found" << RESET << std::endl;
    }
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

    std::map<int, Account *>::iterator it = this->clientAccounts.find(id);
    if (it != this->clientAccounts.end())
    {
        it->second->addValue(amount);
        this->liquidity -= amount;
        std::cout << GREEN << "Loan of " << amount << " granted to account " << id << RESET << std::endl;
        return;
    }

    std::cout << RED << "Account " << id << " not found" << RESET << std::endl;
}

const std::map<int, const Bank::Account *> Bank::getAccounts(void) const
{
    std::map<int, const Account *> constAccounts;
    for (std::map<int, Account *>::const_iterator it = clientAccounts.begin(); it != clientAccounts.end(); ++it)
    {
        constAccounts[it->first] = it->second;
    }
    return (constAccounts);
}

const Bank::Account &Bank::operator[](int id) const
{
    //Use map's find method to locate the account by ID
    std::map<int, Account *>::const_iterator it = clientAccounts.find(id);
    
    // Check if the account was found
    if (it != clientAccounts.end())
    {
        // Return the account object
        return *(it->second);
    }
    
    // If account with the given ID is not found, throw an exception
    throw std::out_of_range("Account ID not found");
}


void Bank::displayAccounts(void) const
{
    std::map<int, Account *>::const_iterator it;
    for (it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++)
    {
        std::cout << "Account " << it->first << " : " << it->second->getValue() << std::endl;
    }
}

// call this: std::cout << bank << std::endl;
std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank)
{
    p_os << "Bank informations : " << std::endl;
    p_os << "Liquidity : " << p_bank.getLiquidity() << std::endl;
    p_os << "Accounts : " << std::endl;
    p_bank.displayAccounts();
    return (p_os);
}

