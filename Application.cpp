#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Application.h"

Application::Application(int &argc, char *argv[]) : QApplication(argc, argv)
{
    p_graphicWidget = NULL;
    p_mainWindow = NULL;
}

Application::~Application()
{
    if( p_graphicWidget != NULL ){
        delete p_graphicWidget;
    }
    
    if( p_mainWindow != NULL ){
        delete p_mainWindow;
    }  

    p_graphicWidget = NULL;
    p_mainWindow = NULL;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

int Application::run(void)
{
    p_mainWindow = new QWidget;
    p_mainWindow->setWindowTitle("Show sequence from PDB file");

    p_graphicWidget = new GraphicWidget;

    // right column with buttons
    p_graphicWidget->setMinimumSize(400,700);
    QPushButton* p_buttonHide = new QPushButton("Hide");
    QPushButton* p_buttonShow = new QPushButton("Show");
    QPushButton* p_buttonOpenFile = new QPushButton("Open File");

    QVBoxLayout* p_rightLayout = new QVBoxLayout;
    p_rightLayout->addWidget(p_buttonHide);
    p_rightLayout->addWidget(p_buttonShow);
    p_rightLayout->addWidget(p_buttonOpenFile);
    p_rightLayout->addStretch();

    QHBoxLayout* p_mainLayout = new QHBoxLayout;
    p_mainLayout->addWidget(p_graphicWidget);
    p_mainLayout->addLayout(p_rightLayout);

    p_mainWindow->setLayout(p_mainLayout);

    p_mainWindow->show();

    // click signals for buttons
    QObject::connect(p_buttonHide,SIGNAL(clicked()),p_graphicWidget,SLOT(hideGraphic()));
    QObject::connect(p_buttonShow,SIGNAL(clicked()),p_graphicWidget,SLOT(showGraphic()));
    QObject::connect(p_buttonOpenFile,SIGNAL(clicked()),p_graphicWidget,SLOT(openFile()));

    return QApplication::exec();
    
    if( p_buttonHide != NULL ){
        delete p_buttonHide;
    }
    
    if( p_buttonShow != NULL ){
        delete p_buttonShow;
    }
    
    if( p_buttonOpenFile != NULL ){
        delete p_buttonOpenFile;
    }
    
    if( p_rightLayout != NULL ){
        delete p_rightLayout;
    }
    
    if( p_mainLayout != NULL ){
        delete p_mainLayout;
    }
    
    p_buttonHide = NULL;
    p_buttonShow = NULL;
    p_buttonOpenFile = NULL;
    p_rightLayout = NULL;
    p_mainLayout = NULL;
}
