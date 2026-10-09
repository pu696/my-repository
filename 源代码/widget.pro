QT       += core gui widgets

CONFIG   += c++17

# 源文件
SOURCES += main.cpp \
           widget.cpp \
           user.cpp \
           calculate.cpp \
           questionbank.cpp \
           record.cpp

# 头文件
HEADERS += widget.h \
           user.h \
           calculate.h \
           questionbank.h \
           record.h

# UI文件
FORMS += widget.ui

# 部署
DESTDIR = ./bin
OBJECTS_DIR = ./obj
MOC_DIR = ./moc
RCC_DIR = ./rcc
