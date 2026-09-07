#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 200

char lines[MAX_LINES][MAX_LENGTH];
int lineCount = 0;


/* INSERT A LINE */
void insertLine()
{
    int position;
    char text[MAX_LENGTH];

    if (lineCount == MAX_LINES)
    {
        printf("Document is full!\n");
        return;
    }

    printf("Enter line number (1 to %d): ", lineCount + 1);

    if (scanf("%d", &position) != 1)
    {
        printf("Invalid line number! Please enter a number.\n");

        while (getchar() != '\n');

        return;
    }

    if (position < 1 || position > lineCount + 1)
    {
        printf("Invalid line number!\n");
        return;
    }

    getchar();

    printf("Enter text: ");
    fgets(text, MAX_LENGTH, stdin);

    text[strcspn(text, "\n")] = '\0';

    /* Shift lines DOWN */
    for (int i = lineCount; i >= position; i--)
    {
        strcpy(lines[i], lines[i - 1]);
    }

    /* Insert new line */
    strcpy(lines[position - 1], text);

    lineCount++;

    printf("Line inserted successfully!\n");
}


/* DELETE A LINE */
void deleteLine()
{
    int position;

    if (lineCount == 0)
    {
        printf("Document is empty! Nothing to delete.\n");
        return;
    }

    printf("Enter line number to delete (1 to %d): ", lineCount);

    if (scanf("%d", &position) != 1)
    {
        printf("Invalid line number! Please enter a number.\n");

        while (getchar() != '\n');

        return;
    }

    if (position < 1 || position > lineCount)
    {
        printf("Invalid line number!\n");
        return;
    }

    /* Shift lines UP */
    for (int i = position - 1; i < lineCount - 1; i++)
    {
        strcpy(lines[i], lines[i + 1]);
    }

    lineCount--;

    printf("Line deleted successfully!\n");
}


/* DISPLAY DOCUMENT */
void displayDocument()
{
    if (lineCount == 0)
    {
        printf("\nDocument is empty!\n");
        return;
    }

    printf("\n----- DOCUMENT -----\n");

    for (int i = 0; i < lineCount; i++)
    {
        printf("%d: %s\n", i + 1, lines[i]);
    }

    printf("--------------------\n");
}


/* SEARCH TEXT */
void searchText()
{
    char word[MAX_LENGTH];
    int found = 0;

    getchar();

    printf("Enter word or phrase to search: ");
    fgets(word, MAX_LENGTH, stdin);

    word[strcspn(word, "\n")] = '\0';

    for (int i = 0; i < lineCount; i++)
    {
        if (strstr(lines[i], word) != NULL)
        {
            printf("Found in line %d: %s\n", i + 1, lines[i]);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Word or phrase not found.\n");
    }
}


/* COUNT LINES AND WORDS */
void countWords()
{
    int totalWords = 0;

    for (int i = 0; i < lineCount; i++)
    {
        char temp[MAX_LENGTH];

        strcpy(temp, lines[i]);

        char *word = strtok(temp, " \t\n");

        while (word != NULL)
        {
            totalWords++;
            word = strtok(NULL, " \t\n");
        }
    }

    printf("Number of lines: %d\n", lineCount);
    printf("Number of words: %d\n", totalWords);
}


/* MAIN PROGRAM */
int main()
{
    char command[20];

    printf("===== LINE EDITOR =====\n");
    printf("Type 'help' to see available commands.\n");

    while (1)
    {
        printf("\n> ");

        scanf("%19s", command);

        if (strcmp(command, "insert") == 0)
        {
            insertLine();
        }
        else if (strcmp(command, "delete") == 0)
        {
            deleteLine();
        }
        else if (strcmp(command, "display") == 0)
        {
            displayDocument();
        }
        else if (strcmp(command, "search") == 0)
        {
            searchText();
        }
        else if (strcmp(command, "count") == 0)
        {
            countWords();
        }
        else if (strcmp(command, "help") == 0)
        {
            printf("\nAvailable commands:\n");
            printf("insert  - Insert a new line\n");
            printf("delete  - Delete a line\n");
            printf("display - Display the document\n");
            printf("search  - Search for a word or phrase\n");
            printf("count   - Count lines and words\n");
            printf("quit    - Exit the editor\n");
        }
        else if (strcmp(command, "quit") == 0)
        {
            printf("Exiting Line Editor...\n");
            break;
        }
        else
        {
            printf("Unknown command! Type 'help' for available commands.\n");
        }
    }

    return 0;
}
