#include <iostream>

class Board
{
    private:
        char data_[8][8];
        int key_;

        /**
         * Clear the terminal
         */
        static void clearTerminal();

        /**
         * Flip a coin
         * @param coinIndex The coin number to be flipped
         * @pre coinIndex is between 0 and 63 (both inclusive).
         */
        void flipCoin( int coinIndex );

        /**
         * Find the spot currently pointed to by the board's status
         * @return The index that the board currently points to
         */
        int getValOfBoard( ) const;

        /**
         * Print the current key location
         */
        void printKey( ) const;

    public:
        /**
         * Default constructor, initializes all spaces to H.
         */
        Board( );

        /**
         * Display the gameboard as it stands
         */
        void display( ) const;

        /**
         * Play the game
         */
        void play( );
};

void Board::flipCoin( int coinIndex )
{
    int i = coinIndex / 8;
    int j = coinIndex % 8;
    data_[i][j] = (data_[i][j] == 'H') ? 'T' : 'H';
}

Board::Board( ) : key_{-1}
{
    for ( int i = 0; i < 8; i++ )
    {
        for (int j = 0; j < 8; j++ )
        {
            data_[i][j] = 'H';
        }
    }
}

void Board::display( ) const
{
    for ( int i = 0; i < 8; i++ )
    {
        for ( int j = 0; j < 8; j++ )
        {
            std::cout << data_[i][j] << '\t';
        }
        std::cout << '\n';
    }
}

void Board::clearTerminal( )
{
    std::system("clear");
}

void Board::printKey( ) const
{
    std::cout << key_ << '\n';
}

int Board::getValOfBoard( ) const
{
    int current = 0;
    for ( int i = 0; i < 8; i++ )
    {
        for ( int j = 0; j < 8; j++ )
        {
            current = data_[i][j] == 'T' ? current ^ ( 8 * i + j ) : current;
        }
    }
    return current;
}

void Board::play( )
{
    int input = -2;
    while ( input != -1 )
    {
        clearTerminal( );
        display( );
        std::cout << "Select a spot 0-63 to flip one of the coins. Enter -1 to finalize the board.\n";
        std::cin >> input;
        if ( input > -1 && input < 64 )
        {
            flipCoin( input );
        }
    }
    clearTerminal( );
    std::cout << "Enter the spot 0-63 to place the key under: ";
    std::cin >> key_;
    clearTerminal( );
    int boardVal = getValOfBoard();
    flipCoin( key_ ^ boardVal );
    display( );
    std::cout << "Coin has been flipped. Where is the key? (0-63)\n";
    std::cin >> input;
    if ( input == key_ )
    {
        std::cout << "Correct! You win!\n";
    } else
    {
        std::cout << "Incorrect. The key was located at spot " << getValOfBoard() << '\n';
    }
}

int main( )
{
    Board *board = new Board();
    board->play();
    delete board;
}
