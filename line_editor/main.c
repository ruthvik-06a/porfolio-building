#include <stdio.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 200

char lines[MAX_LINES][MAX_LENGTH];
int lineCount = 0;


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
    scanf("%d", &position);

    if (position < 1 || position > lineCount + 1)
    {
        printf("Invalid line number!\n");
        return;
    }

    getchar();

    printf("Enter text: ");
    fgets(text, MAX_LENGTH, stdin);

    text[strcspn(text, "\n")] = '\0';

    // Shift lines DOWN
    for (int i = lineCount; i >= position; i--)
    {
        strcpy(lines[i], lines[i - 1]);
    }

    // Insert the new text
    strcpy(lines[position - 1], text);

    lineCount++;

    printf("Line inserted successfully!\n");
}


void deleteLine()
{
    int position;

    if (lineCount == 0)
    {
        printf("Document is empty! Nothing to delete.\n");
        return;
    }

    printf("Enter line number to delete (1 to %d): ", lineCount);
    scanf("%d", &position);

    if (position < 1 || position > lineCount)
    {
        printf("Invalid line number!\n");
        return;
    }

    // Shift lines UP
    for (int i = position - 1; i < lineCount - 1; i++)
    {
        strcpy(lines[i], lines[i + 1]);
    }

    lineCount--;

    printf("Line deleted successfully!\n");
}


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


int main()
{
    int choice;

    while (1)
    {
        printf("\n===== LINE EDITOR =====\n");
        printf("1. Insert line\n");
        printf("2. Delete line\n");
        printf("3. Display document\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                insertLine();
                break;

            case 2:
                deleteLine();
                break;

            case 3:
                displayDocument();
                break;

            case 4:
                printf("Exiting Line Editor...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
