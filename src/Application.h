#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "GraphicWidget.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char *argv[]);
    int run(void);
private:
};

#endif // APPLICATION_H
