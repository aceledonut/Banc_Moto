QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    IMAGES_MOTO/LedOff.bmp \
    IMAGES_MOTO/LedRouge.bmp \
    IMAGES_MOTO/LedVerte.bmp \
    IMAGES_MOTO/Roue_Arrierre.jpg \
    IMAGES_MOTO/Roue_Avant.jpg \
    IMAGES_MOTO/Rouleau.jpg \
    IMAGES_MOTO/cligd0.bmp \
    IMAGES_MOTO/cligd1.bmp \
    IMAGES_MOTO/cligg0.bmp \
    IMAGES_MOTO/cligg1.bmp \
    README.md \
    Roue_Arrierre.jpg \
    Roue_Avant.jpg \
    Rouleau.jpg

RESOURCES += \
    photo.qrc
