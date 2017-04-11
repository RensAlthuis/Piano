#include "pianointerface_unix.h"

PianoInterface::PianoInterface()
{
    dev = open( "/dev/midi2", O_RDWR | O_NOCTTY | O_NONBLOCK | O_NDELAY);

    if (dev < 0){
        qDebug() << "input not opened";
        running = false;
    }
    else{
        running = true;
    }
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
    char writeBuf[3];
    writeBuf[0] = NOTE;
    writeBuf[1] = note;
    writeBuf[2] = vol;
    write(dev, writeBuf, sizeof(writeBuf));
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
        memset (buf, '\0', 16);
        int e = read(dev, buf, 16);

        if (e >= 0){
            if ( buf[0] == TIMING ){

            }else if ( buf[0] == ACTIVE_SENSE ){

            }
            else if ( buf[0] == NOTE ){
                //cout << "Note: " << (int) buf[1];
                //cout << " Vol: " << (int) buf[2] << endl;
                emit note((int)buf[1],(int)buf[2]);
            }
            else if ( buf[0] == PEDAL){
                //cout << "Pedal: ";
                //cout << (int) buf[2] << endl;
                if((int)buf[2] == 0){
                    emit pedal(false);
                }
                else{
                    emit pedal(true);
                }
            }
            if(buf[3] == NOTE){
                emit note((int)buf[4],(int)buf[5]);
            }
            if(buf[6] == NOTE){
                emit note((int)buf[7],(int)buf[8]);
            }
        }
}

void PianoInterface::writeToDev(){
    mutex.lock();
    if (nextEvent[0] != 0){
        write(dev,nextEvent, 4);
        memset(nextEvent, 0, 4);
    }
    mutex.unlock();
}
