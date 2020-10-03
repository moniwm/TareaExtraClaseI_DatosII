#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ClientSocket.h"

ClientSocket *client;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new ClientSocket();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_addVertex_clicked()
{
    addVertexWindow = new AddVertex(this);
    addVertexWindow->setModal(true);
    addVertexWindow->exec();
}

void MainWindow::on_btn_addEdge_clicked()
{
    addEdgeWindow = new AddEdge(this);
    addEdgeWindow->setModal(true);
    addEdgeWindow->exec();
}

void MainWindow::on_btn_deleteVertex_clicked()
{
    deleteVertexWindow = new DeleteVertex(this);
    deleteVertexWindow->setModal(true);
    deleteVertexWindow->exec();
}

void MainWindow::on_btn_deleteEdge_clicked()
{
    deleteEdgeWindow = new DeleteEdge(this);
    deleteEdgeWindow->setModal(true);
    deleteEdgeWindow->exec();
}

