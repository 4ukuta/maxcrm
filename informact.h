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

private:
    Ui::InformAct *ui;
};

#endif // INFORMACT_H
