/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaiao-r <abaiao-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:58:50 by guest             #+#    #+#             */
/*   Updated: 2024/09/16 20:30:59 by abaiao-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Bank.hpp"
#include "../includes/colours.hpp"

/**
 * @brief Default constructor for the Bank class.
 * 
 * This constructor initializes the liquidity of the bank to 0.
 */
Bank::Bank(void) : liquidity(0)
{
}


/**
 * @brief Constructs a new Bank object by copying the contents of another Bank object.
 *
 * @param src The Bank object to be copied.
 */
Bank::Bank(const Bank &src) : liquidity(src.liquidity)
{
    for (std::map<int, Account *>::const_iterator it = src.clientAccounts.begin(); it != src.clientAccounts.end(); it++)
    {
        this->clientAccounts[it->first] = new Account(*(it->second));
    }
}


/**
 * @brief Assignment operator for the Bank class.
 * 
 * This operator assigns the values of the source Bank object to the current Bank object.
 * It performs a deep copy of the client accounts, deleting the existing accounts and copying the new accounts.
 * 
 * @param src The source Bank object to be assigned from.
 * @return A reference to the current Bank object.
 */
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


/**
 * @brief Destructor for the Bank class.
 * 
 * This destructor is responsible for cleaning up the memory allocated for the Account objects
 * stored in the clientAccounts map. It iterates over the map and deletes each Account object.
 * After deleting all the objects, it clears the clientAccounts map.
 */
Bank::~Bank(void)
{
    for (std::map<int, Account *>::iterator it = clientAccounts.begin(); it != clientAccounts.end(); ++it)
    {
        delete it->second;
    }
    this->clientAccounts.clear(); // Clear the vector
}

/**
 * @brief Get the liquidity of the bank.
 * 
 * @return int The liquidity of the bank.
 */
const int &Bank::getLiquidity(void) const
{
    return (this->liquidity);
}

/**
 * @brief Creates a new account and adds it to the bank's client accounts.
 * 
 * This function creates a new account object and adds it to the bank's client accounts
 * using the account's ID as the key. It prints a success message if the account is
 * created successfully, and an error message if the creation fails.
 * 
 * @throws std::exception if the account creation fails.
 */
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


/**
 * @brief Deletes an account from the bank.
 * 
 * This function deletes the account with the specified ID from the bank's list of client accounts.
 * If the account is found and deleted successfully, a message is printed indicating the deletion.
 * If the account is not found, a message is printed indicating that the account was not found.
 * 
 * @param id The ID of the account to be deleted.
 */
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


/**
 * @brief Deposits a specified amount into the account with the given ID.
 * 
 * @param id The ID of the account to deposit into.
 * @param amount The amount to deposit.
 * 
 * @details The function first checks if the amount is valid (not negative, not zero, and not greater than INT_MAX).
 * If the amount is valid, it subtracts a bank fee of 5% from the amount and adds the net amount to the account.
 * The bank fee is added to the bank's liquidity.
 * If the account with the given ID is not found, an error message is displayed.
 * 
 * @note If the amount is invalid or an exception is thrown during the deposit process, an error message is displayed.
 * 
 * @see Bank, Account
 */
void Bank::deposit(int id, int amount)
{
    try {
        // Validate deposit amount
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

        // Find the account by id
        std::map<int, Account *>::iterator it = this->clientAccounts.find(id);
        if (it == this->clientAccounts.end())
        {
            throw std::runtime_error("Error: Account not found");
        }

        // Calculate bank fee and net deposit amount
        int bankFee = amount * 0.05;  // 5% fee
        int netAmount = amount - bankFee;

        // Check for potential underflow
        if (netAmount < 0 && it->second->value < INT_MIN - netAmount)
        {
            throw std::runtime_error("Error: Account value underflow");
        }

        // Check for potential overflow
        if (netAmount > 0 && it->second->value > INT_MAX - netAmount)
        {
            throw std::runtime_error("Error: Account value overflow");
        }

        // Perform the deposit
        it->second->value += netAmount;  // Update the account value
        this->liquidity += bankFee;      // Add the fee to the bank's liquidity

        // Success message
        std::cout << GREEN << "Deposit of " << amount << " made to account " << id << RESET << std::endl;
    }
    catch (const std::exception &e)
    {
        // Catch and display any errors
        std::cerr << YELLOW << e.what() << RESET << std::endl;
    }
}


