// Hasan Kuspinar
#include <iostream>
#include "Board.h"
#include <string>

using namespace std;

Board::Board() // default constructor
{
    head = NULL;
    tail = NULL;
    xCnt = 0;
    oCnt = 0;
}

bool Board::noMove(char ch, int step) // checks if there is a possible valid move or not
{
    slot * ptr1 = head;
    int count;
    int start = 0;
    char ch1;
    char ch2;
    char ch3;
    while(ptr1 != NULL)
    {
        if(ptr1->slotStack.isEmpty()==false) // if the start one is not empty checks whether the target is empty or has the same ch
        {
            ptr1->slotStack.pop(ch1);
            ptr1->slotStack.push(ch1);
            if(ch1 == ch)
            {
                count = 0;
                slot * ptr = head;
                while (ptr != NULL)
                {
                    if (count == (start + step))
                    {
                        if (ptr->slotStack.isEmpty())
                        {
                            return false;
                        }
                        else
                        {
                            ptr->slotStack.pop(ch2);
                            ptr->slotStack.push(ch2);
                            if (ch1 == ch2)
                            {
                                return false;
                            }
                        }
                    }
                    ptr = ptr->next;
                    count++;
                }
            }
        }
        else // if the start one is empty checks if the target has the ch
        {
            count = 0;
            slot * ptr2 = head;
            while (ptr2 != NULL)
            {
                if (count == (start + step))
                {
                    if(ptr2->slotStack.isEmpty()==false)
                    {
                        ptr2->slotStack.pop(ch3);
                        ptr2->slotStack.push(ch3);
                        if (ch == ch3)
                        {
                            return false;
                        }
                    }
                }
                ptr2 = ptr2->next;
                count++;
            }
        }
        ptr1 = ptr1->next;
        start++;
    }
    return true;
}

void Board::printBoard()
{
    int size = 0;
    slot * ptr = head;
    slot * ptr1 = head;
    while(ptr != NULL)
    {
        ptr = ptr->next;
        size++;
    }
    string container[size];
    int index = 0;
    while(ptr1 != NULL) // creating a string array containing the stacks of the board as strings
    {
        if(ptr1->slotStack.isEmpty())
        {
            container[index] = "    ";
        }
        else if(ptr1->slotStack.isFull())
        {
            char ch;
            ptr1->slotStack.pop(ch);
            ptr1->slotStack.push(ch);
            if(ch =='x')
            {
                container[index] = "xxxx";
            }
            else
            {
                container[index] = "oooo";
            }
        }
        else
        {
            int count = 0;
            char ch1;
            string s;
            while(!ptr1->slotStack.isEmpty())
            {
                ptr1->slotStack.pop(ch1);
                count++;
            }
            if(ch1 == 'x')
            {
                s = "x";
            }
            else
            {
                s = "o";
            }
            if(count == 1)
            {
                container[index] = "   " + s;
            }
            else if(count == 2)
            {
                container[index] = "  " + s + s;
            }
            else
            {
                container[index] = " " + s + s + s;
            }
            for(int i = 0; i < count; i++)
            {
                ptr1->slotStack.push(ch1);
            }
        }
        ptr1 = ptr1->next;
        index++;
    }
    for(int a = 0; a <= 4; a++) // iterating over the container to print the board
    {
        for(int b = 0; b < size; b++)
        {
            if(a == 4)
            {
                cout << "^";
            }
            else
            {
                cout << container[b][a];
            }
        }
        cout << endl;
    }
}

int Board::validMove(char ch, int start, int step, int direction) // checks if there is a valid move with the given source index character step and direction
{
    slot * ptr = head;
    slot * ptr2 = head;
    int count = 0;
    int target_index;
    if(direction == 1)
    {
        target_index = start + step;
    }
    else
    {
        target_index = start - step;
    }
    while(count <= start) // checking if the chosen index is within bounds
    {
        if (ptr == NULL)
        {
            return 1;
        }
        else
        {
            ptr = ptr->next;
            count++;
        }
    }
    if(start < 0)
    {
        return 1;
    }
    count = 0;
    slot * ptr4 = head;
    while(count != start)
    {
        ptr4 = ptr4->next;
        count++;
    }
    char ch2;
    if(!ptr4->slotStack.isEmpty()) // checking if the chosen index belongs to the player
    {
        ptr4->slotStack.pop(ch2);
        ptr4->slotStack.push(ch2);
        if (ch2 != ch)
        {
            return 4;
        }
    }
    else
    {
        return 4;
    }
    count = 0;
    while(count <= target_index) // checking if the target is within bounds
    {
        if(ptr2 == NULL)
        {
            return 2;
        }
        else
        {
            ptr2 = ptr2->next;
            count++;
        }
    }
    if(target_index < 0)
    {
        return 2;
    }
    count = 0;
    slot * ptr3 = head;
    while(count != target_index) // checking if the target belongs to player
    {
        ptr3 = ptr3->next;
        count++;
    }
    if(!ptr3->slotStack.isEmpty())
    {
        char ch1;
        ptr3->slotStack.pop(ch1);
        ptr3->slotStack.push(ch1);
        if(ch1 != ch)
        {
            return 3;
        }
    }
    return 0;
}

