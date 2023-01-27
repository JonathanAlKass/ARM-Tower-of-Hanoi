#include "mbed.h"
#include <iostream>
#include <type_traits>
#include <cmath>


#define BLINKING_RATE 300ms
#define MIN_SLICES 2
#define MAX_SLICES 10
// main() runs in its own thread in the OS


BusOut ledsFrom(PB_11, PB_15, PB_13);
BusOut ledsTo(PB_12, PB_1, PB_14);
BusOut amountLeds(PA_1, PA_4, PB_0, PC_1, PC_0, PC_10, PC_12, PA_13, PA_14, PA_15);

//                A     F     E      D     C     G     B
BusOut sevenDigit(PA_9, PA_8, PB_10, PB_4, PB_5, PB_3, PA_10);

DigitalIn modePin(PB_2);
DigitalIn amountPin(PC_5);
DigitalIn speedPin(PC_6);
DigitalIn startPin(PA_12);
int RecursiveCount = 0;

int progress = 0;

void sleep(int hundred_millis){ 
    for(int i = 0; i < hundred_millis; i++){
        ThisThread::sleep_for(100ms);
    }
}
int binary(int num){
    switch(num){
        case 0:
            return 0b0000000000;
        case 1:
            return 0b1000000000;
        case 2:
            return 0b1100000000;
        case 3:
            return 0b1110000000;
        case 4:
            return 0b1111000000;
        case 5:
            return 0b1111100000;
        case 6:
            return 0b1111110000;
        case 7:
            return 0b1111111000;
        case 8:
            return 0b1111111100;
        case 9:
            return 0b1111111110;
        case 10:
            return 0b1111111111;
    }
    return 0b0000000000;
}
int sevenDigitBinary(int num){
    switch(num){
        case 0:
            return 0b0000010;
        case 1:
            return 0b1111010;
        case 2:
            return 0b0100100;
        case 3:
            return 0b0110000;
        case 4:
            return 0b1011000;
        case 5:
            return 0b0010001;
        case 6:
            return 0b0000001;
        case 7:
            return 0b0111010;
        case 8:
            return 0b0000000;
        case 9:
            return 0b0010000;
    }

    return 0b000000;
}

double mapRange(double value, double leftMin, double leftMax, double rightMin, double rightMax) {
    double leftSpan = leftMax - leftMin;
    double rightSpan = rightMax - rightMin;

    double valueScaled = float(value - leftMin) / float(leftSpan);

    return rightMin + (valueScaled * rightSpan);
}
void printHanoi(int from, int to, int speed, double count) {
    ledsFrom = 0b000;
    ledsTo = 0b000;
    sleep(speed);

    switch(from){
        case 1:
            ledsFrom = 0b100;
            break;
        case 2:
            ledsFrom = 0b010;
            break;
        case 3:
            ledsFrom = 0b001;
            break;
    }
    sleep(speed);

    switch(to){
        case 1:
            ledsTo = 0b100;
            break;
        case 2:
            ledsTo = 0b010;
            break;
        case 3:
            ledsTo = 0b001;
            break;
    }
    sleep(speed);


    RecursiveCount ++;
    amountLeds = binary((int)round(mapRange(RecursiveCount, 0, count, 0, 10)));

}

void moveHanoi(int numSlabs, int from, int over, int to, int speed, double count) {
    

    if (numSlabs > 0) {

        moveHanoi(numSlabs-1, from, to, over, speed, count);

        printHanoi(from, to, speed, count);


        moveHanoi(numSlabs-1, over, from, to, speed, count);

    }

}

void ledOn(int index){
    switch(index){
        case 0: 
            ledsFrom = 0b100;
            ledsTo = 0b100;
            break;
        case 1: 
            ledsFrom = 0b010;
            ledsTo = 0b010;
            break;
        case 2: 
            ledsFrom = 0b001;
            ledsTo = 0b001;
            break;
    }
}
void ledOff(){
    ledsFrom = 0b000;
    ledsTo = 0b000;
}