/**
 * @brief Withdraws a specified amount from a client's account.
 * 
 * @param id The ID of the client's account.
 * @param amount The amount to be withdrawn.
 * 
 * @details This function first checks if the amount is valid (not negative, not zero, and not greater than INT_MAX).
 * If the amount is invalid, an exception is thrown and an error message is printed.
 * If the amount is valid, the function attempts to find the client's account using the provided ID.
 * If the account is found, the function deducts the specified amount from the account using the `deductValue` method.
 * If an exception is thrown during the deduction, an error message is printed.
 * If the deduction is successful, a success message is printed.
 * If the account is not found, an error message is printed.
 */
void Bank::withdraw(int id, int amount)
{
    try {
        // Basic validation checks on withdrawal amount
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

        // Search for the account in clientAccounts map
        std::map<int, Account *>::iterator it = this->clientAccounts.find(id);
        if (it != clientAccounts.end())
        {
            Account* account = it->second;

            // Ensure account has sufficient funds
            if (account->value < amount)
            {
                throw std::runtime_error("Error: Account has insufficient funds");
            }

            // Check for overflow and underflow during deduction
            if (amount > 0 && account->value > INT_MAX - amount)
            {
                throw std::runtime_error("Error: Account value overflow");
            }
            if (amount < 0 && account->value < INT_MIN - amount)
            {
                throw std::runtime_error("Error: Account value underflow");
            }

            // Perform deduction
            account->value -= amount;
            std::cout << RED << "Account " << id << " debited with " << amount << RESET << std::endl;

            std::cout << GREEN << "Withdrawal of " << amount << " made from account " << id << RESET << std::endl;
        }
        else
        {
            // Account not found
            std::cout << RED << "Account " << id << " not found" << RESET << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        // Catch and display errors
        std::cerr << YELLOW << e.what() << RESET << std::endl;
    }
}

/**
 * @brief Grants a loan to a specified account.
 * 
 * This function grants a loan of the specified amount to the account with the given ID.
 * It checks the bank's liquidity and the validity of the loan amount before granting the loan.
 * If the loan is granted, the amount is added to the account's value and deducted from the bank's liquidity.
 * 
 * @param id The ID of the account to grant the loan to.
 * @param amount The amount of the loan to be granted.
 * 
 * @note The loan amount must be greater than 0, less than or equal to the bank's liquidity, and less than or equal to INT_MAX.
 * 
 * @return void
 */
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
        it->second->value += amount;
        this->liquidity -= amount;
        std::cout << GREEN << "Loan of " << amount << " granted to account " << id << RESET << std::endl;
        return;
    }

    std::cout << RED << "Account " << id << " not found" << RESET << std::endl;
}

/**
 * @brief Retrieves a map of all accounts in the bank.
 * 
 * This function returns a constant map of integer account IDs to constant pointers to Account objects.
 * The map contains all the accounts associated with the bank.
 * 
 * @return std::map<int, const Account*> The map of all accounts in the bank.
 */
const std::map<int, const Bank::Account *> &Bank::getAccounts(void) const
{
    std::map<int, const Account *> *accounts = new std::map<int, const Account *>();
    for (std::map<int, Account *>::const_iterator it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++)
    {
        (*accounts)[it->first] = it->second;
    }
    return (*accounts);
}


/**
 * @brief Overloaded subscript operator to access an account by ID.
 * 
 * This function allows accessing an account in the bank's clientAccounts map
 * using the account's ID as the index. If the account is found, a reference to
 * the account object is returned. If the account is not found, an exception of
 * type std::out_of_range is thrown.
 * 
 * @param id The ID of the account to access.
 * @return const Bank::Account& A reference to the account object.
 * @throws std::out_of_range If the account with the given ID is not found.
 */
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


/**
 * @brief Displays the accounts and their values in the bank.
 *
 * This function iterates over the `clientAccounts` map and prints the account number and its corresponding value.
 * The account number is obtained from the key of the map, and the value is obtained from the associated `Account` object.
 */
void Bank::displayAccounts(void) const
{
    std::map<int, Account *>::const_iterator it;
    for (it = this->clientAccounts.begin(); it != this->clientAccounts.end(); it++)
    {
        std::cout << "Account " << it->first << " : " << it->second->getValue() << std::endl;
    }
}

/**
 * Overloaded insertion operator for outputting Bank information.
 * 
 * @param p_os The output stream to write the Bank information to.
 * @param p_bank The Bank object to output.
 * @return The modified output stream.
 */
std::ostream &operator<<(std::ostream &p_os, const Bank &p_bank)
{
    p_os << "Bank informations : " << std::endl;
    p_os << "Liquidity : " << p_bank.getLiquidity() << std::endl;
    p_os << "Accounts : " << std::endl;
    p_bank.displayAccounts();
    return (p_os);
}

