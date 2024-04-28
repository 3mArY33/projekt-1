#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <fstream>

std::fstream;

void game(char array[10][12])
{
    std::cout << "   CAR GAME    " << '\n';
    std::cout << "Press 's' to start" << '\n';
    char start = _getch();
    if (start == 's')
    {
        const int rows = 10;
        const int columns = 12;
        int tree, tree_2 = 0;
        int score = 0;
        int high_score = 0;
        
        std::ifstream highScoreFile("high_score.txt"); // Utworzenie pliku 
        if (highScoreFile.is_open()) 
        {
            highScoreFile >> high_score;
            highScoreFile.close();
        }
        else 
        {
            std::cout << "Unable to read high score file. Starting with a high score of 0." << '\n';
        }

        char car = 'H';
        char border = '|';
        char road[12];
        for (int i = 0; i < 12; i++)
        {
            road[i] = ' ';
        }
        road[0] = border;
        road[11] = border;
        road[5] = car;
        int carPosition = 5;
        int treePosition_j = 0;
        int treePosition_i = 0;

        while (true)
        {

            for (int i = 0; i < 20; i++)
            {
                for (int i = 0; i < rows; i++)   // Zapisywanie danych do tablicy dwuwymiarowej.
                {
                    for (int j = 0; j < columns; j++)
                    {
                        tree = rand() % 15 + 1;
                        if (i == tree && i != 0 && i != 9 && j != 0 && j != 11 && array[i][j] != '^')
                        {
                           array[i][j] = '^';
                           tree = rand() % 15 + 1;
                        }
                        else
                        {
                            if (j == 0 || j == 11)
                            {
                                array[i][j] = '|';
                            }
                            else
                            {
                                array[i][j] = ' ';
                            }
                        }

                    }
                }

            }
            for (int i = 0; i < 20; i++)
            {
                for (int i = rows - 1; i > 0; i--)
                {
                    for (int j = 0; j < columns; j++)
                    {
                        std::swap(array[i][j], array[i - 1][j]);
                    }
                }
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < columns; j++)
                    {
                        std::cout << array[i][j];
                        tree_2 = rand() % 15 + 1;
                        if (i != tree && j == tree_2)
                        {
                            tree = rand() % 15 + 1;
                            if (j == tree && i != 0 && i != 9 && j != 0 && j != 11 && array[i][j] != '^')
                            {
                                array[i][j] = '^';
                            }
                        }
                        if (array[i][j] == '^')
                        {
                            treePosition_j = j;
                            treePosition_i = i;
                        }
                        if (carPosition == treePosition_j && treePosition_i == 9) // sprawdzenie kolizji
                        {
                            // Po zakoñczeniu gry
                            system("cls");
                            std::cout << "   GAME OVER    " << '\n';
                            std::cout << "Score: " << score << '\n';
                            
                            if (score > high_score)  // Aktualizowanie wyniku w pliku tekstowym
                            {
                                high_score = score;

                                std::ofstream highScoreFile("high_score.txt");
                                if (highScoreFile.is_open())
                                {
                                    highScoreFile << high_score;
                                    highScoreFile.close();
                                    std::cout << "New high score: " << high_score << std::endl;
                                }
                            }
                            
                            std::cout << "To restart the game press 'r'" << '\n';
                            std::cout << "To close the game press 'x' two times" << '\n';

                            char restart;
                            do
                            {
                                restart = _getch();
                            } while (restart != 'r' && restart != 'x');

                            if (restart == 'r')
                            {
                                game(array); // Restart gry
                            }
                            else
                            {
                                if (restart == 'x')
                                {
                                    return; // Zakoñczenie gry i zamkniêcie konsoli
                                }
                            }
                           
                        }
                    }
                    std::cout << '\n';
                }

                score++;  // Naliczanie punktów

                for (int i = 0; i < 12; i++) // Wyœwietlanie tablicy zawieraj¹cej samochód
                {
                    std::cout << road[i];
                }
                std::cout << '\n';
                std::cout << '\n';
                std::cout << "Score: " << score << '\n';
                std::cout << "High score: " << high_score << '\n';
                    
                Sleep(500);
                system("cls");
                if (_kbhit()) // Funkcja obs³uguj¹ca poruszanie samochodem
                {
                    char click = _getch();

                    if (click == 'a' && carPosition > 1)
                    {
                        if (road[carPosition - 1] == ' ')
                        {
                            std::swap(road[carPosition], road[carPosition - 1]);
                            carPosition--;
                        }
                    }

                    if (click == 'd' && carPosition < 10)
                    {
                        if (road[carPosition + 1] == ' ')
                        {
                            std::swap(road[carPosition], road[carPosition + 1]);
                            carPosition++;
                        }
                    }
                }
            }
        }
    }
}
   

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    const int rows = 10;
    char array[10][12];

    game(array);

    return 0;
}
