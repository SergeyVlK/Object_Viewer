QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../edge_counter.c \
    ../matrix/s21_calc_complements.c \
    ../matrix/s21_common.c \
    ../matrix/s21_create_matrix.c \
    ../matrix/s21_determinant.c \
    ../matrix/s21_eq_matrix.c \
    ../matrix/s21_inverse_matrix.c \
    ../matrix/s21_mult_matrix.c \
    ../matrix/s21_mult_number.c \
    ../matrix/s21_remove_matrix.c \
    ../matrix/s21_sub_matrix.c \
    ../matrix/s21_sum_matrix.c \
    ../matrix/s21_transpose.c \
    ../model.c \
    ../render.c \
    ../settings.c \
    ../transformation.c \
    main.cpp \
    mainwindow.cpp \
    modelview.cpp

HEADERS += \
    ../matrix/s21_common.h \
    ../matrix/s21_matrix.h \
    ../model.h \
    ../matrix/s21_common.h \
    ../matrix/s21_matrix.h \
    ../model.h \
    ../settings.h \
    mainwindow.h \
    modelview.h


include (QtGifImage/src/gifimage/qtgifimage.pri)

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    QtGifImage/qtgifimage.pro
