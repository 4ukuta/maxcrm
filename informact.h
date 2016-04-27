#ifndef INFORMACT_H
#define INFORMACT_H

#include <QWidget>

namespace Ui {
class InformAct;
}

class InformAct : public QWidget
{
    Q_OBJECT

public:
    explicit InformAct(QWidget *parent = 0);
    ~InformAct();

private slots:
    void on_pushButton_clicked();
    void getInfo(QString);

private:
    Ui::InformAct *ui;
};

#endif // INFORMACT_H
