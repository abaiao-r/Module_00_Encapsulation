/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestEncapsulation.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:57:01 by guest             #+#    #+#             */
/*   Updated: 2024/07/09 12:07:14 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/TestEncapsulation.hpp"


/* // Test the Account class to ensure encapsulation
void TestEncapsulation::testAccount()
{
    Bank bank;
    bank.createAccount();
    bank.createAccount();

    std::cout << YELLOW << "Testing Account class" << RESET << std::endl;
    std::cout << YELLOW << "---------------------" << RESET << std::endl;

    std::cout << YELLOW << "Testing private member variables" << RESET << std::endl;
    std::cout << "Account ID: " << bank.clientAccounts[0]->getId() << std::endl;
    std::cout << "Account Value: " << bank.clientAccounts[0]->getValue() << std::endl;

    std::cout << YELLOW << "Testing private member functions" << RESET << std::endl;
    bank.deposit(bank.clientAccounts[0]->getId(), 100);
    bank.deposit(bank.clientAccounts[0]->getId(), 100);

    std::cout << "Account Value: " << bank.clientAccounts[0]->getValue() << std::endl;
    bank.deleteAccount(bank.clientAccounts[0]->getId());
    bank.deleteAccount(bank.clientAccounts[1]->getId());

    std::cout << YELLOW << "Testing private member variables after deletion" << RESET << std::endl;
    std::cout << "Account ID: " << bank.clientAccounts[0]->getId() << std::endl;
    std::cout << "Account Value: " << bank.clientAccounts[0]->getValue() << std::endl;
}

// Test the Bank class to ensure encapsulation
void TestEncapsulation::testBank()
{
    Bank bank;
    bank.createAccount();
    bank.createAccount();

    std::cout << YELLOW << "Testing Bank class" << RESET << std::endl;
    std::cout << YELLOW << "---------------------" << RESET << std::endl;

    std::cout << YELLOW << "Testing private member variables" << RESET << std::endl;
    std::cout << "Bank Liquidity: " << bank.getLiquidity() << std::endl;

    std::cout << YELLOW << "Testing private member functions" << RESET << std::endl;
    bank.deposit(bank.clientAccounts[0]->getId(), 100);
    bank.deposit(bank.clientAccounts[0]->getId(), 100);

    std::cout << "Bank Liquidity: " << bank.getLiquidity() << std::endl;
    bank.deleteAccount(bank.clientAccounts[0]->getId());
    bank.deleteAccount(bank.clientAccounts[1]->getId());

    std::cout << YELLOW << "Testing private member variables after deletion" << RESET << std::endl;
    std::cout << "Bank Liquidity: " << bank.getLiquidity() << std::endl;
} */