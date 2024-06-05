QT       += core gui sql printsupport network charts serialport



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    RDV.cpp \
    Vehicule.cpp \
    adminequipment.cpp \
    admininvoice.cpp \
    adminpage.cpp \
    adminpiste.cpp \
    adminschedule.cpp \
    adminvehicles.cpp \
    arduino.cpp \
    client.cpp \
    clientmanagement.cpp \
    connection.cpp \
    equipement.cpp \
    equipmanagement.cpp \
    equipspage.cpp \
    historique.cpp \
    invoicerpage.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    newpassword.cpp \
    piste.cpp \
    qcustomplot.cpp \
    resetpassword.cpp \
    schedulerpage.cpp \
    signup.cpp \
    smtp.cpp \
    statistic.cpp \
    technicianpage.cpp \
    utilisateur.cpp

HEADERS += \
    RDV.h \
    Vehicule.h \
    adminequipment.h \
    admininvoice.h \
    adminpage.h \
    adminpiste.h \
    adminschedule.h \
    adminvehicles.h \
    arduino.h \
    client.h \
    clientmanagement.h \
    connection.h \
    equipement.h \
    equipmanagement.h \
    equipspage.h \
    historique.h \
    invoicerpage.h \
    login.h \
    mainwindow.h \
    newpassword.h \
    piste.h \
    qcustomplot.h \
    resetpassword.h \
    schedulerpage.h \
    signup.h \
    smtp.h \
    statistic.h \
    technicianpage.h \
    utilisateur.h

FORMS += \
    adminequipment.ui \
    admininvoice.ui \
    adminpage.ui \
    adminpiste.ui \
    adminschedule.ui \
    adminvehicles.ui \
    clientmanagement.ui \
    equipmanagement.ui \
    equipspage.ui \
    invoicerpage.ui \
    login.ui \
    mainwindow.ui \
    newpassword.ui \
    resetpassword.ui \
    schedulerpage.ui \
    signup.ui \
    statistic.ui \
    technicianpage.ui

# QR library
INCLUDEPATH += C:\Users\Amine\Desktop\vcpkg\buildtrees\libqrencode\src\7b43122ce8-98adfdaeb6.clean
LIBS += -LC:\Users\Amine\Desktop\vcpkg\buildtrees\libqrencode\x86-windows-rel -lqrencode

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:RC_ICONS += images/logo.ico
