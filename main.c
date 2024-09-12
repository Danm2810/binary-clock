#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "display.h"
#include "sense.h"
#include <stdbool.h>
#include <ctype.h>

bool isValidString(char word[]);

int main(void){
        open_display();
        bool isValid = true;
while(isValid){
        int hr = 0, min = 0, sec = 0;
        char time[11];

        scanf("%s", &time);
        clear();

        if(strlen(time)>9 || strlen(time)<5 || !(isValidString(time))){
                isValid = false;
        } else {
                int colonsPassed = 0;

                for(int i=0; i<strlen(time); i++){

                        if(!(time[i] == ':')){

                                switch(colonsPassed){
                                        case 0:
                                                if(time[i+1] == ':'){
                                                        hr += (time[i] - '0');
                                                } else {
                                                        hr += (time[i] - '0') * 10;
                                                }
                                        break;

                                        case 1:
                                                if(time[i+1] == ':'){
                            min += (time[i] - '0');
                                  } else {
                            min += (time[i] - '0') * 10;
                                      }
                                        break;

                                        case 2:
                                                if(i+1 == strlen(time)){
                                                        sec += (time[i] - '0');
                                                } else {
                                                        sec += (time[i] - '0') * 10;
                                                }
                                        break;
                                }
                        } else {
                                colonsPassed++;
                        }
                }
        }

        if(isValid){
                if(hr <= 23 && min <= 59 && sec <= 59){
                        display_time(hr, min, sec);
                } else {
                        isValid = false;
                }
        }
}
        close_display();

        return 0;
}

bool isValidString(char word[]){
        bool b = true;

        int colon = 0, num = 0, colon2 = 0;

        if(b){
                for(int i=0; i<strlen(word); i++){

                        if(word[i] == ':'){
                                colon++;
                                colon2++;
                                num = 0;
                        } else {
                                colon2 = 0;
                                num++;
                        }

                        if(num > 2 || isalpha(word[i]) || colon2 > 1){
                                b = false;
                                break;
                        }

                }

                if(b && colon != 2){
                        b = false;
                }
        }

        return b;
}
