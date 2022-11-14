/* ***       Author:  Wei Kian Chen
     *  Last Update:  November 1, 2022
     *        Class:  CSI-281
     *     Filename:  doublyLinkedList.h
     *
     *  Description:
     *      This class is template class for a doubly linked list
     *  
     *  Certification of Authenticity:
     *     I certify that this assignment is entirely my own work.
     **********************************************************************/

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>

using namespace std;

template <typename T>
class DoublyLinkedList
{
private:
   template <typename R>
   struct Node
   {
      R       mData;
      Node<R>* mNext, * mPrevious;

      /*      Pre:  None
       *     Post:  This object is initialized using default values
       *  Purpose:  To intialize date object
       **************************************************************/
      Node()
      {
         mData = R();
         mNext = NULL;
         mPrevious = NULL;
      }


      /*      Pre:  None
       *     Post:  This object is initialized using specified data
       *  Purpose:  To intialize date object
       *************************************************************/
      Node(R data)
      {
         mData = data;
         mNext = NULL;
         mPrevious = NULL;
      }
   };

   Node<T>* mHead, * mTail;
   int     mCount;

public:
   DoublyLinkedList();
   ~DoublyLinkedList();

   int  getCount();
   T    getData(int index);
   void setData(int index, T data);

   void clear();
   void display();
   void displayInReverse();
   void insert(T data);
   bool isEmpty();
   bool isExist(T searchKey);
   bool isExistBinary(T searchKey);
   bool remove(T searchKey);
   T    removeAt(int index);
};


/*      Pre:  None
 *     Post:  The next and previous pointers are initialized to NULL
 *  Purpose:  Default constructor
 ************************************************************************/
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
   mHead = NULL;
   mTail = NULL;
   mCount = 0;
}


template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
   clear();
}


/*      Pre:  The object is instantiated
 *     Post:  The number of nodes in the linked list is returned to the
 *            caller
 *  Purpose:  To retrieve the number of nodes in the list
 ************************************************************************/
template <typename T>
int DoublyLinkedList<T>::getCount()
{
   return mCount;
}


/*      Pre:  The list is instantiated and the index is valid
 *     Post:  The data in the specified index is returned to the caller
 *  Purpose:  To retrieve the specified nodes in the list
 ************************************************************************/
template <typename T>
T DoublyLinkedList<T>::getData(int index)
{
   int     i;
   Node<T>* tmp;

   tmp = mHead;
   for (i = 0; i < index; i++)
      tmp = tmp->mNext;

   return tmp->mData;
}


/*      Pre:  The list is instantiated, the index is valid and the data
 *            is available
 *     Post:  The data in the specified index is updated with the
 *            specified data
 *  Purpose:  To update the specified nodes in the list
 ************************************************************************/
template <typename T>
void DoublyLinkedList<T>::setData(int index, T data)
{
   removeAt(index);
   insert(data);
}


/*      Pre:  The list is instantiated
 *     Post:  All  nodes in the doubly linked list is deleted. mHead,
 *            mTail and mCount are reset
 *  Purpose:  To clear the entire doubly linked list
 ************************************************************************/
template <typename T>
void DoublyLinkedList<T>::clear()
{
   Node<T>* tmp, * toBeDeleted;

   tmp = mHead;

   // removing node by node
   while (tmp != NULL)
   {
      toBeDeleted = tmp;
      tmp = tmp->mNext;
      toBeDeleted->mNext = NULL;
      toBeDeleted->mPrevious = NULL;

      delete toBeDeleted;
   }

   // reinitialize the pointers
   mHead = NULL;
   mTail = NULL;
   mCount = 0;
}



/*      Pre:  The dummy node is instantiated
 *     Post:  The data of the nodes in the doubly linked list is
 *            displayed on the screen
 *  Purpose:  To display all data stored in the doubly linked list
 ************************************************************************/
template <typename T>
void DoublyLinkedList<T>::display()
{
   Node<T>* tmp;

   if (mHead == NULL)
   {
      cout << "The list is empty\n";
      return;
   }

   tmp = mHead;
   while (tmp != NULL)
   {
      cout << tmp->mData << " ";
      tmp = tmp->mNext;
   }
   cout << endl;
}


/*      Pre:  The dummy node is instantiated
 *     Post:  The data of the nodes in the doubly linked list is
 *            displayed on the screen in reverse order
 *  Purpose:  To display all data stored in the doubly linked list in
 *            reverse order
 ************************************************************************/
template <typename T>
void DoublyLinkedList<T>::displayInReverse()
{
}


/*      Pre:  The list is instantiated and the new value is available
 *     Post:  The new node is added onto the doubly linked list in
 *            ascending order.  For example, if the new data is B, then
 *            it must be added in between A and C
 *  Purpose:  To add a new node onto the doubly linked list.
 *              Duplication is not allowed
 ************************************************************************/
