#include "midireader.h"

MidiReader::MidiReader()
    : running(true),
      lastEventIndex(0),
      tempo(600000)
{

}

void MidiReader::loadFile(const char* fileName){

   int n = file.read(fileName);
   qDebug() << n;
   file.deltaTicks();
   file.joinTracks();
   qDebug() << file.getTicksPerQuarterNote();
}

void MidiReader::stop(){
    running = false;
}

void MidiReader::run(){
    MidiEvent e;
    while(running){
        lastEventIndex++;
        e = file.getEvent(0, lastEventIndex);
        unsigned long deltaTime = ((unsigned long) e.tick * tempo );
        if (e.isNoteOn()){
            emit playNote(e.getKeyNumber(), e.getVelocity());
            qDebug() << "Deltatime:" << deltaTime / 1000000 << "\tNOTE ON:" << e.getKeyNumber();
        }else if (e.isNoteOff()){
            emit playNote(e.getKeyNumber(), 0);
            qDebug() << "Deltatime:" << deltaTime / 1000000 << "\tNOTE OFF:" << e.getKeyNumber();
        }else if (e.isTempo()){
            tempo = e.getTempoMicro() / file.getTicksPerQuarterNote();
            qDebug() << "Deltatime:" << deltaTime / 1000000 << "\tTEMPO:" << tempo;
            deltaTime = 0;
        }else{
            qDebug() << "NOT IMPLEMENTED:" << e.getCommandByte() << e.data();
        }
        QThread::usleep(deltaTime);

    }
}

void MidiReader::increaseTempo(int n){
    //ticksPerSecond = std::min((unsigned long) 2000, ticksPerSecond + n);
}

void MidiReader::decreaseTempo(int n){
    //ticksPerSecond = std::max((unsigned long) 100, ticksPerSecond - n);
}
