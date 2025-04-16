# Operations-Game
A C++ console game for practicing basic arithmetic operations with user accounts, score tracking, and a leaderboard. Built using object-oriented programming principles.

# 🧮 Arithmetic Practice Game in C++

This is a console-based C++ program that helps users practice basic arithmetic operations while keeping track of their scores. It features a simple login/signup system and a leaderboard to display top performers.

## 🔧 Features

- 👤 **User Account System**: Sign up, log in, and save your progress.
- ➕ ➖ ✖️ ➗ **Practice Arithmetic**: Includes Addition, Subtraction, Multiplication, and Division.
- 📊 **Score Tracking**: Track your performance per operation and total score.
- 🏆 **Leaderboard**: View the top players based on scores.
- 💾 **Local Data Storage**: Saves user data using binary file handling.

## 🧠 Object-Oriented Programming Concepts Used

- **Encapsulation** – User credentials and scores are safely managed inside classes.
- **Inheritance** – Math operations inherit from a common `Operation` base class.
- **Polymorphism** – Different operations (add, subtract, etc.) are handled through one interface.
- **Abstraction** – The practice system hides complex logic behind a simple interface.

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/your-repo-name.git
2. Open the project in a C++ IDE (e.g., Dev-C++, Code::Blocks, Visual Studio).
3. Make sure players.dat is in the same folder (it will be auto-created after sign-up).
4. Compile and run the main.cpp file.
