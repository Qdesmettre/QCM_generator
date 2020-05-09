QT += widgets

SOURCES += \
	Core/ProjectEdit/choice.cpp \
	Core/Login/login.cpp \
    Core/ProjectEdit/printer.cpp \
	Core/main.cpp \
	Core/ProjectEdit/project.cpp \
	Core/ProjectEdit/projectassist.cpp \
	Core/Login/pwdforgot.cpp \
	Core/ProjectEdit/qcmedit.cpp \
	Core/ProjectEdit/question.cpp \
        Core/Login/signin.cpp \
        Core/ProjectEdit/pdf.cpp \
        Core/ProjectEdit/metrics.cpp

HEADERS += \
	Core/ProjectEdit/choice.h \
	Core/Login/login.h \
    Core/ProjectEdit/printer.h \
	Core/ProjectEdit/project.h \
	Core/ProjectEdit/projectassist.h \
	Core/Login/pwdforgot.h \
	Core/ProjectEdit/qcmedit.h \
	Core/ProjectEdit/question.h \
        Core/Login/signin.h \
        Core/ProjectEdit/pdf.h \
        Core/ProjectEdit/metrics.h

FORMS += \
	Core/Login/login.ui \
	Core/ProjectEdit/printer.ui \
	Core/ProjectEdit/projectassist.ui \
	Core/ProjectEdit/qcmedit.ui \
	Core/Login/signin.ui
TRANSLATIONS = QCM_generator_en.ts QCM_generator_es.ts QCM_generator_fr.ts
