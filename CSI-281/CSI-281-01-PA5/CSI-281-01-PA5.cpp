/*
Author: William Box
Class: CSI-281-01
Assignment: PA 4
Date Assigned: Sept 27
Due Date: Nov 11th 11:59 PM
Description:

Main file used to test the binary search algorithm with doubly-linked lists

Certification of Authenticity:
I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the definition and
consequences of plagiarism and acknowledge that the assessor of this assignment
may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of academic staff;
and/or
- Communicate a copy of this assignment to a plagiarism checking service (which may
then retain a copy of this assignment on its database for the purpose of future
plagiarism checking)
*/

#include <iostream>
#include <fstream>
#include "doublyLinkedList.h"
#include "functions.h"
#include "timer system/timerSystem.h"

int main()
{
    std::string filename = "Test_Results.csv";
    DoublyLinkedList<int> list;
    int listLength = 10000;
    double sum,tmp;
    TimerSystem timer;

    std::ofstream output(filename);

    output << "type,time,run\n";

    timer.startClock();
    while (list.getCount() < listLength)
    {
        list.insert(wb::getRandomNumber());
    }
    std::cout << "It took " << timer.getTime() << " seconds to load " << listLength << " ints into the linked-list" << std::endl;

    output << "Early, Target, N/A\n";
    //early search
    sum = 0;
    for (int i = 0; i < 10; i++)
    {
        int target = list.getData(i);
        timer.startClock();
        list.isExistBinary(target);
        tmp = timer.getTime();
        output << "binary," << tmp << "," << i << "\n";
        sum += tmp;
    }
    output << "average," << sum / 10 << tmp << ", N/A" << "\n";
    
    sum = 0;
    for (int i = 0; i < 10; i++)
    {
        int target = list.getData(i);
        timer.startClock();
        list.isExist(target);
        tmp = timer.getTime();
        output << "normal," << tmp << "," << i << "\n";
        sum += tmp;
    }
    output << "average," << sum / 10 << tmp << ", N/A" << "\n";

    output << "Late, Target\n";
    //end search
    sum = 0;
    for (int i = 990; i < 1000; i++)
    {
        int target = list.getData(i);
        timer.startClock();
        list.isExistBinary(target);
        tmp = timer.getTime();
        output << "binary," << tmp << "," << i << "\n";
        sum += tmp;
    }
    output << "average," << sum / 10 << tmp << ", N/A" << "\n";

    sum = 0;
    for (int i = 990; i < 1000; i++)
    {
        int target = list.getData(i);
        timer.startClock();
        list.isExist(target);
        tmp = timer.getTime();
        output << "normal," << tmp << "," << i << "\n";
        sum += tmp;
    }
    output << "average," << sum / 10 << tmp << ", N/A" << "\n";

    output << "Mid, Target\n";
    //mid search
    sum = 0;
    for (int i = 495; i < 505; i++)
    {
        int target = list.getData(i);
        timer.startClock();
        list.isExistBinary(target);
        tmp = timer.getTime();
        output << "binary," << tmp << "," << i << "\n";
        sum += tmp;
    }
    output << "average," << sum / 10 << tmp << ", N/A" << "\n";

    sum = 0;
    for (int i = 495; i < 505; i++)
    {
        int target = list.getData(i);
        timer.startClock();
        list.isExist(target);
        tmp = timer.getTime();
        output << "normal," << tmp << "," << i << "\n";
        sum += tmp;
    }
    output << "average," << sum / 10 << "\n";

    output << "OOB, Target\n";
    //not in list
    int notInList[] = {-5,-4,-3,-2,-1,10001,10002,10003,10004,10005};
    sum = 0;
    for (int i = 0; i < 10; i++)
    {
        int target = notInList[i];
        timer.startClock();
        list.isExistBinary(target);
        tmp = timer.getTime();
        output << "binary," << tmp << "," << i << "\n";
        sum += tmp;
    }
    output << "average," << sum / 10 << tmp << ", N/A" << "\n";

    sum = 0;
    for (int i = 0; i < 10; i++)
    {
        int target = notInList[i];
        timer.startClock();
        list.isExist(target);
        tmp = timer.getTime();
        output << "normal," << tmp << "," << i << "\n";
        sum += tmp;
    }
    output << "average," << sum / 10 << tmp << ", N/A" << "\n";
}