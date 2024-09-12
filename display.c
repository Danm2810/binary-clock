#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "sense.h"
#include "display.h"

#define WHITE 0xFFFF
#define BLACK 0x0000
#define RED 0XF000
#define GREEN 0x0F00
#define BLUE 0x00F0

pi_framebuffer_t *fb;
sense_fb_bitmap_t *bm;

void clear(void){

clearFrameBuffer(fb, BLACK);
}

void convertToBinary(int num[], int decimal){


        for(int i=7; i>=0; i--){
                int currentNumPlace = pow(2,i);
                //ease of use constant var

                if(decimal - currentNumPlace >= 0){
                        decimal = decimal - currentNumPlace;
                        num[i] = 1;
                }else{
                        num[i] = 0;
                }

        }
}

int open_display(void){

fb=getFrameBuffer();
bm = fb->bitmap;
        return 0;
}

void display_time(int hours, int minutes, int seconds){
/*
displays the time
*/
        display_colons();
        display_hours(hours);
        display_minutes(minutes);
        display_seconds(seconds);
}

void display_colons(void){
/*
displays the colons of the clock
*/
bm->pixel[5][1]=WHITE;
bm->pixel[5][2]=WHITE;
bm->pixel[5][5]=WHITE;
bm->pixel[5][6]=WHITE;

bm->pixel[4][1]=WHITE;
bm->pixel[4][2]=WHITE;
bm->pixel[4][5]=WHITE;
bm->pixel[4][6]=WHITE;

bm->pixel[2][1]=WHITE;
bm->pixel[2][2]=WHITE;
bm->pixel[2][5]=WHITE;
bm->pixel[2][6]=WHITE;

bm->pixel[1][1]=WHITE;
bm->pixel[1][2]=WHITE;
bm->pixel[1][5]=WHITE;
bm->pixel[1][6]=WHITE;
}

void display_number(int color, int display){

        int displayVal[8];

        convertToBinary(displayVal, display);

        for(int i=0; i<8; i++){
                if(displayVal[i] == 1){
                        switch(color){
                                case 0:
                                        bm->pixel[6][7-i]=RED;
                                        break;

                                case 1:
                                        bm->pixel[3][7-i]=GREEN;
                                        break;

                                case 2:
                                        bm->pixel[0][7-i]=BLUE;
                                        break;
                        }

                }
        }
}

void display_hours(int hours){
/*
displays the hours of the clock
*/
        display_number(0, hours);
}

void display_minutes(int minutes){
/*
displays the minutes of the clock
*/
        display_number(1, minutes);
}

void display_seconds(int seconds){
/*
displays the seconds of the clock
*/
        display_number(2, seconds);
}

void close_display(void){
/*
closes the display
*/
        clearFrameBuffer(fb, BLACK);
        freeFrameBuffer(fb);
}
