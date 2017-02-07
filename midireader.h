#ifndef MIDIREADER_H
#define MIDIREADER_H

#include "MidiFile.h"
#include "QDebug"
#include <QThread>
#include <math.h>

class MidiReader : public QThread
{
    Q_OBJECT
public:
    MidiReader();
    void run() override;
    void loadFile(const char* fileName);
    void stop();
    void increaseTempo(int n);
    void decreaseTempo(int n);

private:
    MidiFile file;
    int lastEventIndex;
    bool running;
    unsigned long tempo;

signals:
    void playNote(int note, int vol);


};

#endif // MIDIREADER_H
