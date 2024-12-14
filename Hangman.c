#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Global
char word[20];                          // Word
int chances = 0;                        // chances to find the word
char answer[20] = "__________________"; // blanks (aka placeholder for unknown letters)
char letter;                            // letter (aka letters to find the word)
char Player1_name[20];                  // P1 name
char Player2_name[20];                  // P2 name
char Word_asker[20];                    // One who ask the word
char Letter_typer[20];                  // One who write the letters
char remembered_letters[20];            // typed letters are stored here
int remember_count = 0;                 // remember the index of remember_letters list

// Prototype
void remember_letters(int c);  // responsible for remembering unmatched typed letters
void History(char winner[20]); // responsible for creating history
bool get_players_name();       // responsible for getting Players name
void update_answer();          // responsible for updating answer list on matched letter
bool letter_in_word();         // responsible for checking letters match in word
bool winner();                 // responsible to finding winner
void match();                  // responsible for match

// Main
int main(void)
{
AGAIN:                                                                                                                                                                                                                                                                        // goto label to call on wrong choices
    system("clear");                                                                                                                                                                                                                                                            // screen cleaner
    printf("\t\t\tHANGMAN GAME\n");                                                                                                                                                                                                                                           // Display (Using multiple TABs (\t) to center the it on the screen )
    printf("SUMMARY: Hangman is a guessing game for two Players.\nOne player thinks of a word and other tries to guess it by adding letters within a\ncertain number of chances + a bonus chance. If word found\nwithout losing all chances you WON Else word typer WON.\n"); // Display
    printf("--------------------------------------------------\n\n");                                                                                                                                                                                                           // Display
    printf("1. To play\n2. To Show History\n3. To Quit\n");                                                                                                                                                                                                                   // Display
    char choice;                                                                                                                                                                                                                                                              // store user choice
    scanf("%c", &choice);                                                                                                                                                                                                                                                     // get user choice

    // validate chice
    switch (choice)
    {
    case '1':
        system("clear"); // screen cleaner

        // Get team to play
        bool who_write_word = get_players_name(); // get_players_name function callback
        if (who_write_word == true)               // if return true
        {
            strcpy(Word_asker, Player1_name);   // word asker is P1
            strcpy(Letter_typer, Player2_name); // letter typer is P2
        }
        else if (who_write_word == false) // inverse
        {
            strcpy(Word_asker, Player2_name);   // word asker is P2
            strcpy(Letter_typer, Player1_name); // letter typer is P1
        }

        // get Word
        system("clear");        // screen cleaner
        printf("\t\tWORD\n"); // Display
        printf("%s type your word: ", Word_asker);
        scanf("%s", word);          // Word assign to Global word
        chances = strlen(word) + 1; // lenght of word assign to Global chances
        system("clear");              // screen cleaner
        match();                    // match callback
        break;

    case '2':
        system("code History.dat"); // screen command executer
        break;
    case '3':
        printf("Game Exited\n"); // Display
        break;

    default:
        system("clear"); // screen cleaner
        goto AGAIN;    // label callback
        break;
    }
}

// match started
void match()
{
    int len = strlen(word); // lenght of word ( FOR LOOP )
    while (chances != 0)    // time match played
    {
        system("clear");                           // screen cleaner
        printf("\t\tMATCH\n");                   // Display
        printf("Chances: %i", chances);          // Chances: x
        printf("\t\t");                          // TAB TAB
        printf("[");                             // [
        for (int i = 0; i < remember_count; i++) // loop through remember_count
        {
            printf("%c ", remembered_letters[i]); // write remembered_letters list
        }
        printf("]");                  // ]
        printf("\n");                 // NEWLINE
        for (int i = 0; i < len; i++) // print answer list blank's
        {
            printf("%c ", answer[i]); // _ _ _ _ _ acc to word lenght
        }

        // get user input for letter
        printf("\n\nLetter: "); // Letter:
        getchar();              // buffer cleaner
        scanf("%c", &letter);   // assign to global letter

        // check letter in word
        if (!letter_in_word()) // if letter not in word
        {
            remember_letters(remember_count); // remember the typed letter
            remember_count++;
            chances--; // lost 1 chance
        }
        else // add letter to answer's list
        {
            update_answer();
        }

        // check winner and loser
        if (winner()) // if true
        {

            system("clear");                                                          // screen cleaner
            printf("\t\tMATCH FINISHED\n");                                         // Display
            printf("Congratulation!, %s\nYou WON the Match.....!\n", Letter_typer); // Display
            printf("Word you WON aginst: %s\n\n", word);                            // Display
            History(Letter_typer);                                                  // Histroy creator callback
            break;                                                                  // break while loop
        }
        else if (chances == 0) // if lost chances
        {
            system("clear");                                                        // screen cleaner
            printf("\t\tMATCH FINISHED\n");                                       // Display
            printf("Congratulation!, %s\nYou WON the Match.....!\n", Word_asker); // Display
            printf("Word you WON aginst: %s\n\n", word);                          // Display
            History(Word_asker);                                                  // Histroy creator callback
                                                                                  // no need to break the loop
                                                                                  // loop breaks itself when chances turns to 0
        }
    }
}

