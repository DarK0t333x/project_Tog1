#include "mainwindow.h"
#include <QMouseEvent> // библиотека для отслеживания клика мыши
#include <cmath> // библиотека для счета координат точек

// Вызывается 1 раз при запуске программы
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)  // Вызываем конструктор родительского класса
{
    // Настройки окна
    setWindowTitle("visuailisation");  // Заголовок окна

    // === НАСТРОЙКА ТАЙМЕРА (для анимации) ===
    timer = new QTimer(this);           // Создаем таймер
    timer->setInterval(50);             // Каждые 50 мс (20 раз в секунду)
    connect(timer, SIGNAL(timeout()), this, SLOT(updateAnimation()));
    timer->start();                     // Запускаем таймер



    //СОЗДАЕМ ПЕРВУЮ ТОЧКУ
    for(int i=0;i<1;i++){         //Цикл из 1 точки
        x.append(rand()%600);         //Случайная X
        y.append(rand()%400);         //Случайная Y
        vx.append((rand()%7)-3);    //Скорость X
        vy.append((rand()%7)-3);    //Скорость Y
    }
}


// Вызывается при закрытии программы
MainWindow::~MainWindow()
{
    timer->stop();  // Останавливаем таймер
}


// отрисовка вызывается при запуске и после каждого update()
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);  // Создаем "художника" для рисования

    // ФОН
    painter.fillRect(0,0,width(),height(),Qt::black);  // Черный фон

    //точки
    for(int i=0;i<x.size(); i++) {
        painter.setBrush(Qt::white);   // Белый цвет заливки
        painter.setPen(Qt::NoPen);     // Без контура

        int size = 10;                 // Размер точки

        painter.drawEllipse(x[i],y[i],size,size);  // Рисуем круг
    }

    //текст
    painter.setPen(Qt::white);// Белый цвет текста
    painter.drawText(10, 30, "Dots: " + QString::number(x.size()));  // Кол-во точек
    painter.drawText(10, 55, "Click to add");  // Подсказка
}

//КЛИК МЫШИ
// Вызывается при нажатии кнопки мыши
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // Добавляем новую точку в месте клика
    x.append(event->x());           // X координата клика
    y.append(event->y());           // Y координата клика
    vx.append((rand()%7)-3);    // Случайная скорость X
    vy.append((rand()%7)-3);    // Случайная скорость Y
}


// анимация вызывается таймером каждые 50 мс
void MainWindow::updateAnimation()
{
    counter++;  // Увеличиваем счетчик (пока не используется)

    // ДВИГАЕМ ВСЕ ТОЧКИ
    for(int i=0;i<x.size();i++) {
        // Меняем координаты согласно скорости
        x[i]=x[i]+vx[i];
        y[i]=y[i]+vy[i];

        //левая стена
        if(x[i]<0) {
            x[i]=0;          // Ставим на границу
            vx[i]=-vx[i];    // Разворачиваем скорость
        }

        //правая стена
        if(x[i]>width()) {
            x[i]=width();     // Ставим на границу
            vx[i]=-vx[i];    // Разворачиваем скорость
        }

        //верхняя стена
        if(y[i]<0) {
            y[i]=0;          // Ставим на границу
            vy[i] = -vy[i];    // Разворачиваем скорость
        }

        //нижняя стена
        if(y[i] > height()) {
            y[i] = height();    // Ставим на границу
            vy[i] = -vy[i];    // Разворачиваем скорость
        }
    }

    update();  // Перерисовываем экран (вызовет paintEvent)
}
