/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrefrancisco <andrefrancisco@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:59:05 by guest             #+#    #+#             */
/*   Updated: 2024/07/17 11:56:25 by andrefranci      ###   ########.fr       */
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

/**
 * @brief This function tests the functionality of adding and deducting money from an account.
 * 
 * It creates a bank object, creates an account, and performs various operations such as depositing and withdrawing money.
 * The function checks if the account values and bank liquidity are updated correctly after each operation.
 * 
 * @return void
 */
void    testAddMoneyAndDeductMoney()
{
    std::cout << CYAN << "Test: Adding 100 to an account...\n" << RESET;
    Bank bank;
    bank.createAccount();
    int accountId = bank[10].getId();

    bank.deposit(accountId, 100);
    std::cout << bank << std::endl;
    if (bank[10].getValue() == 95 && bank.getLiquidity() == 5)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    std::cout << CYAN << "Test: Deducting 20 from an account...\n" << RESET;
    bank.withdraw(accountId, 20);
    std::cout << bank << std::endl;

   
    if (bank[10].getValue() == 75 && bank.getLiquidity() == 5)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    std::cout << CYAN << "Test: Deducting 100 from an account...\n" << RESET;
    bank.withdraw(accountId, 100);
    //show account value
    std::cout << bank << std::endl;

    

    if (bank[10].getValue() == 75 && bank.getLiquidity() == 5)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    std::cout << CYAN << "Test: ADD INT_MAX to an account...\n" << RESET;
    bank.deposit(accountId, INT_MAX);
    std::cout << bank << std::endl;
    bank.deposit(accountId, INT_MAX);
    std::cout << bank << std::endl;
    bank.deposit(accountId, INT_MAX);
    std::cout << bank << std::endl;
    bank.deposit(accountId, INT_MAX);
    std::cout << bank << std::endl;


    if (bank[10].getValue() == 2040109540 && bank.getLiquidity() == 107374187)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    std::cout << CYAN << "Test: Deduct INT_MIN from an account...\n" << RESET;
    bank.deposit(accountId, INT_MIN);

    std::cout << bank << std::endl;

    if (bank[10].getValue() == 2040109540 && bank.getLiquidity() == 107374187)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
    
}

/**
 * @brief Test case for adding money to an account via the bank only.
 * 
 * This test verifies that money can only be added to an account through the bank class.
 * It checks if direct modification of the account or adding money without using the bank is not allowed.
 * The test creates a bank, creates an account, and attempts to add money directly to the account.
 * It then checks if the account value and bank liquidity are updated correctly.
 * If the test passes, it prints a success message; otherwise, it prints a failure message.
 * 
 * @note This test indirectly checks the encapsulation of the account class by only allowing bank modification.
 * If encapsulation is broken, manual setting of the account value would be possible.
 */
void testAddMoneyViaBankOnly()
{
    std::cout << CYAN << "Test: Adding money to an account can only be done via the bank...\n" << RESET;
    Bank bank;
    bank.createAccount();
    int accountId = bank[9].getId();

    // Attempt to add money directly (should not be possible in a protected class)
    // Direct modification is not allowed, so we modify through the bank
    bank.deposit(accountId, 100);
    if (bank[9].getValue() == 95 && bank.getLiquidity() == 5)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    // Attempt to modify account directly (should not be possible)
    // This test checks the encapsulation indirectly by only allowing bank modification
    // If encapsulation is broken, manual setting would be possible
}

/**
 * @brief This function tests the functionality of giving a loan in a Bank.
 * 
 * It creates a Bank object, creates an account, deposits funds into the account,
 * and then gives a loan to the account. It checks if the loan is given correctly
 * and if the bank's liquidity is updated accordingly.
 * 
 * It also tests scenarios where the loan amount exceeds the bank's funds, where
 * the loan amount is less than 0, and where the loan amount is greater than INT_MAX.
 * 
 * @return void
 */
