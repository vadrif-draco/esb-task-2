/*
PLAN:

We're detecting if braces or brackets are matching in a given string or not.

For every starting { or (, push it to the stack.
Then if you meet a } or ), pop the stack --> match?, proceed, otherwise break and print "Not Balanced".
If no mismatch occurs check the stack --> empty?, print "Balanced", otherwise print "Not Balanced".

Examples to test:

{1 + (2/5) + 2}
( 2 * 3 + (5/2+(4*3)))
( 2 * 3 + (5/2+(4*3))))
{({2+10}}*11}

*/

#include "typedefs.h"
#include <stdlib.h>
#include <stdio.h>

// Stack and its index, initialized at -1 to signal empty stack
int32_t top = -1;
uint8_t *stack;

// Boolean enum used for one of the functionalities of this program
enum boolean
{
    false = 0,
    true
} balanced;

// This function is responsible for pushing data to the stack
void push(uint8_t u8_data)
{
    // Initial check if stack is full
    if (top == INT32_MAX - 1)
    {
        printf("Error: Stack is full; cannot push.\n\n");
        return;
    }

    // Otherwise, proceed with pushing the data through:

    top++; // 1. Incrementing the top

    stack = realloc(stack, (top + 1) * sizeof(uint8_t)); // 2. Allocating memory for new stack

    stack[top] = u8_data; // 3. Saving the received data in the top slot
}

// This function is responsible for retrieving data from the stack
uint8_t pull()
{
    // Initial check if stack is empty
    if (top == -1)
    {
        printf("Error: Stack is empty; cannot pull.\n");
        return 0; // Returning 0 signifies that the stack is empty
    }

    // Otherwise, proceed with retrieving the data through:

    uint8_t temp = stack[top]; // 1. Store the data to be retrieved in a temporary variable

    top--; // 2. Decrement the top

    stack = realloc(stack, (top + 1) * sizeof(uint8_t)); // 3. Deallocate memory from stack

    return temp; // 4. Return the data that was temporarily stored
}

// This function is responsible for printing the data stored in the stack from top to bottom
void printStack()
{
    // If the stack is empty (indicated by top being -1)
    if (top == -1)
    {
        printf("Nothing to print, the stack is empty.\n");
    }

    // Otherwise, print the data (characters and their ASCII code)
    else
    {
        printf("[TOP OF THE STACK]\n");
        for (int i = top; i >= 0; i--)
            printf("%c [%d]\n", stack[i], stack[i]);
    }
}

// Main Function for manipulating stack content and handling program initial I/O
int8_t main()
{
    enum choice
    {
        Push = 1,
        Pull,
        Print,
        Balance,
        Exit
    } choice; // Choice enum to be used in selecting operation

    stack = malloc(0); // Stack initialization

    printf("The following operations are supported by this application:");
    printf("\n\t1) Push\n\t2) Pull\n\t3) Print Stack Contents\n\t4) Check Balance\n\t5) Exit\n\n");

    while (1)
    {
        printf("Please choose one of the supported operations: ");
        scanf(" %d", &choice);
        printf("\n");
        switch (choice)
        {
        case Push:
        {
            printf("Please, enter the data you'd like to push: ");

            uint8_t temp;
            scanf(" %c", &temp);
            push(temp);

            printf("\n");
            break;
        }
        case Pull:
        {
            uint8_t temp = pull();

            if (temp != 0) // i.e. if there was data in the stack to be pulled
                printf("Pulled: %c [%d]\n", temp, temp);

            printf("\n");
            break;
        }
        case Print:
        {
            printStack();

            printf("\n");
            break;
        }
        case Balance:
        {
            int32_t top_prev = top;
            balanced = true; // Initialized balanced state as true.

            // Prompting user
            printf("Please, enter the data you'd like to check: ");

            // Handling input
            uint8_t *input = calloc(1000, sizeof(uint8_t));
            scanf(" %[^\n]s", input);

            // Looping through each character of input (breaks once terminating character arrives)
            while (*input)
            {
                // If input is a starting brace or bracket...
                if (*input == '{' || *input == '(')
                {
                    push(*input); // Push it to the stack,
                    input++;      // increment the pointer to proceed to the next character,
                    continue;     // and skip the rest of the iteration.
                }

                // Otherwise, if it's a terminating brace...
                else if (*input == '}')
                {

                    // Not Balanced Check #1: Overflow
                    if (top <= top_prev)
                    {
                        balanced = false;
                        break;
                    }

                    // Not Balanced Check #2: Mismatch
                    else if (pull() != '{')
                    {
                        balanced = false;
                        break;
                    }
                }

                // Otherwise, if it's a terminating bracket...
                else if (*input == ')')
                {

                    // Not Balanced Check #1: Empty Stack
                    if (top <= top_prev)
                    {
                        balanced = false;
                        break;
                    }

                    // Not Balanced Check #2: Mismatch
                    else if (pull() != '(')
                    {
                        balanced = false;
                        break;
                    }
                }

                // Finally, increment the pointer to proceed to the next character
                input++;
            }

            // When done with the loop, we check two things:
            //
            // 1. If the stack is back to how it was beforehand, signifying all braces/brackets were closed
            // 2. If the balanced flag was not changed to false throughout the loop due to mismatch
            //
            // If both checks are true, then the input is balanced. Otherwise, it is not balanced.
            if (top == top_prev && balanced)
            {
                printf("\nBalanced\n");
            }
            else
            {
                printf("\nNot Balanced\n");
            }
            printf("\n");
            break;
        }
        case Exit:
        {
            return 0;
        }
        default:
            printf("Invalid input.\n");
        }
    }
}