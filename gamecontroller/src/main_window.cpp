/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/gamecontroller/main_window.hpp"
#include "../include/gamecontroller/robocupController.h"
#include "../include/gamecontroller/robocupController_msg.h"
#include "../include/gamecontroller/robocupController2.h"



/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace gamecontroller {

using namespace Qt;

extern ros::Publisher controller_pub;

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
  : QMainWindow(parent)
  , qnode(argc,argv)
{
    MainWindow::ui.setupUi(this); // Calling this incidentally connects all ui's triggers to on_...() callbacks in this class.
    QObject::connect(&qnode, SIGNAL(rosShutdown()), this, SLOT(close()));

    qnode.init();
    initAddrAndPort();
}

MainWindow::~MainWindow()
{
//    delete &ui;
    delete m_pUdpSocket;
}

void MainWindow::initAddrAndPort()
{
    bool isOpen_Network = false;

    while(!isOpen_Network)
    {
        QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

        for(int i=0;i<ipAddressesList.size();i++)
        {
            if(ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
            {
                if(ipAddressesList.at(i).toString().toStdString().find("192") != std::string::npos)
                {
                    m_qstrIp = ipAddressesList.at(i).toString();
                    isOpen_Network = true;
                    break;
                }
            }
        }

        if(m_qstrIp.isEmpty())
        {
            m_qstrIp = QHostAddress(QHostAddress::LocalHost).toString();
        }
    }
    m_qSrcAddress.setAddress(m_qstrIp);

    m_iPort = 3838;

    ui.IP_Line->setText(m_qstrIp);
    ui.PORT_Line->setText(QString::number(m_iPort));
}

void MainWindow::initSocket()
{
    if(m_pUdpSocket==NULL)
    {
        m_pUdpSocket = new QUdpSocket(this);
    }
    if(m_pUdpSocket!=NULL && m_pUdpSocket->bind(QHostAddress::Any,m_iPort))
    {
        m_bIsServerOpen=true;

        ui.IP_Line->setEnabled(false);
        ui.PORT_Line->setEnabled(false);
        ui.NUM_line->setEnabled(false);

        ui.Server_Open->setText("CLOSE");

        connect(m_pUdpSocket,SIGNAL(readyRead()),this,SLOT(readData()));
    }
}

void MainWindow::closeSocket()
{
    ui.IP_Line->setEnabled(true);
    ui.PORT_Line->setEnabled(true);
    ui.NUM_line->setEnabled(true);

    disconnect(m_pUdpSocket,SIGNAL(readyRead()),this,SLOT(readData()));
    ui.textEdit->clear();

    ui.Server_Open->setText("OPEN");

    m_pUdpSocket->close();

    m_bIsServerOpen = false;
}

void MainWindow::on_Server_Open_clicked()
{
    if(m_bIsServerOpen == false)
    {
        QString n = ui.NUM_line->text();
        playerNum = n.toInt() - 1;
        if(playerNum < 0) playerNum = 1;

        ui.NUM_line->setText(QString::number(playerNum + 1));

        initSocket();
    }
    else
    {
        closeSocket();
    }
}

void MainWindow::readData()
{
    QHostAddress senderAddress;
    quint16 senderPort;

    //robocup_controller::robocupController RCMsg;
    gamecontroller::robocupController2 RCmsg;

    QByteArray str;
    str.resize(m_pUdpSocket->bytesAvailable());

    m_pUdpSocket->readDatagram(str.data(),str.size(),&senderAddress,&senderPort);

    if(str.size() == 640)
    {
        ui.textEdit->clear();

        memmove(&robocupData, str.data(), sizeof(RoboCupGameControlData));
        std::cout << "state = " << (int)robocupData.state << std::endl;
        std::cout << "penalty = " << (int)robocupData.teams[0].players[0].penalty << std::endl;
        std::cout << "half = " << (int)robocupData.firstHalf << std::endl;
        std::cout << "kickoff team = " << (int)robocupData.kickOffTeam << std::endl;
        std::cout << "secondary = " << (int)robocupData.secondaryState << std::endl;

        RCmsg.state = (int)robocupData.state;
        RCmsg.firstHalf = (int)robocupData.firstHalf;
        RCmsg.kickoffTeam = (int)robocupData.kickOffTeam;

        switch ((int)robocupData.firstHalf)
        {
        case 1:
            ui.textEdit->append("1st Half");
            RCmsg.penalty = (int)robocupData.teams[1].players[playerNum].penalty;
            break;

        case 0:
            ui.textEdit->append("2nd Half");
            RCmsg.penalty = (int)robocupData.teams[0].players[playerNum].penalty;
            break;
        }

        switch ((int)robocupData.state)
        {
        case STATE_INITIAL:
            ui.textEdit->append("state : Initial");
            break;
        case STATE_READY:
            ui.textEdit->append("state : Ready");
            RCmsg.readyTime = (int)robocupData.secondaryTime;
            ui.textEdit->append(QString::number(robocupData.secondaryTime));
            break;
        case STATE_SET:
            ui.textEdit->append("state : Set");
            break;
        case STATE_PLAYING:
            ui.textEdit->append("state : Play");
            RCmsg.readyTime = (int)robocupData.secondaryTime;
            ui.textEdit->append(QString::number(robocupData.secondaryTime));
            break;
        case STATE_FINISHED:
            ui.textEdit->append("state : Finish");
            break;

        }

        switch (RCmsg.penalty)
        {
        case HL_BALL_MANIPULATION:
            ui.textEdit->append("penalty : BALL_MANIPULATION");
            break;
        case HL_PHYSICAL_CONTACT:
            ui.textEdit->append("penalty : PHYSICAL_CONTACT");
            break;
        case HL_ILLEGAL_ATTACK:
            ui.textEdit->append("penalty : ILLEGAL_ATTACK");
            break;
        case HL_ILLEGAL_DEFENSE:
            ui.textEdit->append("penalty : ILLEGAL_DEFENSE");
            break;
        case HL_PICKUP_OR_INCAPABLE:
            ui.textEdit->append("penalty : PICKUP_OR_INCAPABLE");
            break;
        case HL_SERVICE:
            ui.textEdit->append("penalty : SERVICE");
            break;
        default:
            ui.textEdit->append("Penalty : NONE");
            break;

        }
/*

#define HL_BALL_MANIPULATION                30
#define HL_PHYSICAL_CONTACT                 31
#define HL_ILLEGAL_ATTACK                   32
#define HL_ILLEGAL_DEFENSE                  33
#define HL_PICKUP_OR_INCAPABLE              34
#define HL_SERVICE                          35
  */

//        controller_pub.publish(RCMsg);
          controller_pub.publish(RCmsg);
    }

}


}  // namespace robocup_controller
