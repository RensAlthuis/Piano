#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include "window.h"
#include "midireader.h"
#define WINDOWS
#ifdef UNIX
    #include "pianointerface_unix.h"
#endif
#ifdef WINDOWS
    #include "pianointerface_win.h"
#endif


class MainScreen : public QWidget
{
    Q_OBJECT
public:
    MainScreen(QWidget* parent = 0);
    ~MainScreen();

private:
    QGridLayout* layout;
    Window* window;
    QWidget* windowContainer;
    PianoInterface* piano;
    QPushButton* button;
    QPushButton* button2;
    QWidget* dummy;
    MidiReader* midiReader;


protected:
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private slots:
    void slotButton1();
    void slotButton2();

signals:
    void keyPressed(int note, int vol);
    void pedalKeyPressed(bool x);


};

#endif // MAINSCREEN_H
