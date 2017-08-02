/**
  * @file main.cpp
  * @brief the main file
  * @author Romain Lebbadi-Breteau
  * @version 1.0
  * @date 02/08/2017
  */
#include <QApplication>
#include "mainwindow.h"

/**
 * @brief main create a window and show it
 * @param argc contains the number of arguments
 * @param argv contains the aguments
 * @return if everything went good
 */
int main(int argc, char *argv[])
{
    /**
     * @brief app is the application
     * @return the current application
     */
    QApplication app(argc, argv);

    /**
     * @brief window is the main window
     */
    MainWindow window;
    window.show();

    return app.exec();
}
