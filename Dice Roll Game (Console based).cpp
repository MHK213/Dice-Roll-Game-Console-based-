#include <iostream>
#include <cstdlib>
#include <ctime>  

using namespace std;

enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stGameResults {
    short GameRounds = 0;
    short Player1WonTimes = 0;
    short ComputerWonTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

struct stRoundInfo {
    short RoundNumber = 0;
    short Player1Rolled = 0;
    short ComputerRolled = 0;
    enWinner Winner;
    string WinnerName;

};

short RandomNumber(short From, short To) {
    short RandNum = rand() % (To - From + 1) + From;

    return RandNum;
}

short ReadHowManyRounds() {
    short GameRounds = 1;

    do {
        cout << "Enter How Many Rounds 1 to 10 ? \n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;
}

enWinner HowWonTheRound(stRoundInfo RoundInfo) {
    if (RoundInfo.Player1Rolled == RoundInfo.ComputerRolled)
        return enWinner::Draw;
    else if (RoundInfo.Player1Rolled > RoundInfo.ComputerRolled)
        return enWinner::Player1;
    else
        return enWinner::Computer;
}

string WinnerName(enWinner Winner) {
    switch (Winner) {
    case enWinner::Player1:
        return "Player1";
    case enWinner::Computer:
        return "Computer";
    case enWinner::Draw:
        return "No Winner";
    default:
        return "Unknown";
    }
}

void setWinnerScreenColor(enWinner Winner) {
    switch (Winner) {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    case enWinner::Draw:
        system("color 6F");
        break;
    }
}

void PrintRoundResult(stRoundInfo RoundInfo) {
    cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1  Choice: " << RoundInfo.Player1Rolled << endl;
    cout << "Computer Choice: " << RoundInfo.ComputerRolled << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]" << endl;
    cout << "__________________________________\n" << endl;

    setWinnerScreenColor(RoundInfo.Winner);
}

enWinner HowWonTheGame(short PlayerWonTimes, short ComputerWonTimes) {
    if (PlayerWonTimes > ComputerWonTimes)
        return enWinner::Player1;
    else if (PlayerWonTimes < ComputerWonTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults FillGameResults(short HowManyRounds, short PlayerWonTimes, short ComputerWonTimes, short DrawTimes) {
    stGameResults GameResults;

    GameResults.GameRounds = HowManyRounds;
    GameResults.Player1WonTimes = PlayerWonTimes;
    GameResults.ComputerWonTimes = ComputerWonTimes;
    GameResults.DrawTimes = DrawTimes;
    GameResults.GameWinner = HowWonTheGame(PlayerWonTimes, ComputerWonTimes);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);

    return GameResults;
}

void GoToNextRound() {
    cout << "\n\nPress any key to go to Next Round..." << endl;
    system("pause>0");
}

stGameResults PlayGame(short HowManyRounds) {
    stRoundInfo RoundInfo;
    short Player1WonTimes = 0, ComputerWonTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
        cout << "\nRound [" << GameRound << "] begins: \n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Rolled = RandomNumber(1, 6);
        RoundInfo.ComputerRolled = RandomNumber(1, 6);
        RoundInfo.Winner = HowWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Computer)
            ComputerWonTimes++;
        else if (RoundInfo.Winner == enWinner::Player1)
            Player1WonTimes++;
        else
            DrawTimes++;

        PrintRoundResult(RoundInfo);
        if(GameRound != 3)
            GoToNextRound();
    }

    return FillGameResults(HowManyRounds, Player1WonTimes, ComputerWonTimes, DrawTimes);
}

string Tab() {
    return "\t\t";
}

void ShowGameOverScreen() {
    cout << Tab() << "__________________________________________________________\n\n";
    cout << Tab() << "                     +++ Game Over +++\n";
    cout << Tab() << "__________________________________________________________\n\n";
}

void ShowFinalGameScreen(stGameResults GameResults) {

    cout << Tab() << "_____________________ [Game Results] _____________________\n\n";
    cout << Tab() << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tab() << "Player1 Won times  : " << GameResults.Player1WonTimes << endl;
    cout << Tab() << "Computer Won times : " << GameResults.ComputerWonTimes << endl;
    cout << Tab() << "Draw times         : " << GameResults.DrawTimes << endl;
    cout << Tab() << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tab() << "__________________________________________________________\n\n";

    setWinnerScreenColor(GameResults.GameWinner);
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void StartGame() {

    char PlayAgain = 'Y';

    do {
        ResetScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameScreen(GameResults);

        cout << endl << Tab() << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}