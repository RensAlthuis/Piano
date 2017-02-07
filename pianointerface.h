#ifndef PIANOINTERFACE_H
#define PIANOINTERFACE_H

#include <QThread>
#include <QDebug>
#include <QMutex>

#include <cstring>
#include <iostream>
#include "unistd.h"
#include "fcntl.h"
#include <bitset>

class PianoInterface : public QThread
{
    Q_OBJECT
public:
    PianoInterface();
    void stop();
    void setNextEvent(char* event);
private:
    const char TIMING = 0b11111000;
    const char ACTIVE_SENSE = 0b11111110;
    const char NOTE = 0b10010000;
    const char PEDAL = 0b10110000;
    int dev;
    bool running;
    int lastEventIndex;
    QMutex mutex;
    char nextEvent[4];

    void run() override;
    void readFromDev(char* buf);
    void writeToDev();

signals:
    void note(int note, int vol);
    void pedal(bool x);
public slots:
    void playNote(int note, int vol);
};

#endif // PIANOINTERFACE_H
