/* 
 * File:   QECounter.h
 * Author: Manolito Ramirez
 *
 * Created on March 6, 2020, 9:34 PM
 */
int counter = 0;
void counter_increment(){
    counter++;
}

int counter_get(){
    int hold = counter;
    counter = 0;
    return hold;
}
