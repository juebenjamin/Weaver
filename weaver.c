#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Typedef for the struct Word, which has only one member, a string called "word"
typedef struct
{
    char *word;
} Word;

/* Function takes an array of words, the number of words in the array and a new word to add to the array.
It creates a new array of words with one more element than the original one using realloc, it
creates a new string with the size of the new word and then copies the new word to this string.
It then stores the new string in the last element of the new array of words, increments the number of words in
the array and returns the new array. */
Word *addWordToArray(Word *words, int *numWords, char *word)
{
    Word *newWords = (Word *)realloc(words, sizeof(Word) * (*numWords + 1));
    if (newWords == NULL)
    {
        printf("Error: could not allocate memory for new words.\n");
        exit(1);
    }
    char *newWord = (char *)malloc(sizeof(char) * (strlen(word) + 1));
    if (newWord == NULL)
    {
        printf("Error: could not allocate memory for word.\n");
        exit(1);
    }
    strcpy(newWord, word);
    newWords[*numWords].word = newWord;
    (*numWords)++;
    return newWords;
}

/* This function takes an array of words and the number of words in the array and
frees the memory allocated for each string in the array and for the array itself. */
void freeArray(Word *words, int numWords)
{
    for (int i = 0; i < numWords; i++)
    {
        free(words[i].word);
    }
    free(words);
}

/* This function takes a word, an array of words and the number of words in the array.
It checks if the given word exists in the array of words and returns 1 if it exists, 0 otherwise. */
int isValidWord(char *word, Word *words, int numWords)
{
    for (int i = 0; i < numWords; i++)
    {
        if (strcmp(word, words[i].word) == 0)
        {
            return 1;
        }
    }
    return 0;
}

/* This function takes two words and checks if they differ by exactly one letter.
It returns 1 if they differ by exactly one letter, 0 otherwise. */
int isOneLetterDifferent(char *word1, char *word2)
{
    int numDifferent = 0;
    for (int i = 0; i < strlen(word1); i++)
    {
        if (word1[i] != word2[i])
        {
            numDifferent++;
        }
        if (numDifferent > 1)
        {
            return 0;
        }
    }
    return numDifferent == 1;
}
/* Function takes an array of words and the number of words as input, and returns a randomly
 selected word from the array. Returns the word at that index.*/
char *getRandomWord(Word *words, int numWords)
{
    int randomIndex = rand() % numWords;
    return words[randomIndex].word;
}

/* Function takes an array of words, the number of words in the array,
the desired word length, the maximum word length, the starting word, the ending word, and the current word.
It first prompts the user to enter the starting and ending words, or 'r' for either to select a random word
from the array. It checks if the user entered valid words by making sure they have the desired word length
and exist in the array of words. It then enters a loop where it prompts the user to enter the next word in
the sequence. The loop continues until the user enters the ending word, enters 'q' to quit the game, or enters
an invalid word. It checks if the entered word is valid by making sure it has the desired word length and exists
in the array of words, and that it differs from the current word by exactly one letter. If the entered word is valid,
it updates the current word and increments the number of moves. When the user enters the ending word, it prints a
congratulatory message with the number of moves it took to reach the ending word. */
void playGame(Word *words, int numWords, int wordLength, int maxWordLength, char *startWord,
              char *endWord, char *currentWord)
{
    printf(
        "Enter starting and ending words, or 'r' for either for a random word: ");
    scanf("%s %s", startWord, endWord);
    while (1)
    {
        // Prompting the user to enter the starting and ending words, or 'r' for either to select a random word from the array.
        if (strcmp(startWord, "r") == 0)
        {
            // Select random starting word
            strcpy(startWord, getRandomWord(words, numWords));
        }
        if (strcmp(endWord, "r") == 0)
        {
            // Select random ending word
            strcpy(endWord, getRandomWord(words, numWords));
        }
        // Check if start word and end word are of valid length
        if (strlen(startWord) != wordLength)
        {
            printf("Your word, '%s', is not a %d-letter word. Try again.\n",
                   startWord, wordLength);
            printf("Enter starting and ending words, or 'r' for either for a random "
                   "word: ");
            scanf("%s %s", startWord, endWord);
            continue;
        }
        if (strlen(endWord) != wordLength)
        {
            printf("Your word, '%s', is not a %d-letter word. Try again.\n", endWord,
                   wordLength);
            printf("Enter starting and ending words, or 'r' for either for a random "
                   "word: ");
            scanf("%s %s", startWord, endWord);
            continue;
        }
        // Check if start or end word are in the dictionary
        if (!isValidWord(startWord, words, numWords))
        {
            printf("Your word, '%s', is not a valid dictionary word. Try again.\n",
                   startWord);
            printf("Enter starting and ending words, or 'r' for either for a random "
                   "word: ");
            scanf("%s %s", startWord, endWord);
            continue;
        }
        if (!isValidWord(endWord, words, numWords))
        {
            printf("Your word, '%s', is not a valid dictionary word. Try again.\n",
                   endWord);
            printf("Enter starting and ending words, or 'r' for either for a random "
                   "word: ");
            scanf("%s %s", startWord, endWord);
            continue;
        }
        break;
    }
    // Present the user with their starting and ending words, initialize moves counter and give intructions
    printf("Your starting word is: %s.\n", startWord);
    printf("Your ending word is: %s.\n", endWord);
    int numMoves = 1;
    strcpy(currentWord, startWord);
    printf("\nOn each move enter a word of the same length that is at most 1 "
           "character different and is also in the dictionary.\n");
    printf("You may also type in 'q' to quit guessing.\n");
    while (strcmp(currentWord, endWord) != 0)
    {
        printf("\n%d. Previous word is '%s'. Goal word is '%s'. Next word: ",
               numMoves, currentWord, endWord);
        char nextWord[maxWordLength];
        scanf("%s", nextWord);
        // Stop the loop and present the choice menu if the user enters q
        if (strcmp(nextWord, "q") == 0)
        {
            break;
        }
        // Check the user-entered word for length
        if (strlen(nextWord) != wordLength)
        {
            printf("Your word, '%s', is not a %d-letter word. Try again.\n",
                   nextWord, wordLength);
            continue;
        }
        // Check the user-entered word to see if it's in the dictonary
        if (!isValidWord(nextWord, words, numWords))
        {
            printf("Your word, '%s', is not a valid dictionary word. Try again.\n",
                   nextWord);
            continue;
        }
        // Check that the user-entered word is only one letter different
        if (!isOneLetterDifferent(currentWord, nextWord))
        {
            printf(
                "Your word, '%s', is not exactly 1 character different. Try again.\n",
                nextWord);
            continue;
        }
        // Add one to counter of moves being made
        numMoves++;
        strcpy(currentWord, nextWord);
    }
    //  User entered the ending word, print a congratulatory message with the number of moves it took to reach the ending word.
    if (strcmp(currentWord, endWord) == 0)
    {
        printf("Congratulations! You changed '%s' into '%s' in %d moves.\n",
               startWord, endWord, numMoves - 1);
    }
}

