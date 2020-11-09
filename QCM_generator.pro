QT += widgets

SOURCES += \
	Login/pwdforgot.cpp \
	Login/signin.cpp \
    Print/printbase.cpp \
        Print/printer.cpp \
        Print/ToPdf\pdf.cpp \
        Print/ToPdf\metrics.cpp \
	Project/Temp/tempchoice.cpp \
	Project/Temp/tempproject.cpp \
	Project/Temp/tempquestion.cpp \
        Project/about.cpp \
	Project/choice.cpp \
        Project/project.cpp \
        Project/thanks.cpp \
	Project/qcmedit.cpp \
	Project/question.cpp \
        main.cpp
HEADERS += \
	Login/pwdforgot.h \
	Login/signin.h \
    Print/printbase.h \
        Print/printer.h \
        Print/ToPdf/pdf.h \
        Print/ToPdf/metrics.h \
	Project/Temp/tempchoice.h \
	Project/Temp/tempproject.h \
	Project/Temp/tempquestion.h \
        Project/about.h \
	Project/choice.h \
        Project/project.h \
        Project/thanks.h \
	Project/qcmedit.h \
        Project/question.h

FORMS += \
	Login/login.ui \
	Login/signin.ui \
    Print/printbase.ui \
	Print/printer.ui \
        Project/about.ui \
        Project/qcmedit.ui \
        Project/thanks.ui
RESOURCES += \
    themes.qrc