void Board::movePiece(int source, int target) // makes the move with the given source and target indices
{
    slot * ptr = head;
    slot * ptr2 = head;
    int count1 = 0;
    int count2 = 0;
    char ch;
    while(true)
    {
        if(count1 == source)
        {
            ptr->slotStack.pop(ch);
            break;
        }
        ptr = ptr->next;
        count1++;
    }
    while(true)
    {
        if(count2 == target)
        {
            ptr2->slotStack.push(ch);
            break;
        }
        ptr2 = ptr2->next;
        count2++;
    }
}

int Board::evaluateGame()
{
    if(xCnt < oCnt)
    {
        return 1;
    }
    else if(oCnt < xCnt)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

void Board::createSlotBegin(char ch, int num) // creates a slot containing a stack with num many x's or  o's in the head
{
    slot * ptr = new slot;
    for(int i = 0; i < num; i++) // appending num times ch to the slot
    {
        ptr->slotStack.push(ch);
        if(ch=='x')
        {
            xCnt++;
        }
        else
        {
            oCnt++;
        }
    }
    if(head == NULL) // adding the slot to beginning
    {
        head = ptr;
        tail = head;
        head->prev = NULL;
        head->next = NULL;
    }
    else
    {
        head->prev = ptr;
        ptr->next = head;
        ptr->prev = NULL;
        head = ptr;
    }
}

void Board::createSlotEnd(char ch, int num) // creates a slot containing a stack with num many x's or  o's in the tail
{
    slot * ptr = new slot;
    for(int i = 0; i < num; i++) // appending num times ch to the slot
    {
        ptr->slotStack.push(ch);
        if(ch=='x')
        {
            xCnt++;
        }
        else
        {
            oCnt++;
        }
    }
    if(tail == NULL) // adding the slot to end
    {
        ptr->next = NULL;
        ptr->prev = NULL;
        tail = ptr;
        head = tail;
    }
    else
    {
        ptr->next = NULL;
        ptr->prev = tail;
        tail->next = ptr;
        tail = ptr;
    }
}

void Board::createEmptySlotEnd() // creates an empty slot at the tail
{
    slot * ptr = new slot;
    if(tail == NULL)
    {
        ptr->next = NULL;
        ptr->prev = NULL;
        tail = ptr;
        head = tail;
    }
    else
    {
        ptr->next = NULL;
        ptr->prev = tail;
        tail->next = ptr;
        tail = ptr;
    }
}

void Board::clearBoard() // deletes the list (inspired from week 5 lab codes)
{
    slot * ptr;
    while(head != NULL)
    {
        ptr = head;
        head = head->next;
        delete ptr;
    }
    tail = NULL;
}

bool Board::targetSlotFull(int num) // checks if the slot with the given index is full
{
    slot * ptr = head;
    bool b2 = true;
    bool result;
    int count1 = 0;
    while(b2)
    {
        if(count1 == num) // searching the requested slot
        {
            if(ptr->slotStack.isFull())
            {
                result = true;
            }
            else
            {
                result = false;
            }
            b2 = false;
        }
        ptr = ptr->next;
        count1++;
    }
    return result;
}

void Board::destroySlot(int num) // destroys the slot with the given index
{
    slot * ptr = head;
    slot * deleted;
    int count = 0;
    bool b1 = true;
    while(b1)
    {
        if(count == num) // searching the requested slot
        {
            char ch;
            deleted = ptr;
            while(deleted->slotStack.isEmpty()==false)
            {
                deleted->slotStack.pop(ch);
                if(ch == 'x')
                {
                    xCnt--;
                }
                else
                {
                    oCnt--;
                }
            }
            if(ptr == head && ptr == tail) // checking if there head and tail are the same or NULL
            {
                delete deleted;
                head = NULL;
                tail = NULL;
            }
            else if(ptr == head)
            {
                ptr = ptr->next;
                delete deleted;
                head = ptr;
                head->prev = NULL;
            }
            else if(ptr == tail)
            {
                ptr = ptr->prev;
                delete deleted;
                tail = ptr;
                tail->next = NULL;
            }
            else
            {
                ptr = ptr->next;
                deleted->prev->next = ptr;
                ptr->prev = deleted->prev;
                delete deleted;
            }
            b1 = false;
        }
        ptr = ptr->next;
        count++;
    }
}