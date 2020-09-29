#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class Application : public QApplication
{
    Q_OBJECT

public:
    // constructors
    Application(int &argc, char *argv[]);

    // event loop
    int run(void) const;

private:
};

#endif // APPLICATION_H
