#ifndef DELETEEDGE_H
#define DELETEEDGE_H

#include <QDialog>

namespace Ui {
class DeleteEdge;
}

class DeleteEdge : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteEdge(QWidget *parent = nullptr);
    ~DeleteEdge();

private:
    Ui::DeleteEdge *ui;
};

#endif // DELETEEDGE_H
