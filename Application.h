#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include "GraphicWidget.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    Application(int &argc, char *argv[]);
    virtual ~Application();
    int run(void);
private:
    GraphicWidget*  p_graphicWidget;
    QWidget*        p_mainWindow;
};

#endif // APPLICATION_H
