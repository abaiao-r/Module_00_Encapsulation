/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:59:00 by guest             #+#    #+#             */
/*   Updated: 2024/07/09 11:03:20 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACCOUNT_HPP
# define ACCOUNT_HPP

#include <iostream>

class Account
{
    private:
        int id;
        int value;
        static int nextId;
    
    public:
        Account(void);
        Account(const Account &src);
        Account &operator=(const Account &src);
        ~Account(void);

        int getId(void) const;
        int getValue(void) const;
        void addValue(int amount);
        void deductValue(int amount);

};
    // p_os = print output stream && p_account = print account
    std::ostream &operator<<(std::ostream &p_os , const Account &p_account);

#endif