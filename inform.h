#ifndef INFORM_H
#define INFORM_H

#include <QWidget>

namespace Ui {
class Inform;
}

class Inform : public QWidget
{
    Q_OBJECT

public:
    explicit Inform(QWidget *parent = 0);
    ~Inform();
public slots:
    void getName(QString );
private:
    Ui::Inform *ui;
};

#endif // INFORM_H