template <typename T>
void DoublyLinkedList<T>::insert(T data)
{
   Node<T> *newNode, *tmp, *oneBefore;

   newNode = new Node<T>(data);
   if (newNode != NULL)
   {
      // case 1: list is empty
      if (mHead == NULL)
      {
         mHead = newNode;
         mTail = newNode;

         mCount++;
      }
      // case 2: adding at head
      else if (mHead->mData > data)
      {
         mHead->mPrevious = newNode;
         newNode->mNext = mHead;

         mHead = newNode;
         mCount++;
      }

      // case 3: adding at tail
      else if (mTail->mData < data)
      {
         mTail->mNext = newNode;
         newNode->mPrevious = mTail;

         mTail = newNode;
         mCount++;
      }

      // case 4: adding in the middle
      else
      {
         tmp = mHead;
         oneBefore = mHead;

         while (tmp != NULL && tmp->mData < data)
         {
            oneBefore = tmp;
            tmp = tmp->mNext;
         }

         if (tmp->mData != data)
         {
            oneBefore->mNext = newNode;
            newNode->mPrevious = oneBefore;

            tmp->mPrevious = newNode;
            newNode->mNext = tmp;

            mCount++;
         }
         else
            delete newNode;
      }
   }
}


/*      Pre:  The list is instantiated and the new value is available
 *     Post:  Return true is the list is empty, otherwise false
 *  Purpose:  To determine if the doubly linked list is empty
 ************************************************************************/
template <typename T>
bool DoublyLinkedList<T>::isEmpty()
{
   return mCount == 0;
}


/*      Pre:  The list is instantiated and the searchkey is provided
 *     Post:  True is the given value exists in the doubly linked list, 
 *            otherwise false
 *  Purpose:  To validate if a given value exists in the doubly linked list
 *            using binary search
 ************************************************************************/
template <typename T>
bool DoublyLinkedList<T>::isExist(T searchKey)
{
    Node<T> *tmp;
    bool found = false;

    tmp = mHead;
    while (!found && tmp != NULL)
    {
        if (tmp->mData == searchKey) found = true;
        else tmp = tmp->mNext;
    }

    return found;
}


/*      Pre:  The dummy node is instantiated and the searchkey is provided
 *     Post:  True is the given value exists in the doubly linked list,
 *            otherwise false
 *  Purpose:  To validate if a given value exists in the doubly linked
 *            list using binary search
 ************************************************************************/
template <typename T>
bool DoublyLinkedList<T>::isExistBinary(T searchKey)
{
    
    int lowerBound = 0;
    int upperBound = getCount();
    int mid;

    bool found = false;

    while (lowerBound <= upperBound)
    {
        mid = (lowerBound + upperBound) / 2;

        T value = getData(mid);

        if (value == searchKey)
        {
            found = true;
            break;
        }
        else if (value > searchKey)
        {
            upperBound = mid - 1;
        }
        else
        {
            lowerBound = mid + 1;
        }
    }
    return found;
}


/*      Pre:  The list is instantiated and the searchkey is provided
 *     Post:  If the given searchKey exists in the doubly linked list, it is
 *            removed from the list
 *  Purpose:  To remove a given value from the doubly linked list
 ************************************************************************/
template <typename T>
bool DoublyLinkedList<T>::remove(T searchKey)
{
   Node<T> *tmp, *oneBefore;
   bool    deleted = false;

   if (mHead != NULL)
   {
      if (searchKey < mHead->mData); // beware of ;
      else if (searchKey > mTail->mData);  // beware of ;
      else if (searchKey == mHead->mData)
      {
         deleted = true;

         tmp = mHead;
         mHead = mHead->mNext;

         if (mHead == NULL)
            mTail = NULL;
         else
            mHead->mPrevious = NULL;

         tmp->mNext = NULL;

         delete tmp;
         mCount--;
      }
      else if (searchKey == mTail->mData)
      {
         deleted = true;

         tmp = mTail;
         mTail = mTail->mPrevious;
         mTail->mNext = NULL;

         tmp->mPrevious = NULL;
         delete tmp;
         mCount--;
      }
      else
      {
         tmp = mHead;
         oneBefore = mHead;

         while (tmp != NULL && tmp->mData != searchKey)
         {
            oneBefore = tmp;
            tmp = tmp->mNext;
         }

         if (tmp != NULL)
         {
            deleted = true;

            oneBefore->mNext = tmp->mNext;
            (tmp->mNext)->mPrevious = oneBefore;

            tmp->mNext = NULL;
            tmp->mPrevious = NULL;
            delete tmp;
            mCount--;
         }
      }
   }

   return deleted;
}

/*      Pre:  The list is instantiated and the index for the node to be deleted
 *            is provided.  The index starts at zero
 *     Post:  If the index is valid, the node at the specified index location is
 *            removed and mCount is adjust accordingly.  And, mHead and mTail 
 *            will be adjust when needed
 *  Purpose:  To remove a node at the specified index location within the 
 *            doubly linked list
 ************************************************************************/
template <typename T>
T DoublyLinkedList<T>::removeAt(int index)
{
   Node<T> *tmp, *oneBefore;
   T       data = T();
   int     i;

   if (index < 0 || index >= mCount)
      return data;

   for (i = 0, tmp = mHead; i < index; i++)
      tmp = tmp->mNext;

   data = tmp->mData;

   if (index == 0)
   {
      mHead = tmp->mNext;
      mHead->mPrevious = NULL;
   }
   else if (index == mCount - 1)
   {
      mTail = oneBefore;
      mTail->mNext = NULL;
   }
   else
   {
      oneBefore = tmp->mPrevious;
      oneBefore->mNext = tmp->mNext;
      (tmp->mNext)->mPrevious = oneBefore;
   }

   tmp->mNext = NULL;
   tmp->mPrevious = NULL;

   delete tmp;

   mCount--;

   return data;
}


#endif