#ifndef ASYNCPIZZARESPONSE_H
#define ASYNCPIZZARESPONSE_H

#include <QQuickImageResponse>
#include <QRunnable>
#include <QStringList>
#include <QMap>
#include <QPainter>
/*******************************************************
 * Building a one-time-run PizzaRenderer!
 *
 *  Idea -
 *      1.)Render Pizza in a 523,528 (pizza size) QImage
 *      2.)For each topping in the topping list, load and
 *          paint the toppings.
 *
 *
 * *****************************************************/
class AsyncPizzaResponse : public QQuickImageResponse, public QRunnable
{
    public:
        AsyncPizzaResponse(const QStringList &toppings, const QMap<QString,QImage *> &loadedImages, const QSize &requestedSize)
         : m_toppingsList(toppings), m_loadedImages(loadedImages), m_requestedSize(requestedSize), m_texture(0)
        {
            setAutoDelete(false);
        }

        QQuickTextureFactory *textureFactory() const
        {
            return m_texture;
        }

        void drawTopping(QPainter &painter, const QString &source)
        {
            QImage  img(95,95,QImage::Format_RGB32);
            img = (*m_loadedImages.value(source));

            int x = 92;
            int y = 78;
            int columns_drawn(0);
            painter.drawImage(80,175,img);
            for(int index(0); index < 16; index++)
            {
                painter.drawImage(x,y,img);
                x+= 80;
                columns_drawn++;
                if(columns_drawn >= 4)
                {
                    columns_drawn = 0;
                    x = 92 - ((10 - index)*4);
                    y+= 92;
                }
            }
            painter.drawImage(385,175,img);
            painter.drawImage(385,245,img);
        }

        void run()
        {
            QImage image(523, 528, QImage::Format_RGB32);
            image = (*m_loadedImages.value("pizza"));

            // Create the painter
            QPainter  painter(&image);

            for(QString item : m_toppingsList)
            {
                drawTopping(painter, item);
            }

            // ignore this stuff
            if (m_requestedSize.isValid() && (image.size() != m_requestedSize))
                image = image.scaled(m_requestedSize);
            m_texture = QQuickTextureFactory::textureFactoryForImage(image);
            emit finished();
        }

        QMap<QString,QImage *> m_loadedImages;
        QStringList m_toppingsList;
        QSize m_requestedSize;
        QQuickTextureFactory *m_texture;
};

#endif // ASYNCPIZZARESPONSE_H
