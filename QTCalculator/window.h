#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "action.h"

class Window : public QWidget
{
    Q_OBJECT

   private:
    action* actionObject;
public:
    explicit Window(QWidget *parent = nullptr);

signals:

};

#endif // WINDOW_H
