#ifndef ADDVERTEX_H
#define ADDVERTEX_H

#include <QDialog>

namespace Ui {
class AddVertex;
}

class AddVertex : public QDialog
{
    Q_OBJECT

public:
    explicit AddVertex(QWidget *parent = nullptr);
    ~AddVertex();

private slots:
    void on_input_VertexValue_blockCountChanged(int newBlockCount);

private:
    Ui::AddVertex *ui;
};

#endif // ADDVERTEX_H
