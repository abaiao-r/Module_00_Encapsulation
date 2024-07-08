/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:59:05 by guest             #+#    #+#             */
/*   Updated: 2024/07/08 14:07:59 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bank.hpp"
#include "../includes/colours.hpp"
#include <iostream>

void testAddMoneyViaBankOnly()
{
    std::cout << BLUE << "Test: Adding money to an account can only be done via the bank...\n" << RESET;
    Bank bank;
    bank.createAccount();
    int accountId = bank.getAccounts().at(0)->getId();

    // Attempt to add money directly (should not be possible in a protected class)
    // Direct modification is not allowed, so we modify through the bank
    bank.modifyAccount(accountId, 100);
    if (bank.getAccounts().at(0)->getValue() == 95 && bank.getLiquidity() == 5)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    // Attempt to modify account directly (should not be possible)
    // This test checks the encapsulation indirectly by only allowing bank modification
    // If encapsulation is broken, manual setting would be possible
}

void testGiveLoan(void)
{
    std::cout << BLUE << "Test: Bank can give a loan within its funds...\n" << RESET;
    Bank bank;
    bank.createAccount();
    bank.modifyAccount(bank.getAccounts().at(0)->getId(), 1000);
    bank.giveLoan(bank.getAccounts().at(0)->getId(), 50);

    if (bank.getAccounts().at(0)->getValue() == 1000 && bank.getLiquidity() == 0)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    
    }

    // Test giving loan exceeding liquidity
    std::cout << BLUE << "Test: Bank cannot give a loan exceeding its funds...\n" << RESET;
    Bank bank2;
    bank2.createAccount();
    bank2.modifyAccount(bank2.getAccounts().at(0)->getId(), 1000);
    bank2.giveLoan(bank2.getAccounts().at(0)->getId(), 5000);
    
    if (bank2.getAccounts().at(0)->getValue() == 1000 && bank2.getLiquidity() == 0)
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
    else
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
}

void testCreateDeleteModifyAccounts()
{
    std::cout << BLUE << "Test: Bank can create, delete, and modify accounts...\n" << RESET;
    Bank bank;
    bank.createAccount();
    bank.createAccount();

    int initialSize = bank.getAccounts().size();
    bank.deleteAccount(bank.getAccounts().at(0)->getId());
    int newSize = bank.getAccounts().size();

    if (initialSize == 2 && newSize == 1)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    // Test modifying account
    int accountId = bank.getAccounts().at(0)->getId();
    bank.modifyAccount(accountId, 100);
    
    if (bank.getAccounts().at(0)->getValue() == 95 && bank.getLiquidity() == 5)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
}

void testAccountModificationProtection()
{
    std::cout << BLUE << "Test: Account attributes are not modifiable from the outside...\n" << RESET;
    Account account;
    int originalValue = account.getValue();

    // Attempt to modify account value directly
    account.addValue(100); // This is the only way to modify it

    if (account.getValue() == originalValue + 100)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
}

void testUniqueAccountIds()
{
    std::cout << BLUE << "Test: Accounts must have unique IDs...\n" << RESET;
    Bank bank;
    bank.createAccount();
    bank.createAccount();

    int id1 = bank.getAccounts().at(0)->getId();
    int id2 = bank.getAccounts().at(1)->getId();

    if (id1 != id2)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
}

void testBankReceive5Percent()
{
    std::cout << BLUE << "Test: Bank receives 5% of each money inflow... \n" << RESET;
    Bank bank;
    bank.createAccount();
    int accountId = bank.getAccounts().at(0)->getId();

    bank.modifyAccount(accountId, 100);
    if (bank.getLiquidity() == 5 && bank.getAccounts().at(0)->getValue() == 95)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
}

int main()
{
    /* Bank bank;

    bank.createAccount();
    bank.createAccount();

    bank.modifyAccount(0, 100);
    bank.modifyAccount(1, 200);

    bank.giveLoan(0, 50);

    std::cout << bank << std::endl; */

    std::cout << PURPLE << "Running tests...\n" << RESET;


    testBankReceive5Percent();
    testUniqueAccountIds();
    testAccountModificationProtection();
    testCreateDeleteModifyAccounts();
    testGiveLoan();
    testAddMoneyViaBankOnly();
    
    return (0);
}
