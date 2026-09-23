#include "gaugewidget.h"

#include <QPainter>
#include <QtMath>

GaugeWidget::GaugeWidget(QWidget *parent)
    : QWidget(parent)
{
    valeur = 0;
    maximum = 100;
    unite = "";

    setMinimumSize(250, 250);
}

// VALEUR

void GaugeWidget::setValue(double value)
{
    valeur = value;

    if (valeur < 0)
        valeur = 0;

    if (valeur > maximum)
        valeur = maximum;

    update();
}

// MAXIMUM

void GaugeWidget::setMaximum(double max)
{
    maximum = max;
    update();
}


// UNITE

void GaugeWidget::setUnit(const QString &unit)
{
    unite = unit;
    update();
}

// DESSIN

void GaugeWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);


    // =========================
    // FOND
    // =========================

    painter.fillRect(rect(), Qt::black);


    // =========================
    // CENTRE
    // =========================

    int taille = qMin(width(), height());

    QPoint centre(
        width() / 2,
        height() / 2
        );

    int rayon = taille / 2 - 15;


    // =========================
    // CERCLE EXTERIEUR
    // =========================

    painter.setPen(
        QPen(Qt::white, 3)
        );

    painter.setBrush(Qt::black);

    painter.drawEllipse(
        centre,
        rayon,
        rayon
        );


    // =========================
    // CERCLE INTERIEUR
    // =========================

    painter.setPen(
        QPen(Qt::gray, 2)
        );

    painter.drawEllipse(
        centre,
        rayon - 15,
        rayon - 15
        );


    // =====================================================
    // GRADUATIONS
    // =====================================================

    painter.save();

    for (int i = 0; i <= 40; i++)
    {
        /*
         * Angle radial :
         *
         * 0       = bas gauche
         * maximum = bas droite
         *
         * -225° -> 45°
         */

        double angle =
            -225.0 + i * 270.0 / 40.0;

        double radians =
            qDegreesToRadians(angle);


        // Point extérieur
        double x1 =
            centre.x()
            + qCos(radians) * (rayon - 10);

        double y1 =
            centre.y()
            + qSin(radians) * (rayon - 10);


        // Longueur graduation

        int longueur;

        if (i % 5 == 0)
            longueur = 18;
        else
            longueur = 8;


        // Point intérieur

        double x2 =
            centre.x()
            + qCos(radians)
                  * (rayon - 10 - longueur);

        double y2 =
            centre.y()
            + qSin(radians)
                  * (rayon - 10 - longueur);


        // Valeur de la graduation

        double valeurGraduation =
            maximum * i / 40.0;


        // =========================
        // ZONE ROUGE
        // =========================

        if (maximum == 18000 &&
            valeurGraduation >= 16000)
        {
            painter.setPen(
                QPen(
                    Qt::red,
                    i % 5 == 0 ? 4 : 2
                    )
                );
        }
        else
        {
            painter.setPen(
                QPen(
                    Qt::white,
                    i % 5 == 0 ? 3 : 1
                    )
                );
        }


        // Dessin de la graduation

        painter.drawLine(
            QPointF(x1, y1),
            QPointF(x2, y2)
            );
    }

    painter.restore();


    // =====================================================
    // CHIFFRES
    // =====================================================

    painter.setPen(Qt::white);

    QFont font = painter.font();

    font.setBold(true);
    font.setPointSize(12);

    painter.setFont(font);


    int nombreGraduations;

    if (maximum == 18000)
        nombreGraduations = 9;
    else
        nombreGraduations = 6;


    for (int i = 0;
         i <= nombreGraduations;
         i++)
    {
        /*
         * Même angle que les graduations.
         */

        double angle =
            -225.0
            + i * 270.0 / nombreGraduations;


        double radians =
            qDegreesToRadians(angle);


        // Position des chiffres

        double x =
            centre.x()
            + qCos(radians)
                  * (rayon - 42);

        double y =
            centre.y()
            + qSin(radians)
                  * (rayon - 42);


        // Valeur

        QString texte =
            QString::number(
                maximum * i / nombreGraduations,
                'f',
                0
                );


        QRectF zone(
            x - 35,
            y - 14,
            70,
            28
            );


        painter.drawText(
            zone,
            Qt::AlignCenter,
            texte
            );
    }


    // =====================================================
    // UNITE
    // =====================================================

    QFont unitFont = painter.font();

    unitFont.setPointSize(10);
    unitFont.setBold(true);

    painter.setFont(unitFont);


    QRectF zoneUnite(
        centre.x() - 60,
        centre.y() - 70,
        120,
        30
        );


    painter.drawText(
        zoneUnite,
        Qt::AlignCenter,
        unite
        );


    // AIGUILLE


    /*
     * Même angle que les graduations.
     * 0       = bas gauche
     * maximum = bas droite
     */

    double angle =
        -225.0
        + (valeur / maximum) * 270.0;


    double radians =
        qDegreesToRadians(angle);


    // Extrémité de l'aiguille

    double xAiguille =
        centre.x()
        + qCos(radians)
              * (rayon - 35);

    double yAiguille =
        centre.y()
        + qSin(radians)
              * (rayon - 35);


    // AIGUILLE Vert

    painter.setPen(QPen(Qt::green, 5) );


    painter.drawLine( centre,QPointF(xAiguille, yAiguille ) );

    // CENTRE AIGUILLE

    painter.setBrush(Qt::green);

    painter.setPen(Qt::white);


    painter.drawEllipse(centre,  8, 8 );

    // VALEUR NUMERIQUE

    QFont valueFont = painter.font();

    valueFont.setPointSize(14);
    valueFont.setBold(true);

    painter.setFont(valueFont);


    QString affichage =
        QString::number(valeur,'f',  0  );


    QRectF zoneValeur(centre.x() - 70, centre.y() + 45, 140,35);


    painter.drawText(zoneValeur, Qt::AlignCenter, affichage   );
}
