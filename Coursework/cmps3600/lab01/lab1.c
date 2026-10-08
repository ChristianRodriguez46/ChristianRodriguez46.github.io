// Author: Christian ROdriguez
// lab-1.c
// Created date: 8/28/2025
// refactor lab1cpp to c
// #include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// #include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
// using namespace std;

int main()
{
    // cout << "Enter your name: ";
    write(1, "Enter your name: ", 17);
    char name[100];
    // cin >> name;
    read(0, name, 100);
    
    // cout << "Enter your number: ";
    write(1, "Enter a number: ", 16);
    // cin >> number;
    int number;
    char buff[16];
    read(0, buff, 16);
    number = atoi(buff);

    // ofstream fout("log");
    int fd = open("log", O_CREAT|O_RDWR|O_TRUNC, S_IRUSR | S_IWUSR);

    // if (fout.fail()) {
    //     cerr << "ERROR: opening output file." << endl;
    //     exit(0);
    // }
    if (fd == -1) {
        write (1, "ERROR: opening output file.\n", 28);
        exit(0);
    }
    // fout << name << endl;
    write(fd,name,strlen(name));
    write(fd,"\n",1);
    
    int sum;
    for (int i=1; i <= number; ++i)
        sum += i;
    // fout << "summation from 1 to " << number << " is " << sum << endl;
    char ts[200];
    sprintf(ts, "summation from 1 to %i is %i\n", number, sum);
    write(fd,ts,strlen(ts));
    // fout.close();
    close(fd);
    return 0;
}
