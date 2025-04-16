#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;

#define MAX_USERS 100

// ================= ENCAPSULATION =================
class Player {
private:
    string username;
    string password;
    int scores[5];

public:
    Player() {
        for (int i = 0; i < 5; i++) scores[i] = 0;
    }

    void setCredentials(string user, string pass) {
        username = user;
        password = pass;
    }

    string getUsername() {
        return username;
    }

    int* getScores() {
        return scores;
    }

    void addScore(int index, int value) {
        scores[index] += value;
        scores[4] += value;
    }

    int getScore(int index) {
        return scores[index];
    }

    int authenticate(string user, string pass) {
        return (username == user && password == pass) ? 1 : 0;
    }

    void print() {
        cout << username;
    }

    void resetScores() {
        for (int i = 0; i < 5; i++) scores[i] = 0;
    }

    friend class PlayerManager;
};

// encap uli
class PlayerManager {
private:
    vector<Player> players;

public:
    void storePlayers() {
        ifstream file("players.dat", ios::binary);
        if (file.is_open()) {
            int count;
            file.read((char*)&count, sizeof(int));
            players.resize(count);
            for (int i = 0; i < count; i++) {
                char username[20], password[20];
                int scores[5];
                file.read(username, sizeof(username));
                file.read(password, sizeof(password));
                file.read((char*)scores, sizeof(scores));
                players[i].setCredentials(username, password);
                for (int j = 0; j < 5; j++) players[i].addScore(j, scores[j]);
            }
            file.close();
        }
    }

    void savePlayers() {
        ofstream file("players.dat", ios::binary);
        if (file.is_open()) {
            int count = players.size();
            file.write((char*)&count, sizeof(int));
            for (int i = 0; i < count; i++) {
                char username[20], password[20];
                int* scores = players[i].getScores();
                strncpy(username, players[i].getUsername().c_str(), sizeof(username));
                strncpy(password, "", sizeof(password));
                file.write(username, sizeof(username));
                file.write(password, sizeof(password));
                file.write((char*)scores, sizeof(int) * 5);
            }
            file.close();
        }
    }

    int signUp() {
        system("CLS");
        if (players.size() >= MAX_USERS) {
            cout << "User limit reached!\n";
            return -1;
        }

        string username, password;
        cout << "Enter a new username: ";
        cin >> username;

        for (int i = 0; i < players.size(); i++) {
            if (players[i].getUsername() == username) {
                cout << "Username already taken. Try logging in.\n";
                return -1;
            }
        }

        cout << "Enter a password: ";
        cin >> password;

        Player newPlayer;
        newPlayer.setCredentials(username, password);
        players.push_back(newPlayer);

        savePlayers();
        cout << "Sign-up successful! You can now log in.\n";
        return players.size() - 1;
    }

    int logIn() {
        system("CLS");
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        for (int i = 0; i < players.size(); i++) {
            if (players[i].authenticate(username, password)) {
                cout << "Login successful!\n";
                return i;
            }
        }

        cout << "Invalid username or password!\n";
        return -1;
    }

    void displayLeaderboard(int operation) {
        system("CLS");

        if (players.size() == 0) {
            cout << "No players registered yet.\n";
            return;
        }

        cout << "========== OVERALL LEADERBOARD ==========\n";

        vector<Player> sortedPlayers = players;

        for (int i = 0; i < sortedPlayers.size() - 1; i++) {
            for (int j = i + 1; j < sortedPlayers.size(); j++) {
                int scoreA = sortedPlayers[i].getScore((operation == -1) ? 4 : operation);
                int scoreB = sortedPlayers[j].getScore((operation == -1) ? 4 : operation);
                if (scoreA < scoreB) {
                    swap(sortedPlayers[i], sortedPlayers[j]);
                }
            }
        }

        for (int i = 0; i < sortedPlayers.size(); i++) {
            int score = sortedPlayers[i].getScore((operation == -1) ? 4 : operation);
            cout << (i + 1) << ". " << sortedPlayers[i].getUsername() << " - " << score << " points\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }

    Player& getPlayer(int index) {
        return players[index];
    }
};

// ================= POLYMORPHISM at INHERITANCE =================
class Operation {
public:
    virtual int calculate(int a, int b) = 0; // pure virtual siyaa
};

class Addition : public Operation {
public:
    int calculate(int a, int b) {
        return a + b;
    }
};

class Subtraction : public Operation {
public:
    int calculate(int a, int b) {
        if (a < b) swap(a, b);
        return a - b;
    }
};

class Multiplication : public Operation {
public:
    int calculate(int a, int b) {
        return a * b;
    }
};

class Division : public Operation {
public:
    int calculate(int a, int b) {
        while (b == 0 || a % b != 0) {
            a = (rand() % 10 + 1) * (rand() % 5 + 1);
            b = rand() % 5 + 1;
        }
        return a / b;
    }
};

// ================= ABSTRACTION =================
void arithmeticPractice(Player& player, PlayerManager& manager) {
    int choice, num1, num2, answer, correctAnswer, score;
    Operation* operation = NULL;
    string ops[] = {"Addition", "Subtraction", "Multiplication", "Division"};

    while (1) {
        cout << "\n======= Choose an Operation to Practice =======\n";
        cout << "1. Addition\n2. Subtraction\n3. Multiplication\n4. Division\n5. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 5) break;

        score = 0;
        switch (choice) {
            case 1: operation = new Addition(); break;
            case 2: operation = new Subtraction(); break;
            case 3: operation = new Multiplication(); break;
            case 4: operation = new Division(); break;
            default:
                cout << "Invalid choice!\n";
                continue;
        }

        for (int i = 0; i < 5; i++) {
            system("CLS");
            num1 = rand() % 10 + 1;
            num2 = rand() % 10 + 1;
            correctAnswer = operation->calculate(num1, num2);

            cout << num1;
            if (choice == 1) cout << " + ";
            else if (choice == 2) cout << " - ";
            else if (choice == 3) cout << " x ";
            else cout << " / ";
            cout << num2 << " = ";
            cin >> answer;

            if (answer == correctAnswer) {
                cout << "Correct!\n";
                score++;
            } else {
                cout << "Wrong! The correct answer was " << correctAnswer << ".\n";
            }
            Sleep(1000);
        }

        player.addScore(choice - 1, score);
        manager.savePlayers();
        cout << "\nScore for this session: " << score << "\n";

        delete operation;
    }
}

int main() {
    srand(time(NULL));
    PlayerManager manager;
    manager.storePlayers();

    cout << "\n================ WELCOME PLAYER! ================\n";

    int choice, playerIndex;

    while (1) {
        cout << "\n============ What do you plan to do? ============\n\n";
        cout << "1. Continue\n2. Start\n3. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            playerIndex = manager.logIn();
        } else if (choice == 2) {
            playerIndex = manager.signUp();
        } else if (choice == 3) {
            system("CLS");
            cout << "\n=============== Exiting program. Thank you! ===============\n";
            manager.savePlayers();
            break;
        } else {
            cout << "Invalid choice. Try again.\n";
            continue;
        }

        if (playerIndex != -1) {
            manager.displayLeaderboard(-1);
            arithmeticPractice(manager.getPlayer(playerIndex), manager);
        }
    }

    return 0;
}
