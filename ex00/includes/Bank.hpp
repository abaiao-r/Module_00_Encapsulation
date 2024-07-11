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
#include "Account.hpp"

class Bank
{
    private:
        int liquidity;
        std::vector<Account *> clientAccounts;

    public:
        Bank(void);
        Bank(const Bank &src);
        Bank &operator=(const Bank &src);
        ~Bank(void);

        int getLiquidity(void) const;
        void createAccount(void);
        void deleteAccount(int id);
        void modifyAccount(int id, int amount);
        void giveLoan(int id, int amount);
        const std::vector<const Account *> &getAccounts(void) const;
        void displayAccounts(void) const;

};
    // p_os = print output stream && p_bank = print bank
    std::ostream &operator<<(std::ostream &p_os , const Bank &p_bank);

#endif