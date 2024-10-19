#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ctnspace(char p[], char s[]) { //Function that counts the number of digits in the string
    char* spf;
    spf = strtok (p,s); //Pointer to the first element of string (String in this case is \
    a digit separated from the whole string by " "
    int ctn = 0;
    while (spf != NULL) {
        spf = strtok (NULL,s); //Update the pointer to the first element of another string (String in this case is a next digit\
        separated from the whole string by " "
        ctn++; //Counting how many times pointer was updated, and it will be number of digits
    }
    return ctn;//Returning it
}


int InPower(int sys, int queue) { //Function that raises a number to a certain power
    int res = 1;
    while (queue > 0) {
        res *= sys;
        --queue;
    }
    return res; //Returning the result
}


int calculate(const int sys,const char* arr){ //Function that converts numbers from a given numeral system to decimal
    int sum = 0;
    if (arr[strlen(arr)-1] == '\n') { //Check if there is '\n' in the end of digits, cause if it is, program \
        think that it contains not, for example, 5 digits, but 6
        for (int i = 0; i<strlen(arr)-1; i++){
            if (arr[i] >= '0' && arr[i] <= '9') {
                sum += (arr[i] - '0') * InPower(sys,strlen(arr)-2-i); //Using ASCII to translate digits from char to int
            }
            if (arr[i] >= 'A' && arr[i] <= 'F') {
                sum += (arr[i] - 'A' + 10) * InPower(sys,strlen(arr)-2-i); //Using ASCII to translate digits from char to int
            }
        }
    }
    else {
        for (int i = 0; i<strlen(arr); i++){
            if (arr[i] >= '0' && arr[i] <= '9') {
                sum += (arr[i] - '0') * InPower(sys,strlen(arr)-1-i); //Using ASCII to translate digits from char to int
            }
            if (arr[i] >= 'A' && arr[i] <= 'F') {
                sum += (arr[i] - 'A' + 10) * InPower(sys,strlen(arr)-1-i); //Using ASCII to translate digits from char to int
            }
        }
    }
    return sum; //Returning the number in decimal
}

