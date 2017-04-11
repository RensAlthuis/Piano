#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <QtQuick>
#include <QTimer>
#include <math.h>

class Window : public QQuickView
{
    Q_OBJECT
public:
    explicit Window(QWindow *parent = 0);
    virtual void render(QPainter* painter);
    ~Window();
private:
    QBackingStore* bstore;
    QTimer time;
    int notes[88];
    int notesPedal[88];
    bool pedal;
    void drawKey(){

    }

public slots:
    void renderLater();
    void renderNow();
    void noteSwitch(int note = 60, int vol = 125);
    void pedalSwitch(bool x);
    void timeTick();

signals:
protected:
    bool event(QEvent* event) override;

    void resizeEvent(QResizeEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;
};

#endif // WINDOW_H
