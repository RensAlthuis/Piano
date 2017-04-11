#include "pianointerface_win.h"

PianoInterface::PianoInterface()
{

}

void PianoInterface::stop(){
    running = false;
}

void PianoInterface::setNextEvent(char* event){
   lastEventIndex++;
   mutex.lock();
   memcpy(nextEvent, event, 4);
   mutex.unlock();

}

void PianoInterface::playNote(int note, int vol){

}


void PianoInterface::run(){


    char buf [16];
    while (running){
        readFromDev(buf);
        writeToDev();
    }
    return;
}

void PianoInterface::readFromDev(char* buf){

}

void PianoInterface::writeToDev(){

}