void testGiveLoan(void)
{
    std::cout << CYAN << "Test: Bank can give a loan within its funds...\n" << RESET;
    Bank bank;
    bank.createAccount();
    bank.deposit(bank[5].getId(), 1000);
    std::cout << bank << std::endl;
    bank.giveLoan(bank[5].getId(), 50);

    std::cout << bank << std::endl;


    if (bank[5].getValue() == 1000 && bank.getLiquidity() == 0)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    // Test giving loan exceeding liquidity
    std::cout << CYAN << "Test: Bank cannot give a loan exceeding its funds...\n" << RESET;
    Bank bank2;
    bank2.createAccount();
    bank2.deposit(bank2[6].getId(), 1000);
    std::cout << bank2 << std::endl;
    bank2.giveLoan(bank2[6].getId(), 5000);
    std::cout << bank2 << std::endl;
    
    if (bank2[6].getValue() == 1000 && bank2.getLiquidity() == 0)
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
    else
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }

    // Test to loan less than 0
    std::cout << CYAN << "Test: Bank cannot give a loan less than 0...\n" << RESET;
    Bank bank3;
    bank3.createAccount();
    bank3.deposit(bank3[7].getId(), 1000);
    bank3.giveLoan(bank3[7].getId(), -50);
    std::cout << bank3 << std::endl;

    if (bank3[7].getValue() == 1000 && bank3.getLiquidity() == 0)
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
    else
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }

    // Test to loan > Int_max
    std::cout << CYAN << "Test: Bank cannot give a loan greater than INT_MAX...\n" << RESET;
    Bank bank4;
    bank4.createAccount();
    bank4.deposit(bank4[8].getId(), 1000);
    bank4.giveLoan(bank4[8].getId(), INT_MAX);
    std::cout << bank4 << std::endl;

    if (bank4[8].getValue() == 950 && bank4.getLiquidity() == 50)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
}

/**
 * @brief This function tests the functionality of creating, deleting, and modifying accounts in a Bank.
 * 
 * It creates a Bank object, creates two accounts, deletes one account, and modifies the remaining account.
 * The function then checks if the operations were successful by comparing the initial and final sizes of the accounts,
 * and checking the values of the modified account and the bank's liquidity.
 */
void testCreateDeleteModifyAccounts()
{
    std::cout << CYAN << "Test: Bank can create, delete, and modify accounts...\n" << RESET;
    Bank bank;
    bank.createAccount();
    bank.createAccount();

    int initialSize = bank.getAccounts().size();
    std::cout << "Before deleting account: " << bank << std::endl;
    bank.deleteAccount(bank[3].getId());
    std::cout << "After deleting account: " << bank << std::endl;
    int newSize = bank.getAccounts().size();

    if (initialSize == 2 && newSize == 1)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }

    // Test modifying account
    int accountId = bank[4].getId();
    bank.deposit(accountId, 100);

    std::cout << "After modifying account: " << bank << std::endl;
    
    if (bank[4].getValue() == 95 && bank.getLiquidity() == 5)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
}

/**
 * @brief Test the protection of account attributes from modification.
 * 
 * This function creates an account without going through the bank class and tries to modify its attributes.
 * It verifies that the account attributes cannot be modified from the outside and should result in a compilation error.
 */
void testAccountModificationProtection()
{
    std::cout << CYAN << "Test: Account attributes are not modifiable from the outside...\n" << RESET;
    
    // create account without going through bank class and try to modify it
    // should not be possible and give an error of compilation
/*     Account account;
    account.id = 1;
    account.value = 100;
    account.addValue(100);
    account.deductValue(50);
 */

}

/**
 * @brief Test case to check if accounts have unique IDs.
 * 
 * This function creates two accounts in a bank and checks if their IDs are unique.
 * If the IDs are unique, the test passes; otherwise, the test fails.
 */
void testUniqueAccountIds()
{
    std::cout << CYAN << "Test: Accounts must have unique IDs...\n" << RESET;
    Bank bank;
    bank.createAccount();
    bank.createAccount();

    int id1 = bank[1].getId();
    int id2 = bank[2].getId();

    if (id1 != id2)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
}

/**
 * @brief This function tests if the bank receives 5% of each money inflow.
 * 
 * It creates a bank object, creates an account, and deposits 100 units of money into the account.
 * Then, it checks if the bank's liquidity is 5 and if the account's value is 95.
 * If the test passes, it prints "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n", otherwise it prints "Test failed!".
 */
