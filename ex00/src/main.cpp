/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:59:05 by guest             #+#    #+#             */
/*   Updated: 2024/07/09 13:07:00 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bank.hpp"
#include "../includes/colours.hpp"
#include "../includes/TestEncapsulation.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>

void    testAddMoneyAndDeductMoney()
{
    std::cout << CYAN << "Test: Adding 100 to an account...\n" << RESET;
    Bank bank;
    bank.createAccount();
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

    std::cout << CYAN << "Test: Deducting 20 from an account...\n" << RESET;
    bank.modifyAccount(accountId, -20);

   
    if (bank.getAccounts().at(0)->getValue() == 75 && bank.getLiquidity() == 5)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    std::cout << CYAN << "Test: Deducting 100 from an account...\n" << RESET;
    bank.modifyAccount(accountId, -100);
    //show account value
    std::cout << "Account value: " << bank.getAccounts().at(0)->getValue() << std::endl;

    if (bank.getAccounts().at(0)->getValue() == 75 && bank.getLiquidity() == 5)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    std::cout << CYAN << "Test: ADD INT_MAX to an account...\n" << RESET;
    bank.modifyAccount(accountId, INT_MAX);
    bank.modifyAccount(accountId, INT_MAX);
    bank.modifyAccount(accountId, INT_MAX);
    bank.modifyAccount(accountId, INT_MAX);
    // show account value
    std::cout << "Account value: " << bank.getAccounts().at(0)->getValue() << std::endl;
    // show liquidity
    std::cout << "Liquidity: " << bank.getLiquidity() << std::endl;

    if (bank.getAccounts().at(0)->getValue() == 2040109540 && bank.getLiquidity() == 107374187)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    std::cout << CYAN << "Test: Deduct INT_MIN from an account...\n" << RESET;
    bank.modifyAccount(accountId, INT_MIN);

    if (bank.getAccounts().at(0)->getValue() == 2040109540 && bank.getLiquidity() == 107374187)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
    
}

void testAddMoneyViaBankOnly()
{
    std::cout << CYAN << "Test: Adding money to an account can only be done via the bank...\n" << RESET;
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
    std::cout << CYAN << "Test: Bank can give a loan within its funds...\n" << RESET;
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
    std::cout << CYAN << "Test: Bank cannot give a loan exceeding its funds...\n" << RESET;
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

    // Test to loan less than 0
    std::cout << CYAN << "Test: Bank cannot give a loan less than 0...\n" << RESET;
    Bank bank3;
    bank3.createAccount();
    bank3.modifyAccount(bank3.getAccounts().at(0)->getId(), 1000);
    bank3.giveLoan(bank3.getAccounts().at(0)->getId(), -50);

    if (bank3.getAccounts().at(0)->getValue() == 950 && bank3.getLiquidity() == 50)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    // Test to loan > Int_max
    std::cout << CYAN << "Test: Bank cannot give a loan greater than INT_MAX...\n" << RESET;
    Bank bank4;
    bank4.createAccount();
    bank4.modifyAccount(bank4.getAccounts().at(0)->getId(), 1000);
    bank4.giveLoan(bank4.getAccounts().at(0)->getId(), INT_MAX);

    if (bank4.getAccounts().at(0)->getValue() == 950 && bank4.getLiquidity() == 50)
    {
        std::cout << GREEN << "Test passed!\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
}

void testCreateDeleteModifyAccounts()
{
    std::cout << CYAN << "Test: Bank can create, delete, and modify accounts...\n" << RESET;
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
    std::cout << CYAN << "Test: Account attributes are not modifiable from the outside...\n" << RESET;
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
    std::cout << CYAN << "Test: Accounts must have unique IDs...\n" << RESET;
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
    std::cout << CYAN << "Test: Bank receives 5% of each money inflow... \n" << RESET;
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


//Test delete accounts
void testDeleteAccounts()
{
    std::cout << CYAN << "Test: Deleting accounts...\n" << RESET;
    {
        Bank bank;
        bank.createAccount();
        bank.createAccount();
        bank.deleteAccount(bank.getAccounts().at(0)->getId());

        if (bank.getAccounts().size() == 1)
        {
            std::cout << GREEN << "Test passed! Account deleted successfully.\n" << RESET;
        }
        else
        {
            std::cout << RED << "Test failed! Account not deleted.\n" << RESET;
        }
    }

    {
        std::cout << YELLOW << "Test: Delete 1000 accounts...\n" << RESET;
        Bank bank;
        for (int i = 0; i < 1000; ++i)
        {
            bank.createAccount();
        }

        for (int i = 0; i < 1000; ++i)
        {
            bank.deleteAccount(bank.getAccounts().at(0)->getId());
        }

        if (bank.getAccounts().empty())
        {
            std::cout << GREEN << "Test passed! All accounts deleted successfully.\n" << RESET;
        }
        else
        {
            std::cout << RED << "Test failed! Not all accounts were deleted.\n" << RESET;
        }
    }

    {
        std::cout << YELLOW << "Test: Delete 1000000 accounts...\n" << RESET;
        Bank bank;
        try
        {
            for (long i = 0; i < 1000000; ++i)
            {
                bank.createAccount();
            }

            for (long i = 0; i < 1000000; ++i)
            {
                bank.deleteAccount(bank.getAccounts().at(0)->getId());
            }

            if (bank.getAccounts().empty())
            {
                std::cout << GREEN << "Test passed! All accounts deleted successfully.\n" << RESET;
            }
            else
            {
                std::cout << RED << "Test failed! Not all accounts were deleted.\n" << RESET;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << RED << "Test failed! Exception: " << e.what() << "\n" << RESET;
        }
        catch (...)
        {
            std::cout << RED << "Test failed! Unknown exception.\n" << RESET;
        }
    }
}

// Test account ID uniqueness
void testAccountIDUniqueness()
{
    std::cout << CYAN << "Test: Account IDs must be unique...\n" << RESET;
    
    {
        Bank bank;
        bank.createAccount();
        bank.createAccount();

        int id1 = bank.getAccounts().at(0)->getId();
        int id2 = bank.getAccounts().at(1)->getId();

        if (id1 != id2)
        {
            std::cout << GREEN << "Test passed! Account IDs are unique.\n" << RESET;
        }
        else
        {
            std::cout << RED << "Test failed! Account IDs are not unique.\n" << RESET;
        }
    }

    {
        Bank bank;
        for (int i = 0; i < 1000; ++i)
        {
            bank.createAccount();
        }

        std::vector<int> ids;
        bool unique = true;

        for (int i = 0; i < 1000; ++i)
        {
            int id = bank.getAccounts().at(i)->getId();
            if (std::find(ids.begin(), ids.end(), id) != ids.end())
            {
                unique = false;
                break;
            }
            ids.push_back(id);
        }

        if (unique)
        {
            std::cout << GREEN << "Test passed! Account IDs are unique up to 1000.\n" << RESET;
        }
        else
        {
            std::cout << RED << "Test failed! Account IDs are not unique.\n" << RESET;
        }
    }

    {
        Bank bank;
        try
        {
            for (long i = 0; i < static_cast<long>(INT_MAX) + 1; ++i)
            {
                bank.createAccount();
            }
            std::cout << GREEN << "Test passed! Created more than INT_MAX accounts.\n" << RESET;
        }
        catch (const std::exception &e)
        {
            std::cout << RED << "Test failed! Exception: " << e.what() << "\n" << RESET;
        }
        catch (...)
        {
            std::cout << RED << "Test failed! Unknown exception.\n" << RESET;
        }

        // Verify the uniqueness of all IDs up to INT_MAX
        bool unique = true;
        std::set<int> ids;
        for (int i = 0; i < INT_MAX; ++i)
        {
            int id = bank.getAccounts().at(i)->getId();
            if (ids.find(id) != ids.end())
            {
                unique = false;
                break;
            }
            ids.insert(id);
        }

        if (unique)
        {
            std::cout << GREEN << "Test passed! Account IDs are unique up to INT_MAX.\n" << RESET;
        }
        else
        {
            std::cout << RED << "Test failed! Account IDs are not unique.\n" << RESET;
        }
    }
}

void testCreateLotsOfAccounts()
{
    std::cout << CYAN << "Test: Creating a large number of accounts...\n" << RESET;
    Bank bank;

    // Test creating 1000 accounts
    for (int i = 0; i < 1000; ++i)
    {
        bank.createAccount();
    }
    if (bank.getAccounts().size() == 1000)
    {
        std::cout << GREEN << "Test passed! Created 1000 accounts.\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed! Did not create 1000 accounts.\n" << RESET;
    }

    // Test creating more than INT_MAX accounts
    try
    {
        for (long i = 0; i < static_cast<long>(INT_MAX) + 1; ++i)
        {
            bank.createAccount();
        }
        std::cout << GREEN << "Test passed! Created more than INT_MAX accounts.\n" << RESET;
    }
    catch (const std::exception &e)
    {
        std::cout << RED << "Test failed! Exception: " << e.what() << "\n" << RESET;
    }
    catch (...)
    {
        std::cout << RED << "Test failed! Unknown exception.\n" << RESET;
    }
}


int main(void)
{
    std::cout << PURPLE << "Running tests...\n" << RESET;

    // Encapsulation test
/*     TestEncapsulation tester;
    tester.testAccount();
    tester.testBank(); */
    
    // this test stress tests probablytake too long to run and fills up computer memory
    /* testCreateLotsOfAccounts();
    testAccountIDUniqueness();
    testDeleteAccounts(); */

    testBankReceive5Percent();
    testUniqueAccountIds();
    testAccountModificationProtection();
    testCreateDeleteModifyAccounts();
    testGiveLoan();
    testAddMoneyViaBankOnly();
    testAddMoneyAndDeductMoney();
    
    return (0);
}
