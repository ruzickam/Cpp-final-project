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

int Application::run(void)
{
    QWidget mainWindow;
    mainWindow.setWindowTitle("Show sequence from PDB file");

    GraphicWidget* p_graphicWidget = new GraphicWidget;   
    p_graphicWidget->setMinimumSize(400,700);

    // right column with buttons
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

    mainWindow.setLayout(p_mainLayout);
    mainWindow.show();

    // click signals for buttons
    QObject::connect(p_buttonHide,SIGNAL(clicked()),p_graphicWidget,SLOT(hideGraphic()));
    QObject::connect(p_buttonShow,SIGNAL(clicked()),p_graphicWidget,SLOT(showGraphic()));
    QObject::connect(p_buttonOpenFile,SIGNAL(clicked()),p_graphicWidget,SLOT(openFile()));

    return QApplication::exec();
}