void testBankReceive5Percent()
{
    std::cout << CYAN << "Test: Bank receives 5% of each money inflow... \n" << RESET;
    Bank bank;
    bank.createAccount();
    int accountId = bank.getAccounts().at(0)->getId();
    std::cout << bank << std::endl;

    bank.deposit(accountId, 100);
    std::cout << bank << std::endl;
    if (bank.getLiquidity() == 5 && bank.getAccounts().at(0)->getValue() == 95)
    {
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n\n" << RESET;
    }
    else
    {
        std::cout << RED << "Test failed!\n" << RESET;
    }
}



/**
 * @brief This function tests the deletion of accounts.
 * 
 * It creates multiple accounts, deletes some of them, and checks if the deletion was successful.
 * The function performs three tests:
 * 1. Deleting a single account and checking if the account was successfully deleted.
 * 2. Deleting 1000 accounts and checking if all accounts were deleted.
 * 3. Deleting 1,000,000 accounts and checking if all accounts were deleted.
 * 
 * @return void
 */
void testDeleteAccounts()
{
    std::cout << CYAN << "Test: Deleting accounts...\n" << RESET;
    {
        Bank bank;
        bank.createAccount();
        bank.createAccount();
        std::cout << bank << std::endl;
        bank.deleteAccount(bank[1].getId());
        std::cout << bank << std::endl;

        if (bank.getAccounts().size() == 1)
        {
            std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n Account deleted successfully.\n" << RESET;
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
            bank.deleteAccount(bank[i].getId());
        }

        if (bank.getAccounts().empty())
        {
            std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n All accounts deleted successfully.\n" << RESET;
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
                bank.deleteAccount(bank[i].getId());
            }

            if (bank.getAccounts().empty())
            {
                std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n All accounts deleted successfully.\n" << RESET;
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


/**
 * @brief Tests the uniqueness of account IDs.
 * 
 * This function creates multiple accounts using the `Bank` class and checks if the account IDs are unique.
 * It performs two tests:
 * 1. It creates 1000 accounts and verifies that the account IDs are unique up to 1000.
 * 2. It creates more than `INT_MAX` accounts and verifies that the account IDs are unique up to `INT_MAX`.
 * 
 * @note This function assumes that the `Bank` class and the `Account` class have been properly implemented.
 * 
 * @return None.
 */
void testAccountIDUniqueness()
{
    std::cout << CYAN << "Test: Account IDs must be unique...\n" << RESET;
    
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
            int id = bank[i].getId();
            if (std::find(ids.begin(), ids.end(), id) != ids.end())
            {
                unique = false;
                break;
            }
            ids.push_back(id);
        }

        if (unique)
        {
            std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n Account IDs are unique up to 1000.\n" << RESET;
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
            std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n Created more than INT_MAX accounts.\n" << RESET;
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
            int id = bank[i].getId();
            if (ids.find(id) != ids.end())
            {
                unique = false;
                break;
            }
            ids.insert(id);
        }

        if (unique)
        {
            std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n Account IDs are unique up to INT_MAX.\n" << RESET;
        }
        else
        {
            std::cout << RED << "Test failed! Account IDs are not unique.\n" << RESET;
        }
    }
}

/**
 * @brief Test function to create a large number of accounts.
 * 
 * This function tests the creation of a large number of accounts in a Bank object.
 * It creates 1000 accounts and checks if the number of accounts in the Bank object is 1000.
 * It also tests creating more than INT_MAX accounts and checks if an exception is thrown.
 */
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
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n Created 1000 accounts.\n" << RESET;
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
        std::cout << GREEN << "Test passed!\n\n-----------------------------------------------------------------------------------------------------------------------------\n\n Created more than INT_MAX accounts.\n" << RESET;
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


/**
 * @brief The main function of the program.
 * 
 * This function is the entry point of the program. It runs various tests related to encapsulation.
 * The tests include testing account creation, modification, deletion, bank operations, and more.
 * 
 * @return 0 indicating successful execution of the program.
 */
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
