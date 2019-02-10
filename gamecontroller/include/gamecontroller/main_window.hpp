/**
 * @file /include/gamecontroller/main_window.hpp
 *
 * @brief Qt based gui for gamecontroller.
 *
 * @date November 2010
 **/
#ifndef gamecontroller_MAIN_WINDOW_H
#define gamecontroller_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_main_window.h"
#include "qnode.hpp"

#include "RoboCupGameControlData.h"

#include <QtNetwork>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>

#include <iostream>

using namespace std;
/*****************************************************************************
** Namespace
*****************************************************************************/

namespace gamecontroller {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    QTimer        *mTimer;
    MainWindow(int argc, char** argv, QWidget *parent = 0);
    ~MainWindow();

    void ReadSettings(); // Load up qt program settings at startup
    void WriteSettings(); // Save qt program settings when closing

    //	void closeEvent(QCloseEvent *event); // Overloaded function
    void showNoMasterMessage();

    void initAddrAndPort();
    void initSocket();
    void closeSocket();

public Q_SLOTS:
    /******************************************
        ** Auto-connections (connectSlotsByName())
        *******************************************/
    //	void on_actionAbout_triggered();
    //	void on_button_connect_clicked(bool check );
    //	void on_checkbox_use_environment_stateChanged(int state);

    /******************************************
    ** Manual connections
    *******************************************/
    //    void updateLoggingView(); // no idea why this can't connect automatically

private:
    Ui::RobocupController ui;
    QNode qnode;

    QUdpSocket     *m_pUdpSocket=NULL;

    QHostAddress   m_qSrcAddress;
    QHostAddress   m_qDestAddress;

    quint16        m_iPort;
    QString        m_qstrIp;

    bool           m_bIsServerOpen;

    int            playerNum;


private Q_SLOTS:
    void on_Server_Open_clicked();

    void readData();

private:

    struct RoboCupGameControlData robocupData;
    struct RoboCupGameControlReturnData robocupreturnData;
    struct RobotInfo robotInfo;
    struct TeamInfo teamInfo;
};

}  // namespace gamecontroller

#endif // gamecontroller_MAIN_WINDOW_H



