#include "widget.h"

#include <QGridLayout>
#include <QFileDialog>
#include <qDebug>

QImage Widget::ConvertToBlackAndWhite(const QImage& colorImage) {
    QImage blackAndWhiteImage(colorImage.size(), QImage::Format_RGB32);

        for (int y = 0; y < colorImage.height(); ++y) {
            for (int x = 0; x < colorImage.width(); ++x) {
                // Получаем цвет пикселя в RGB формате
                QColor color = QColor::fromRgb(colorImage.pixel(x, y));

                // Вычисляем яркость пикселя по формуле Y = 0.299R + 0.587G + 0.114B
                int brightness = 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();

                // Создаем новый цвет пикселя, используя яркость для всех компонентов RGB
                QColor newColor(brightness, brightness, brightness);

                // Устанавливаем новый цвет пикселя в черно-белое изображение
                blackAndWhiteImage.setPixelColor(x, y, newColor);
            }
        }
        return blackAndWhiteImage;
}

void Widget::CreateButton(QPushButton *button, int width, int height){
    button->setFixedSize(width, height);
    button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void Widget::BlackInWhite(){

    if (accessBlackInWhite == true){
    pixmapFilt = QPixmap::fromImage(ConvertToBlackAndWhite(image));
    while (viewImage == nullptr) {viewImage = new ImageView;}
    if (bolFilter == false){
    if(!pixmapFilt.isNull()) {
        delete itemFilter;
        itemFilter = nullptr;

        itemFilter = new QGraphicsPixmapItem(pixmapFilt);

        viewImage->setScene(setScene);
        bolDefulat = true;
        bolFilter = true;
            }
        }
    itemFilter->setTransformOriginPoint(itemFilter->boundingRect().center());
    if (bolFilter == true)
        {
        qDebug() << "bolFilter :" << bolFilter;

        setScene->removeItem(itemDefulat);

        setScene->addItem(itemFilter);

        float scaleFactor = qMin(viewImage->width() / itemFilter->boundingRect().width(), viewImage->height() / itemFilter->boundingRect().height());
        itemFilter->setScale(scaleFactor);

        QPointF center = viewImage->viewport()->rect().center();
        QPointF itemCenter = itemFilter->mapToScene(itemFilter->boundingRect().center());
        QPointF offset = center - itemCenter;
        itemFilter->setPos(itemFilter->pos() + offset);

        viewImage->setScene(setScene);
        accessBlackInWhite = false;
       }
    }
}

void Widget::LoadButtonImage(){

    QString Path = QFileDialog::getOpenFileName(this); // далогов
    if (Path != file_name){
    file_name.clear();
    file_name = Path;

    pixmap= QPixmap();
    pixmapFilt = QPixmap();
    image = QImage();

    pixmap.load(file_name);
    if(!pixmap.isNull()){
    image.load(file_name);
    access = true;
    bolDefulat = false;
    bolFilter = false;
    setScene->removeItem(itemDefulat);
    setScene->removeItem(itemFilter);}}
}

void Widget::ShowImageButton(){

    if (access == true){

    while (viewImage == nullptr) {viewImage = new ImageView;}
    if(bolDefulat == false)
        {
        QPixmap timepix = QPixmap();

    if(!pixmap.isNull()) {
        if (timepix != pixmap){

         delete itemDefulat;
        itemDefulat = nullptr;
        timepix = pixmap;


        setScene->clear();
        setScene->removeItem(itemDefulat);

        itemDefulat = new QGraphicsPixmapItem(pixmap);
        bolDefulat = true;}
            }
        }

    if(bolDefulat = true)
        {
        qDebug() << "bolDefulat :" << bolDefulat ;
        setScene->removeItem(itemFilter);

        setScene->addItem(itemDefulat);

        itemDefulat->setTransformOriginPoint(itemDefulat->boundingRect().center());
        float scaleFactor = qMin(viewImage->width() / itemDefulat->boundingRect().width(), viewImage->height() / itemDefulat->boundingRect().height());
        itemDefulat->setScale(scaleFactor);

        QPointF center = viewImage->viewport()->rect().center();
        QPointF itemCenter = itemDefulat->mapToScene(itemDefulat->boundingRect().center());
        QPointF offset = center - itemCenter;
        itemDefulat->setPos(itemDefulat->pos() + offset);

        viewImage->setScene(setScene);

        bolFilter == true;
        accessBlackInWhite = true;
        }
   }
    pixmap = QPixmap();
}

void Widget::SaveImageButton(){
    if(!pixmapFilt.isNull()){
    QString fileNameSave = QFileDialog::getSaveFileName(nullptr, "Сохранить изображение", "", "JPEG (*.jpg);;PNG (*.png)");
    pixmapFilt.save(fileNameSave);}
}
/////////////////////////////////////////////////////////////////////////////////////////////

Widget::Widget(QWidget *parent)
    : QWidget(parent){
    QGridLayout* body_grid = new QGridLayout(this);

    QPushButton* open = new QPushButton("Open" );
    QPushButton* save = new QPushButton("Save");
    QPushButton* show = new QPushButton("Show");
    QPushButton* transformation = new QPushButton("Transform");

    label = new QLabel(this);

    CreateButton(open,75, 30);
    body_grid->addWidget(open, 1, 3, 1, 1);

    CreateButton(save,75, 30);
    body_grid->addWidget(save, 2, 3, 1, 1);

    CreateButton(show,75, 30);
    body_grid->addWidget(show, 3, 3, 1, 1);

    CreateButton(transformation,75, 30);
    body_grid->addWidget(transformation, 4, 3, 1, 1);

    connect(open, SIGNAL(clicked()), this, SLOT(LoadButtonImage()));
    connect(show, SIGNAL(clicked()), this, SLOT(ShowImageButton()));
    connect(save, SIGNAL(clicked()), this, SLOT(SaveImageButton()));
    connect(transformation, SIGNAL(clicked()), this, SLOT(BlackInWhite()));

    label->setPixmap(pixmap);
    setScene = new QGraphicsScene(viewImage);
    viewImage = new ImageView;
    viewImage->setScene(setScene);
    while (viewImage == nullptr) {viewImage = new ImageView;}

    body_grid->addWidget(viewImage, 1, 1, 5, 1);
    setLayout(body_grid);
}

Widget::~Widget(){
    setScene->clear();

    pixmap= QPixmap();
    pixmapFilt = QPixmap();
    image = QImage();
    file_name.clear();

    delete setScene;
    delete viewImage;

    setScene = nullptr;
    viewImage = nullptr;
}