// check letter in word
bool letter_in_word()
{
    int len = strlen(word);       // lenght of word (FOR LOOP)
    for (int i = 0; i < len; i++) // loop through word
    {
        if (letter == word[i]) // if letter is in word
        {
            return true;
        }
        if (letter - 32 == word[i]) // if capital of letter is in word
        {
            return true;
        }
    }
    return false;
}

// update answer if letter matched word
void update_answer()
{
    int len = strlen(word);       // lenght of word (FOR LOOP)
    for (int i = 0; i < len; i++) // loop through word
    {
        if (letter == word[i]) // if letter is in word
        {
            answer[i] = letter; // update answer's that index with letter
        }
        if (letter - 32 == word[i]) // if capital of letter is in word
        {
            answer[i] = letter - 32; // update answer's that index with letter
        }
    }
}

// check Winner
bool winner()
{
    int matching = 0;             // similarity count
    int len = strlen(word);       // lenght of word (FOR LOOP)
    for (int i = 0; i < len; i++) // loop till lenght of word in both (word && answer)
    {
        if (word[i] == answer[i]) // if both are similar
        {
            matching++; // increament matching
        }
    }
    if (matching == len) // if similarity count is same as lenght
    {
        return true; // they matched with specified lenght
    }
    return false;
}

// get players name
bool get_players_name()
{
    printf("\t\tNAME THE PLAYERS\n"); // Display
    // prompt Players name
    printf("Player1 name: "); // Player1 name:
    scanf("%s", Player1_name);
    printf("Player2 name: "); // Player2 name:
    scanf("%s", Player2_name);

    system("clear"); // screen cleaner

    // ask who want to write the word
AGAIN:
    printf("\t\tNAME THE PLAYERS\n"); // Display
    printf("Who want to write the word?\n1. %s\n2. %s\n", Player1_name, Player2_name);
    char choice; // user choice for writing word
    getchar();   // buffer cleaner
    scanf("%c", &choice);
    switch (choice)
    {
    case '1':
        return true;
        break;
    case '2':
        return false;
        break;
    default:
        system("clear"); // screen cleaner
        goto AGAIN;
        break;
    }
}

// History creator
void History(char winncer[20])
{
    FILE *file;                            // file pointer
    file = fopen("History.dat", "a");      // open in append mode
    if (strcmp(winner, Player1_name) == 0) // if winner matches P1
    {
        fprintf(file, "\nPlayer1: %s (Won)\nPlayer2: %s\n", &Player1_name, &Player2_name); // Players name
    }
    else if (strcmp(winner, Player2_name) == 0) // if winner matches P2
    {
        fprintf(file, "\nPlayer1: %s\nPlayer2: %s (Won)\n", &Player1_name, &Player2_name); // Players name
    }

    fprintf(file, "Word: %s\n", &word);               // Word: XXXXXX
    fprintf(file, "Chances: %i + 1\n", strlen(word)); // Chances: X

    fclose(file); // Memory safety
}

// Remember letters
void remember_letters(int c)
{
    for (int i = c; i < 20; i++)
    {
        remembered_letters[i] = letter; // add letter to remembered list
    }
}