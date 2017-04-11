#include "mainscreen.h"

MainScreen::MainScreen(QWidget* parent)
    :QWidget(parent)
{

    setFixedSize(1280,720);
    layout = new QGridLayout();
    window = new Window;

    windowContainer = QWidget::createWindowContainer(window);

    windowContainer->setFixedHeight(250);
    windowContainer->setFocusPolicy(Qt::NoFocus);

    button = new QPushButton("increase tempo", this);
    button->setFocusPolicy(Qt::NoFocus);

    button2 = new QPushButton("decrease tempo", this);
    button2->setFocusPolicy(Qt::NoFocus);
    dummy = new QWidget(this);
    dummy->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QObject::connect(button, SIGNAL(released()), this, SLOT(slotButton1()));
    QObject::connect(button2, SIGNAL(released()), this, SLOT(slotButton2()));

    layout->addWidget(windowContainer, 3, 0);
    layout->addWidget(button, 0, 0);
    layout->addWidget(button2, 1, 0);
    layout->addWidget(dummy, 2, 0);

    setLayout(layout);

    piano = new PianoInterface();

    //Window Signals
    QObject::connect(this, SIGNAL(keyPressed(int,int)), window, SLOT(noteSwitch(int,int)));
    QObject::connect(this, SIGNAL(pedalKeyPressed(bool)), window, SLOT(pedalSwitch(bool)));

    //PainInterface Signals;
    QObject::connect(this, SIGNAL(keyPressed(int,int)), piano, SLOT(playNote(int,int)));
    QObject::connect(piano, SIGNAL(note(int,int)), window, SLOT(noteSwitch(int,int)));
    QObject::connect(piano, SIGNAL(pedal(bool)), window, SLOT(pedalSwitch(bool)));

    piano->start();

    midiReader = new MidiReader();
    QObject::connect(midiReader, SIGNAL(playNote(int,int)), piano, SLOT(playNote(int,int)));
    QObject::connect(midiReader, SIGNAL(playNote(int,int)), window, SLOT(noteSwitch(int,int)));
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open"),"/home/rens/Music/MidiFiles", tr("midi files (*.mid *.midi)"));
    qDebug() << fileName;
    string fileNamestr = fileName.toStdString();
    midiReader->loadFile(fileNamestr.c_str());
    midiReader->start();
}


MainScreen::~MainScreen(){
    piano->stop();
}

void MainScreen::keyPressEvent(QKeyEvent *event){
    if (!event->isAutoRepeat()){
        if (event->key() == Qt::Key_A){
            emit keyPressed(60, 60);
        }
        if (event->key() == Qt::Key_S){
            emit keyPressed(62, 60);
        }
        if (event->key() == Qt::Key_D){
            emit keyPressed(64, 60);
        }
        if (event->key() == Qt::Key_F){
            emit keyPressed(65, 60);
        }
        if (event->key() == Qt::Key_Space){
            emit pedalKeyPressed(true);
        }
    }
}

void MainScreen::keyReleaseEvent(QKeyEvent *event){
    if (!event->isAutoRepeat()){
        if (event->key() == Qt::Key_A){
            emit keyPressed(60, 0);
        }
        if (event->key() == Qt::Key_S){
            emit keyPressed(62, 0);
        }
        if (event->key() == Qt::Key_D){
            emit keyPressed(64, 0);
        }
        if (event->key() == Qt::Key_F){
            emit keyPressed(65, 0);
        }
        if (event->key() == Qt::Key_Space){
            emit pedalKeyPressed(false);
        }
    }
}

void MainScreen::slotButton1(){
    midiReader->increaseTempo(10);
}

void MainScreen::slotButton2(){
    midiReader->decreaseTempo(10);
}
