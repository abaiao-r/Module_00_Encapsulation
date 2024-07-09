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

void TestEncapsulation::testAccount()
{
    std::cout << CYAN << "Testing Account class if it is encapsulated" << RESET << std::endl;

    Account account;

    // The following lines should cause compilation errors if the attributes are private
    // Uncommenting these lines should cause the code to fail to compile
    // account.id = 1;       // Should cause compilation error
    // account.value = 100;  // Should cause compilation error

}

void TestEncapsulation::testBank()
{
    std::cout << CYAN << "Testing Bank class if it is encapsulated" << RESET << std::endl;
    
    Bank bank;
    // The following lines should cause compilation errors if the attributes are private
    // Uncommenting these lines should cause the code to fail to compile
    // bank.liquidity = 1000;  // Should cause compilation error
    // bank.clientAccounts.push_back(new Account());  // Should cause compilation error
}