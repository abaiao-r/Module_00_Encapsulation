# PISCINE OBJECT - Module 00: Encapsulation

![Encapsulation](https://www.crio.do/blog/content/images/2022/01/What-is-Encapsulation.png)

## Introduction

This module focus on a fundamental concept in object-oriented programming: encapsulation. Encapsulation allows you to hide the internal state of an object and require all interactions to be performed through an object's methods, enhancing security and simplicity.

## Why is Encapsulation Relevant?

Encapsulation ensures that the internal representation of an object is hidden from the outside. This provides several benefits:
- **Security**: By restricting access to internal data, encapsulation helps prevent accidental or unauthorized modifications.
- **Maintainability**: Encapsulation makes it easier to manage and update code. Changes to the internal implementation do not affect external code that uses the object.
- **Modularity**: Encapsulation allows you to divide your program into distinct, manageable sections, improving the overall structure and readability of the code.

## How to Run

To run the project, follow these steps on your terminal:

1. **Clone the Repository**:
   ```sh
   git clone git@github.com:abaiao-r/Module_00_Encapsulation.git
   cd Module_00_Encapsulation
   ```

2. **For each exercise, go to its directory, compile the code, and run the executable**:
   ```sh
    cd ex00
    make all
    ./Divide_and_conquer
   ```
   ```sh
    cd ex01
    make all
    ./I_dont_know_what_im_doing
    ```

## Exercises

### Exercise 00: Divide and Conquer

In this exercise, I encapsulated the attributes and methods of a banking system and customer account system. The goal is to ensure that sensitive data and operations are protected from unauthorized access and modification.

**Relevance:**
- **Security**: By making account attributes private, we prevent unauthorized users from directly modifying account balances and loan information, ensuring that only the bank can perform these actions through controlled methods.
- **Integrity**: Ensuring unique account IDs and managing account actions through the bank prevents logical inconsistencies and fraudulent activities.
- **Control**: By handling all transactions through the bank, it can implement rules like taking a percentage fee on each deposit, maintaining the integrity and profitability of the banking system.

### Exercise 01: I Don’t Know What I’m Doing!

In this exercise, I created a `Vector2` structure to represent points and a `Graph` class to manage and display these points. This exercise focuses on encapsulating the data and behavior associated with a graphical representation.

**Relevance:**
- **Data Integrity**: Encapsulating the coordinates within the `Vector2` structure ensures that they are only modified through controlled methods, preventing invalid states.
- **Modularity**: Separating the `Graph` class from the `Vector2` structure allows each class to focus on its specific responsibilities. The `Graph` class manages the collection of points and their visualization, while `Vector2` handles the details of point representation.
- **Encapsulation in Visualization**: By managing the addition and display of points within the `Graph` class, we ensure that the graph's internal state is consistent and correctly rendered when outputting to the console.

## Conclusion

Encapsulation is a key concept in object-oriented programming that promotes better coding practices by hiding the internal state of objects and requiring all interactions to be performed through an object's methods. By following the principles of encapsulation, you can create more secure, maintainable, and modular code.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


## Author

👤 ** André Francisco Baião Rolão Cândido da Silva **

