#include <bits/stdc++.h>
using namespace std;

class Player;
class Board;
class Game;

class GameException : public exception
{
private:
    string message;

public:
    GameException(const string &msg) : message(msg) {}
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

enum class GameState
{
    IN_PROGRESS,
    PLAYER1_WON,
    PLAYER2_WON,
    DRAW
};

enum class PlayerType
{
    PLAYER1 = 1,
    PLAYER2 = -1
};

class Player
{
private:
    int id;
    string name;
    PlayerType type;

public:
    Player(int id, string name, PlayerType type) : id(id), name(name), type(type) {}

    string getName() const { return name; }
    PlayerType getType() const { return type; }
    int getId() const { return id; }
};

class Board
{
private:
    vector<vector<int>> board;
    // const int BOARD_SIZE = 3;
    static constexpr int BOARD_SIZE = 3;
    vector<int> rowSum, colSum;
    int diagSum, revDiagSum;

    bool isValidPosition(int x, int y) const
    {
        return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
    }

public:
    Board() : board(BOARD_SIZE, vector<int>(BOARD_SIZE, 0)),
              rowSum(BOARD_SIZE, 0),
              colSum(BOARD_SIZE, 0),
              diagSum(0),
              revDiagSum(0) {}

    void printBoard() const
    {
        cout << "\nCurrent Board State:\n";
        cout << "  0 1 2\n";
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            cout << i << " ";
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                char symbol = ' ';
                if (board[i][j] == static_cast<int>(PlayerType::PLAYER1))
                    symbol = 'X';
                else if (board[i][j] == static_cast<int>(PlayerType::PLAYER2))
                    symbol = 'O';
                cout << symbol;
                if (j < BOARD_SIZE - 1)
                    cout << "|";
            }
            cout << endl;
            if (i < BOARD_SIZE - 1)
                cout << "  -+-+-\n";
        }
        cout << endl;
    }

    bool makeMove(int x, int y, const Player &player)
    {
        if (!isValidPosition(x, y))
        {
            throw GameException("Invalid position! Position must be between 0 and 2.");
        }

        if (board[x][y] != 0)
        {
            throw GameException("Position already occupied!");
        }

        int playerValue = static_cast<int>(player.getType());
        board[x][y] = playerValue;

        rowSum[x] += playerValue;
        colSum[y] += playerValue;
        if (x == y)
            diagSum += playerValue;
        if (x + y == BOARD_SIZE - 1)
            revDiagSum += playerValue;

        return true;
    }

    GameState checkWinner() const
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            if (rowSum[i] == 3 || colSum[i] == 3)
                return GameState::PLAYER1_WON;
            if (rowSum[i] == -3 || colSum[i] == -3)
                return GameState::PLAYER2_WON;
        }

        if (diagSum == 3 || revDiagSum == 3)
            return GameState::PLAYER1_WON;
        if (diagSum == -3 || revDiagSum == -3)
            return GameState::PLAYER2_WON;

        return isFull() ? GameState::DRAW : GameState::IN_PROGRESS;
    }

    bool isFull() const
    {
        for (const auto &row : board)
        {
            for (int cell : row)
            {
                if (cell == 0)
                    return false;
            }
        }
        return true;
    }
};

class Game
{
private:
    Board board;
    Player player1;
    Player player2;
    Player *currentPlayer;
    GameState state;

    void switchPlayer()
    {
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }

    pair<int, int> getPlayerMove() const
    {
        int x, y;
        cout << currentPlayer->getName() << "'s turn (Enter row and column numbers, 0-2): ";

        if (!(cin >> x >> y))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw GameException("Invalid input! Please enter numbers.");
        }

        return {x, y};
    }

public:
    Game() : player1(1, "Player 1", PlayerType::PLAYER1),
             player2(2, "Player 2", PlayerType::PLAYER2),
             state(GameState::IN_PROGRESS)
    {
        currentPlayer = &player1;
    }

    void start()
    {
        cout << "Welcome to Tic-Tac-Toe!\n";
        cout << "Player 1 (X) vs Player 2 (O)\n\n";

        while (state == GameState::IN_PROGRESS)
        {
            try
            {
                board.printBoard();

                auto [x, y] = getPlayerMove();
                board.makeMove(x, y, *currentPlayer);

                state = board.checkWinner();

                if (state == GameState::IN_PROGRESS)
                {
                    switchPlayer();
                }
            }
            catch (const GameException &e)
            {
                cout << "Error: " << e.what() << " Please try again.\n";
                continue;
            }
            catch (const exception &e)
            {
                cout << "Unexpected error occurred: " << e.what() << endl;
                continue;
            }
        }

        board.printBoard();

        switch (state)
        {
        case GameState::PLAYER1_WON:
            cout << "Player 1 wins!\n";
            break;
        case GameState::PLAYER2_WON:
            cout << "Player 2 wins!\n";
            break;
        case GameState::DRAW:
            cout << "It's a draw!\n";
            break;
        default:
            cout << "Unexpected game state!\n";
        }
    }
};

int main()
{
    try
    {
        Game game;
        game.start();
    }
    catch (const exception &e)
    {
        cerr << "Fatal error: " << e.3333333333() << endl;
        return 1;
    }

    return 0;
}