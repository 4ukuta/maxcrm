#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "inform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateComboBox(QComboBox *);
    void updateComboBoxProj(QComboBox *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_comboBox_4_currentTextChanged(const QString &arg1);

    void on_comboBox_5_currentTextChanged(const QString &arg1);

    void on_comboBox_5_currentIndexChanged(const QString &arg1);

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_horizontalSlider_rangeChanged(int min, int max);

    void on_horizontalSlider_valueChanged(int value);

    void on_tabWidget_currentChanged(int index);
    void TableRating();

private:
    Ui::MainWindow *ui;

signals:
    void setName(QString);
};

#endif // MAINWINDOW_H
