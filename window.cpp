#include "window.h"


Window::Window(QWindow *parent)
:   QQuickView(parent)
{

    // Set up window
    create();
    bstore = new QBackingStore(this);

    for (int i = 0; i < 88; i++){
        notes[i] = 0;
        notesPedal[i] = 0;
    }
    pedal = false;


    // Fadeout timer on 20ms timeout
    QObject::connect(&time, SIGNAL(timeout()), this, SLOT(timeTick()));
    time.start(20);


}

Window::~Window(){

    time.stop();
}

void Window::exposeEvent(QExposeEvent * ){

    if(isExposed()){
        renderNow();
    }
}


void Window::resizeEvent(QResizeEvent * event){
    bstore->resize(event->size());
    if(isExposed()){
        renderNow();
    }
}

void Window::renderNow(){
    if(!isExposed()){
        return;
    }

    QRect rect(0,0, width(), height());
    bstore->beginPaint(rect);

    QPaintDevice* device = bstore->paintDevice();
    QPainter painter(device);

    painter.fillRect(rect, Qt::white);
    render(&painter);

    bstore->endPaint();
    bstore->flush(rect);
}

void Window::renderLater(){
    requestUpdate();
}

bool Window::event(QEvent* event){
    if(event->type() == QEvent::UpdateRequest){
        renderNow();
        return true;
    }

    return QWindow::event(event);
}


void Window::render(QPainter* painter){

    int w = width()/50;
    int n = 0;

    // WHITE KEYS
    for(int i = 0; i < 84; i++){
        QRect* rect;
        if (i%12 == 1 || i%12 == 3 || i%12 == 6 || i%12 == 8 || i%12 == 10){
            n++;
            continue;
        }else{
            rect = new QRect((w*i + 20 - n*w),50,w,150);
        }

        int col = 0;
        if(!pedal){
            col = std::max(255-(2*notes[i+3]),0);
        }else{
            col = std::max(255-(2*notesPedal[i+3]),0);
        }
        QBrush brush(QColor(col,col,col));
        painter->fillRect(*rect, brush);
        painter->drawRect(*rect);
    }

    n = 0;

    // BLACK KEYS
    for(int i = 0; i < 84; i++){
        QRect* rect;
        if (i%12 == 1 || i%12 == 3 || i%12 == 6 || i%12 == 8 || i%12 == 10){
            n++;
            rect = new QRect( (w*i + 20 + w/2 - n*w + 2) , 50, w - 4, 115);
        }else{
            continue;
        }

        int col = 0;
        if(!pedal){
            col = std::max(255-(2*notes[i+3]),0);
        }else{
            col = std::max(255-(2*notesPedal[i+3]),0);
        }
        QBrush brush(QColor(col,col,col));
        painter->fillRect(*rect, brush);
        painter->drawRect(*rect);
    }

    // PEDAL
    QRect rect(width()/2 - 50, height() - 40, 100, 20 );
    int col = (pedal ? 0 : 255);
    QBrush brush(QColor(col,col,col));
    painter->fillRect(rect, brush);
    painter->drawRect(rect);
}

void Window::timeTick(){
    for(int i = 0; i < 88; i++){
        notes[i] = std::max(notes[i] - 1, 0);
        notesPedal[i] = std::max(notesPedal[i] - 1, 0);
    }
    renderNow();
}

void Window::noteSwitch(int note, int vol){
        notes[note - 21] = vol*255/127;
        if (vol != 0){
            notesPedal[note -21] = vol*255/127;
        }
    renderNow();
}

void Window::pedalSwitch(bool x){
    pedal = x;
    if(pedal){
        for(int i = 0; i < 88; i++){
            notesPedal[i] = notes[i];
        }
    }
    qDebug() << "pedal: " << x;
}
