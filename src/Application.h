#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class Application : public QApplication
{
    Q_OBJECT

public:
    // constructors
    Application() = delete;
    Application(int& argc, char* argv[]);

    // event loop
    int run(void) const;

private:
    static constexpr auto minWindowWidth {400};
    static constexpr auto minWindowHeight {700};
};

#endif // APPLICATION_H