int main() {
    while (true) {
        //singleplayer
        int amount = 2;
        int start = 0;
        int MOVEMENT_SPEED_INDEX = 0;
        int speeds[] = {20, 15, 10, 5, 3, 1};
        int MOVEMENT_SPEED = speeds[0];
        int mode = 0; //0: Singleplayer     1: Multiplayer


        //multiplayer
        int usercount = 2;
        int users[] = {0, 0, 0};
        int startmulti = 0;
        sleep(5);


        
        amountLeds = binary(0);
        while (start == 0) {


            if(mode == 0){ //singleplayer


                
                sevenDigit = sevenDigitBinary(MOVEMENT_SPEED_INDEX+1);
                if(amountPin == 1){
                    if(amount == 5){
                        sleep(20);
                        if(amountPin == 1){
                            amount++;
                        }
                    }else{
                        amount++;
                    }
                    if (amount > MAX_SLICES) {
                        amount = MIN_SLICES;
                    }
                }
                if(speedPin == 1){
                    MOVEMENT_SPEED_INDEX += 1;
                    if(MOVEMENT_SPEED_INDEX > 5){
                        MOVEMENT_SPEED_INDEX = 0;
                    }
                    MOVEMENT_SPEED = speeds[MOVEMENT_SPEED_INDEX];
                    sevenDigit = sevenDigitBinary(MOVEMENT_SPEED_INDEX+1);
                }



            }else if(mode == 1){ //multiplayer

                amountLeds = binary(0);

                if(speedPin == 1){
                    usercount += 1;
                    if(usercount > 3){
                        usercount = 2;
                    }
                    sevenDigit = sevenDigitBinary(usercount+1);
                }
            }
            
            if(startPin == 1){
                sleep(5);
                if(startPin == 1){
                    start = 1;
        
                }
            }

            if(modePin == 1){
                mode++;
                if(mode > 1){
                    mode = 0;
                }
            }
            
            amountLeds = binary(amount);

            sleep(4);

        }
        amountLeds = binary(0);

        


        if(mode == 0){
            for (int i = 0; i < 3; i++) { //starting
                ledsFrom = 0b000;
                ledsTo = 0b000;
                ThisThread::sleep_for(BLINKING_RATE);
                ledsFrom = 0b111;
                ledsTo = 0b111;
                ThisThread::sleep_for(BLINKING_RATE);
            }
            ledsFrom = 0b000;
            ledsTo = 0b000;
            ThisThread::sleep_for(BLINKING_RATE);


            int count = pow(2, amount);
            moveHanoi(amount, 1, 3, 2, MOVEMENT_SPEED, count);
            amountLeds = binary(10);


            for (int i = 0; i < 5; i++) { //ending
                ledsFrom = 0b000;
                ledsTo = 0b000;
                ThisThread::sleep_for(BLINKING_RATE);
                ledsFrom = 0b010;
                ledsTo = 0b010;
                ThisThread::sleep_for(BLINKING_RATE);
            }
            ledsFrom = 0b000;
            ledsTo = 0b000;
            amountLeds = binary(0);
            sevenDigit = sevenDigitBinary(0);
        }else if(mode == 1){
            for(int i = 0; i < usercount; i++){ //for every user
                while(startmulti == 0){
                    if(startPin == 1){ // start button
                        sleep(5);
                        if(startPin == 1){
                            startmulti = 1;
                        }
                    }
                }

                sleep(30);
                Timer timer;
                timer.start();
                ledOn(i);
                while(startPin == 0){
                    
                }
                timer.stop();
            
                users[i] = timer.elapsed_time().count();
                ledOff();
            }
            int winner = 0;
            if(users[0] != 0 && users[0] < users[1] && (users[0] < users[2] || users[2] == 0)) winner = 0;
            if(users[1] != 0 && users[1] < users[0] && (users[1] < users[2] || users[2] == 0)) winner = 1;
            if(users[2] != 0 && users[2] < users[0] && users[2] < users[1]) winner = 2;
            switch(winner){
                case 0: 
                    for (int i = 0; i < 3; i++) { //starting
                        ledsFrom = 0b000;
                        ledsTo = 0b000;
                        ThisThread::sleep_for(BLINKING_RATE);
                        ledsFrom = 0b100;
                        ledsTo = 0b100;
                        ThisThread::sleep_for(BLINKING_RATE);
                    }
                    break;
                case 1: 
                    for (int i = 0; i < 3; i++) { //starting
                        ledsFrom = 0b000;
                        ledsTo = 0b000;
                        ThisThread::sleep_for(BLINKING_RATE);
                        ledsFrom = 0b010;
                        ledsTo = 0b010;
                        ThisThread::sleep_for(BLINKING_RATE);
                    }
                    break;
                case 2: 
                    for (int i = 0; i < 3; i++) { //starting
                        ledsFrom = 0b000;
                        ledsTo = 0b000;
                        ThisThread::sleep_for(BLINKING_RATE);
                        ledsFrom = 0b001;
                        ledsTo = 0b001;
                        ThisThread::sleep_for(BLINKING_RATE);
                    }
                    break;
            }

            
        }
        

       

        ThisThread::sleep_for(5000ms);
    }
}
