// CSI-281-01-PA5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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