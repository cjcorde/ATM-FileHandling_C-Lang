# C Language ATM

This repository contains a simple command-line based ATM (Automated Teller Machine) program implemented in the C programming language. The program allows users to perform various banking operations, such as creating an account, reading account information, updating balances, making deposits, making withdrawals, and deleting accounts.

## Features

- **Account Creation**: Users can create a new bank account by providing an account number, a personal identification number (PIN), initial balance, and date of account creation.

- **Account Information Reading**: Users can view account information based on their choice, including account number, PIN, balance, and account creation date.

- **Balance Updates**: Account holders can deposit or withdraw funds, updating their account balance accordingly. The system ensures sufficient funds are available for withdrawals.

- **Account Deletion**: Account holders can delete their account. Optionally, the system allows administrators to delete either individual accounts or all accounts in the system.

## Getting Started

1. Clone the repository to your local machine.

2. Compile the C source code using a C compiler. For example:

   ```bash
   gcc -o atm atm.c
   ```

3. Run the executable:

   ```bash
   ./atm
   ```

## How to Use

1. Launch the application and log in using your account number and PIN.

2. Once logged in, you can select from the following options:

   - **Create Account**: To create a new bank account, providing necessary details like account number, PIN, balance, and date.

   - **Read Account**: View account information based on various options, such as account number, PIN, balance, date, or view all accounts.

   - **Update Account**: Perform deposit or withdrawal transactions, updating the account balance accordingly.

   - **Delete Account**: Delete an individual account or all accounts present in the system.

   - **Exit**: To quit the application.

## Note

- Account data is stored in the `account.dat` file, formatted in the following way: `Date: MM/DD/YYYY | Account Number: XXXXX | PIN: YYYY | Balance: ZZZZ.ZZ`

- The PIN should be kept secure as it serves as a security measure for account access.

- This is a simplified implementation and should not be used for actual banking operations in a production environment.

## Contributions

Contributions to the repository are welcome. If you find any issues or have ideas for improvements, feel free to create pull requests or raise issues.

**Disclaimer**: The ATM program in this repository is for educational purposes only and should not be used for real-world banking operations. It does not provide any security features or encryption for sensitive information.

---
