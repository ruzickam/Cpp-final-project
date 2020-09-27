#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Application.h"

Application::Application(int &argc, char *argv[]) : QApplication(argc, argv)
{

}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

int Application::run(void) const
{
    QWidget mainWindow;

    QHBoxLayout mainLayout(&mainWindow);

    GraphicWidget graphicWidget(&mainWindow);
    QVBoxLayout rightLayout;

    QPushButton buttonHide("Hide", &mainWindow);
    QPushButton buttonShow("Show", &mainWindow);
    QPushButton buttonOpenFile("Open File", &mainWindow); 

    //--------------------------------------------------------------------------
    
    // add graphicWidget and rightLayout to mainLayout
    mainLayout.addWidget(&graphicWidget);
    mainLayout.addLayout(&rightLayout);  

    // set graphicWidget size
    graphicWidget.setMinimumSize(400, 700);

    // right column with buttons  
    rightLayout.addWidget(&buttonHide);
    rightLayout.addWidget(&buttonShow);
    rightLayout.addWidget(&buttonOpenFile);
    rightLayout.addStretch();

    // setup and show main window
    mainWindow.setWindowTitle("Show sequence from PDB file");
    mainWindow.show();

    // click signals for buttons
    QObject::connect(&buttonHide, SIGNAL(clicked()), &graphicWidget, SLOT(hideGraphic()));
    QObject::connect(&buttonShow, SIGNAL(clicked()), &graphicWidget, SLOT(showGraphic()));
    QObject::connect(&buttonOpenFile, SIGNAL(clicked()), &graphicWidget, SLOT(openFile()));

    return QApplication::exec();
}
