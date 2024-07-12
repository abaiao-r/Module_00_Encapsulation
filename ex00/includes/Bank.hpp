/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bank.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:58:58 by guest             #+#    #+#             */
/*   Updated: 2024/07/09 12:53:30 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BANK_HPP
# define BANK_HPP

#include <vector>
#include <climits>
#include <iostream>
#include <climits>
#include <stdexcept>
#include <map>

class Bank
{
    private:

        class Account
        {
            private:
                int id;
                int value;
                static int nextId;

                friend class Bank;
                void addValue(int amount);
                void deductValue(int amount);
            
            public:
                Account(void);
                Account(const Account &src);
                Account &operator=(const Account &src);
                ~Account(void);

                int getId(void) const;
                int getValue(void) const;

        };

        int liquidity;
        std::map<int, Account *> clientAccounts;

    public:
        Bank(void);
        Bank(const Bank &src);
        Bank &operator=(const Bank &src);
        ~Bank(void);

        int getLiquidity(void) const;
        void createAccount(void);
        void deleteAccount(int id);
        void deposit(int id, int amount);
        void withdraw(int id, int amount);
        void giveLoan(int id, int amount);
        const std::map<int, const Account *> getAccounts(void) const;
        void displayAccounts(void) const;

        // Overload operator [] to access the accounts by their id
        const Account &operator[](int id) const;
        
};

    // p_os = print output stream && p_bank = print bank
    std::ostream &operator<<(std::ostream &p_os , const Bank &p_bank);

#endif