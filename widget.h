#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPushButton>




class ImageView : public QGraphicsView {
public:
    ImageView(QWidget* parent = nullptr) : QGraphicsView(parent) {}

protected:
    void resizeEvent(QResizeEvent* event) override {
        QGraphicsView::resizeEvent(event);
        fitInView(sceneRect(), Qt::KeepAspectRatio);
    }
};


class Widget : public QWidget
{
    Q_OBJECT

public slots:

    void BlackInWhite();
    void LoadButtonImage();
    void ShowImageButton();
    void SaveImageButton();
    void CreateButton(QPushButton *button, int width, int height);
    QImage ConvertToBlackAndWhite(const QImage& colorImage);


public:

    bool bolDefulat = false;// yes
    bool bolFilter = false;//n
    bool bolImageLoad = false;

    bool access = false;
    bool accessBlackInWhite = false;

    QString file_name;

    QLabel* label;

    QPixmap pixmap; //imgs
    QPixmap pixmapFilt;
    QImage image; //_image


    QGraphicsScene* setScene = nullptr;
    ImageView* viewImage = nullptr;

    QGraphicsPixmapItem* itemDefulat = nullptr;
    QGraphicsPixmapItem* itemFilter = nullptr;

    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