int main() {
    FILE *finp = fopen("input.txt", "r"); //Opening input.txt and output.txt
    FILE *foup = fopen("output.txt", "w");
    char sep[10] = " "; //Symbol that will separate our string in ctnspaces()
    char *sep_part; //Pointer that will point to the first element of string (separated from the whole string by " ")

    char FirstLine[100]; //String that will contain the first line
    fgets(FirstLine, 100, finp); //Writing from the first line in input.txt to FirstLine string
    int const amount = strtol(FirstLine, NULL, 10); //Converting string to int by using strtol()
    if (40 < amount || amount < 1) { //Checking if it lower than 40 and greater than 0
        fputs("Invalid inputs\n", foup); //If it's not print "Invalid inputs\n" and stop the program
        fclose(foup);
        fclose(finp);
        return 0;
    }

    char SecondLine[10000];//String that will contain the second line
    char SecondLine_copy1[10000]; //String that will contain the copy of second line
    char SecondLine_copy2[10000]; //String that will contain the copy of second line
    fgets(SecondLine, 10000, finp);//Writing from the first line in input.txt to SecondLine string
    strcpy(SecondLine_copy1, SecondLine); //Copying the SecondLine because we should use strtok() later, \
    but it's erasing the line after working
    strcpy(SecondLine_copy2, SecondLine);
    int numbersB = ctnspace(SecondLine_copy2, sep); //Counting the number of digits in the SecondLine

    char ThirdLine[10000];//String that will contain the third line
    char ThirdLine_copy[10000];//String that will contain the copy of third line
    fgets(ThirdLine, 10000, finp); //Writing from the third line in input.txt to ThirdLine string
    strcpy(ThirdLine_copy, ThirdLine); //Copying the SecondLine because we should use strtok() later, \
    but it's erasing the line after working
    int const numbersC = ctnspace(ThirdLine, sep); //Counting the number of digits in the ThirdLine
    int arr_3_line[numbersC]; //Array that will contain elements from ThirdLine

    char FourthLine[10000]; //String that will contain the fourth line
    fgets(FourthLine, 10000, finp); //Writing from the fourth line in input.txt to FourthLine string
    if (FourthLine[0] != '\0') { //Checking if there is '\0'
        fputs("Invalid inputs\n", foup);
        fclose(foup);
        fclose(finp);
        return 0;
    }

    sep_part = strtok (ThirdLine_copy,sep);//Pointer to the first element of string (String in this case is \
    a digit separated from the whole string by " "
    for (int i = 0; i < numbersC; i++) {
        if (strtol(sep_part, NULL, 10) == 2 || strtol(sep_part, NULL, 10) == 8 || strtol(sep_part, NULL, 10) == 16 \
            || strtol(sep_part, NULL, 10) == 10 ) { //Checking that the ThirdLine contains only 2, 8, 10, 16
            arr_3_line[i] = strtol(sep_part, NULL, 10); //Write the integers to the array by using strtol()
        }
        else {
            fputs("Invalid inputs\n", foup);
            fclose(foup);
            fclose(finp);
            return 0;
        }
        sep_part = strtok (NULL,sep); //Update the pointer to the first element of another string (String in this case is a next digit\
        separated from the whole string by " "
    }

    if (numbersB != amount || numbersC != amount) { //Checking that number of digits in the SecondLine equal to \
        number of digits in the ThirdLine and they equal to the N in the first line
        fputs("Invalid inputs\n", foup);
        fclose(foup);
        fclose(finp);
        return 0;
    }

    sep_part = strtok (SecondLine,sep);//Pointer to the first element of string (String in this case is \
    a digit separated from the whole string by " "
    for (int i = 0; i < numbersB; i++) { //Checking that digits in the SecondLine contains only symbols that \
        can be in their numeral system
        for (int j = 0; j < strlen(sep_part); j++) {
            if (strlen(sep_part) > 6 && sep_part[6] != '\n') {//Checking that each number in the SecondLine contains no more than 6 digit\
                and also check if there is '\n' cause program thinks that it is a digit too
                fputs("Invalid inputs\n", foup);
                fclose(foup);
                fclose(finp);
                return 0;
            }
            if (arr_3_line[i] == 2) {
                if ((sep_part[j] - '0' > 1 || sep_part[j] - '0' < 0) && (sep_part[j] != '\n')  && (sep_part[j] != '\0'))  { //Using ASCII
                    fputs("Invalid inputs\n", foup);
                    fclose(foup);
                    fclose(finp);
                    return 0;
                }
            }

            if (arr_3_line[i] == 8) {
                if ((sep_part[j] - '0' > 7 || sep_part[j] - '0' < 0) && (sep_part[j] != '\n') && (sep_part[j] != '\0'))  { //Using ASCII
                    fputs("Invalid inputs\n", foup);
                    fclose(foup);
                    fclose(finp);
                    return 0;
                }
            }

            if (arr_3_line[i] == 10) {
                if ((sep_part[j] - '0' > 9 || sep_part[j] - '0' < 0) && (sep_part[j] != '\n')  && (sep_part[j] != '\0'))  { //Using ASCII
                    fputs("Invalid inputs\n", foup);
                    fclose(foup);
                    fclose(finp);
                    return 0;
                }
            }

            if (arr_3_line[i] == 16) {
                if ((sep_part[j] - '0' > 9 || sep_part[j] - '0' < 0) && (sep_part[j] - 'A' + 10 < 9 || sep_part[j] - 'A' + 10 > 15) \
                    && (sep_part[j] != '\n') && (sep_part[j] != '\0'))  { //Using ASCII
                    fputs("Invalid inputs\n", foup);
                    fclose(foup);
                    fclose(finp);
                    return 0;
                    }
            }

        }
        sep_part = strtok (NULL,sep);//Update the pointer to the first element of another string (String in this case is a next digit\
        separated from the whole string by " "
    }

    sep_part = strtok (SecondLine_copy1,sep);//Pointer to the first element of string (String in this case is \
    a digit separated from the whole string by " "
    int summa = 0; //Int that will contain the sum of numbers in the SecondLine
    for (int i = 0; i < amount; i++) { //Loop that converts every number int the SecondLine to decimal
        if (i%2 == 0) {
            summa += calculate(arr_3_line[i], sep_part) - 10; //Writing the result to int summa
        }
        if (i%2 != 0) {
            summa += calculate(arr_3_line[i], sep_part) + 10; //Writing the result to int summa
        }
        sep_part = strtok (NULL,sep);//Update the pointer to the first element of another string (String in this case is a next digit\
        separated from the whole string by " "
    }

    fprintf(foup,"%d\n",summa); //Printing the summa to the output.txt

    fclose(foup); //Closing the Files
    fclose(finp); //Closing the Files
    return 0;
}