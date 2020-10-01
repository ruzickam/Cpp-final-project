#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Application.h"
#include "GraphicWidget.h"

//==============================================================================
//---CONSTRUCTORS---------------------------------------------------------------
//==============================================================================

Application::Application(int& argc, char* argv[]) : QApplication(argc, argv) {}

//==============================================================================
//---EVENT LOOP-----------------------------------------------------------------
//==============================================================================

int Application::run(void) const
{
    QWidget mainWindow;

    QHBoxLayout mainLayout {&mainWindow};

    GraphicWidget graphicWidget {&mainWindow};
    QVBoxLayout rightLayout;
    
    // add graphicWidget and rightLayout to mainLayout
    mainLayout.addWidget(&graphicWidget);
    mainLayout.addLayout(&rightLayout);  

    // set graphicWidget minimum size
    graphicWidget.setMinimumSize(GraphicWidget::minWindowWidth , GraphicWidget::minWindowHeight);

    // -------------------------------------------------------

    QPushButton buttonHide {"Hide", &mainWindow};
    QPushButton buttonShow {"Show", &mainWindow};
    QPushButton buttonOpenFile {"Open File", &mainWindow};

    // right column with buttons  
    rightLayout.addWidget(&buttonHide);
    rightLayout.addWidget(&buttonShow);
    rightLayout.addWidget(&buttonOpenFile);
    rightLayout.addStretch();

    // -------------------------------------------------------

    // setup and show main window
    mainWindow.setWindowTitle("Show sequence from PDB file");
    mainWindow.show();

    // -------------------------------------------------------

    // click signals for buttons
    QObject::connect( &buttonHide, SIGNAL( clicked() ), &graphicWidget, SLOT(hideShortcuts() ) );
    QObject::connect( &buttonShow, SIGNAL( clicked() ), &graphicWidget, SLOT(showShortcuts() ) );
    QObject::connect( &buttonOpenFile, SIGNAL( clicked() ), &graphicWidget, SLOT(openPDBfile() ) );

    // -------------------------------------------------------

    auto ret {0};
    try {
        ret = QApplication::exec();
    } catch (const std::bad_alloc&){
        // clean up here, e.g. save the session
        // and close all config files.

        return EXIT_FAILURE;
    }

    return ret;
}