/* Function reads in the words from a file and stores them in an array of words. It takes a pointer to a pointer to a Word
 structure, a pointer to the number of words in the array, a pointer to the desired word length, and the maximum word length.
 It prompts the user to enter the desired word length and reads in words from a file named words.txt that have the desired word
 length. It then stores these words in an array of Word structures using the addWordToArray function. */
void getWords(Word **words, int *numWords, int *wordLength, int maxWordLength)
{
    // Read in words from file
    FILE *filePtr = fopen("words.txt", "r");
    if (filePtr == NULL)
    {
        printf("Error: could not open words.txt for reading\n");
        exit(1);
    }
    // Prompt the user to enter how many letters they want the word to be
    printf("How many letters do you want to have in the words? ");
    scanf("%d", wordLength);
    char word[maxWordLength];
    *numWords = 0;
    *words = NULL;
    // Fetch words from dictonary of proper size, add each fetched word to array of words
    while (fscanf(filePtr, "%s", word) != EOF)
    {
        if (strlen(word) == *wordLength)
        {
            *words = addWordToArray(*words, numWords, word);
        }
    }
    printf("Number of %d-letter words found: %d.\n\n", *wordLength, *numWords);
    fclose(filePtr);
}

/* The main function of the program. It declares the necessary variables, prints an introduction to the game, reads in the
words from the file and gets the game parameters from the user using the getWords function, plays the game using the playGame
function, and allows the user to play again, change the word length, or exit the program. */
int main()
{
    srand(1);
    // Declare variables
    Word *words = NULL;
    int numWords = 0;
    int wordLength = 0;
    int maxWordLength = 50;
    char currentWord[maxWordLength];
    char startWord[maxWordLength];
    char endWord[maxWordLength];

    // Print game introduction and instructions
    printf("Weaver is a game where you try to find a way to get from the "
           "starting word to the ending word.\n");
    printf("You can change only one letter at a time, and each word along the "
           "way must be a valid word.\n");
    printf("Enjoy!\n\n");

    // Read in words from file and get game parameters from user
    getWords(&words, &numWords, &wordLength, maxWordLength);

    // Play the game
    playGame(words, numWords, wordLength, maxWordLength, startWord, endWord, currentWord);

    // Ask user if they want to play again, change word length, or exit program
    int choice = 0;
    do
    {
        printf("\nEnter: \t1 to play again,\n");
        printf("\t2 to change the number of letters in the words and then play "
               "again, or\n");
        printf("\t3 to exit the program.\n");
        printf("Your choice --> ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            // play again
            playGame(words, numWords, wordLength, maxWordLength, startWord, endWord, currentWord);
        }
        else if (choice == 2)
        {
            // change word length then play again
            freeArray(words, numWords);
            getWords(&words, &numWords, &wordLength, maxWordLength);
            playGame(words, numWords, wordLength, maxWordLength, startWord, endWord, currentWord);
        }
        else if (choice == 3)
        {
            // exit the program
            printf("\n\nThanks for playing!\n");
            printf("Exiting...\n");
        }
        else
        {
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    // Free memory and exit program
    freeArray(words, numWords);
    return 0;
}