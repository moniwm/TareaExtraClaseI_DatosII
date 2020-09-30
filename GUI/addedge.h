#ifndef ADDEDGE_H
#define ADDEDGE_H

#include <QDialog>

namespace Ui {
class AddEdge;
}

class AddEdge : public QDialog
{
    Q_OBJECT

public:
    explicit AddEdge(QWidget *parent = nullptr);
    ~AddEdge();

private:
    Ui::AddEdge *ui;
};

#endif // ADDEDGE_H
