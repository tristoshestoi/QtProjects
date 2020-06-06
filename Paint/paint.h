#ifndef PAINT_H
#define PAINT_H

#include <QWidget>
#include <QTimer>
#include <QResizeEvent>
#include <QFileDialog>
#include <QMenu>

#include <paintscene.h>



QT_BEGIN_NAMESPACE
namespace Ui {
class Paint;
}
QT_END_NAMESPACE

class Paint : public QWidget
{
    Q_OBJECT

public:
    explicit Paint(QWidget *parent = 0);
    ~Paint();


private:
    Ui::Paint *ui;
    QTimer *timer;
    void mousePressEvent(QMouseEvent * event);
    /* Определяем таймер для подготовки актуальных размеров
                             * графической сцены
                         * */
    paintScene *scene;  // Объявляем кастомную графическую сцену

    QMenu *menu = new QMenu("Menu",this);
    QAction *action = new QAction ("Eraser");


private:
    /* Переопределяем событие изменения размера окна
     * для пересчёта размеров графической сцены
     * */
    void resizeEvent(QResizeEvent * event);

private slots:
    void slotTimer();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // PAINT_H
