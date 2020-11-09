#include "printer.h"
#include "ui_printer.h"
#include <iostream>
#include <QSettings>
PrintSetter::PrintSetter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintSetter)
{
    ui->setupUi(this);
    ui->enTete->setFont(QFont("Courier"));
    m_bold = false;
    m_oblique = false;

    QSettings settings;

    /*ui->lettreC->setChecked(settings.value("printer/choice/lettre").toBool());
    ui->lettreQ->setChecked(settings.value("printer/question/lettre").toBool());
    ui->numC->setChecked(settings.value("printer/choice/num").toBool());
    ui->numQ->setChecked(settings.value("printer/question/num").toBool());
    ui->affC->setCurrentIndex(settings.value("printer/choice/affIndex").toInt());
    ui->affQues->setCurrentIndex(settings.value("printer/question/affIndex").toInt());
    ui->persoC->setDisabled(settings.value("printer/choice/affDisabled").toBool());
    if(ui->persoC->isEnabled())
        ui->persoC->setText(settings.value("printer/choice/affText").toString());
    ui->persoQues->setDisabled(settings.value("printer/question/affDisabled").toBool());
    if(ui->persoQues->isEnabled())
        ui->persoQues->setText(settings.value("printer/question/affText").toString());
    ui->boldC->setChecked(settings.value("printer/choice/bold").toBool());
    ui->fontC->setCurrentIndex(settings.value("printer/choice/font").toInt());
    ui->fontSizeC->setCurrentIndex(settings.value("printer/choice/fontSize").toInt());
    ui->boldQ->setChecked(settings.value("printer/question/bold").toBool());
    ui->fontQ->setCurrentIndex(settings.value("printer/question/font").toInt());
    ui->fontSizeQ->setCurrentIndex(settings.value("printer/question/fontSize").toInt());
    ui->nbQues->setValue(settings.value("printer/question/nb").toInt());
    ui->orderQ->setCurrentIndex(settings.value("printer/question/order").toInt());
    ui->nbCh->setValue(settings.value("printer/choice/nb").toInt());
    ui->orderC->setCurrentIndex(settings.value("printer/choice/order").toInt());

    ui->enTete->setHtml(settings.value("printer/entete/text").toString());*/

    connect(ui->enTete, SIGNAL(cursorPositionChanged()), this, SLOT(actuBut()));
}
int PrintSetter::nbQues() const{
    return ui->nbQues->value();
}
int PrintSetter::nbChoice() const{
    return ui->nbCh->value();
}
bool PrintSetter::randQues() const{
    return ui->orderQ->currentIndex() == 1;
}
void PrintSetter::setNbQues(const int &n){
    ui->nbQues->setValue(n);
}
void PrintSetter::setNbChoice(const int &n){
    ui->nbCh->setValue(n);
}
void PrintSetter::setMaxC(const int &n){
    ui->nbCh->setMaximum(n);
}
void PrintSetter::setMaxQ(const int &n){
    ui->nbQues->setMaximum(n);
}
bool PrintSetter::randChoices() const{
    return ui->orderC->currentIndex() == 1;
}
QTextEdit *PrintSetter::text() const{return ui->enTete;}
QString PrintSetter::preC() const{return ui->affC->currentText();}
QString PrintSetter::preQ() const{return ui->affQues->currentText();}
bool PrintSetter::boldC() const{return ui->boldC->isChecked();}
bool PrintSetter::boldQ() const{return ui->boldQ->isChecked();}
QString PrintSetter::persoC() const{return ui->persoC->text();}
QString PrintSetter::persoQ() const{return ui->persoQues->text();}
bool PrintSetter::letterC() const{return ui->lettreC->isChecked();}
bool PrintSetter::letterQ() const{return ui->lettreQ->isChecked();}
PDF::Font PrintSetter::fontC() const{
    if(boldC()){
        if(ui->fontC->currentText() == "Courier")
            return PDF::Font::COURIER_BOLD;
        else if(ui->fontC->currentText() == "Times New Roman")
            return PDF::Font::TIMES_BOLD;
        else
            return PDF::Font::HELVETICA_BOLD;
    }
    else{
        if(ui->fontC->currentText() == "Courier")
            return PDF::Font::COURIER;
        else if(ui->fontC->currentText() == "Times New Roman")
            return PDF::Font::TIMES;
        else
            return PDF::Font::HELVETICA;
    }

}
int PrintSetter::exec(){
    int r = QDialog::exec();

    QSettings settings;

    settings.setValue("printer/choice/lettre", ui->lettreC->isChecked());
    settings.setValue("printer/question/lettre", ui->lettreQ->isChecked());
    settings.setValue("printer/choice/num", ui->numC->isChecked());
    settings.setValue("printer/question/num", ui->numQ->isChecked());
    settings.setValue("printer/choice/aff", ui->affC->currentIndex());
    settings.setValue("printer/question/aff", ui->affQues->currentIndex());



    return r;
}

PDF::Font PrintSetter::fontQ() const{
    if(boldQ()){
        if(ui->fontQ->currentText() == "Courier")
            return PDF::Font::COURIER_BOLD;
        else if(ui->fontQ->currentText() == "Times New Roman")
            return PDF::Font::TIMES_BOLD;
        else
            return PDF::Font::HELVETICA_BOLD;
    }
    else{
        if(ui->fontQ->currentText() == "Courier")
            return PDF::Font::COURIER;
        else if(ui->fontQ->currentText() == "Times New Roman")
            return PDF::Font::TIMES;
        else
            return PDF::Font::HELVETICA;
    }
}

int PrintSetter::fontSizeC() const{return ui->fontSizeC->currentText().toInt();}
int PrintSetter::fontSizeQ() const{return ui->fontSizeQ->currentText().toInt();}

void PrintSetter::actuBut(){
    switch(ui->enTete->currentFont().pointSize()){
    case 6: ui->fontSizeE->setCurrentIndex(0); break;
    case 7: ui->fontSizeE->setCurrentIndex(1); break;
    case 8:ui->fontSizeE->setCurrentIndex(2); break;
    case 9:ui->fontSizeE->setCurrentIndex(3); break;
    case 10:ui->fontSizeE->setCurrentIndex(4); break;
    case 11:ui->fontSizeE->setCurrentIndex(5); break;
    case 12:ui->fontSizeE->setCurrentIndex(6); break;
    case 14:ui->fontSizeE->setCurrentIndex(7); break;
    case 16:ui->fontSizeE->setCurrentIndex(8); break;
    case 18:ui->fontSizeE->setCurrentIndex(9); break;
    case 20:ui->fontSizeE->setCurrentIndex(10); break;
    case 22:ui->fontSizeE->setCurrentIndex(11); break;
    case 24:ui->fontSizeE->setCurrentIndex(12); break;
    case 26:ui->fontSizeE->setCurrentIndex(13); break;
    case 28:ui->fontSizeE->setCurrentIndex(14); break;
    case 36:ui->fontSizeE->setCurrentIndex(15); break;
    case 48:ui->fontSizeE->setCurrentIndex(16); break;
    case 72:ui->fontSizeE->setCurrentIndex(17); break;
    }
    if(ui->enTete->fontFamily() == "Courier")
        ui->fontE->setCurrentIndex(0);
    else if(ui->enTete->fontFamily() == "Helvetica")
        ui->fontE->setCurrentIndex(1);
    else ui->fontE->setCurrentIndex(2);
    QFont tests(ui->boldE->font());
    tests.setBold(ui->enTete->currentFont().bold());
    ui->boldE->setFont(tests);

    tests = ui->obliqueE->font();
    tests.setItalic(ui->enTete->currentFont().italic());
    ui->obliqueE->setFont(tests);

    tests = ui->leftToRight->font();
    tests.setBold(ui->enTete->alignment() == Qt::AlignLeft);
    ui->leftToRight->setFont(tests);

    tests = ui->rightToLeft->font();
    tests.setBold(ui->enTete->alignment() == Qt::AlignRight);
    ui->rightToLeft->setFont(tests);

    tests = ui->center->font();
    tests.setBold(ui->enTete->alignment() == Qt::AlignCenter);
    ui->center->setFont(tests);
}
void PrintSetter::on_boldE_clicked(){
    m_bold = !m_bold;

    QFont font(ui->enTete->currentFont());
    font.setBold(m_bold);
    ui->enTete->setCurrentFont(font);


    QFont fontB(ui->boldE->font());
    fontB.setBold(m_bold);
    ui->boldE->setFont(fontB);
}
void PrintSetter::on_fontE_currentIndexChanged(int const& i){
    ui->enTete->setCurrentFont(QFont(ui->fontE->currentText()));
}
void PrintSetter::on_obliqueE_clicked(){
    m_oblique = !m_oblique;

    QFont font(ui->enTete->currentFont());
    font.setItalic(m_oblique);
    ui->enTete->setCurrentFont(font);

    QFont fontB(ui->obliqueE->font());
    fontB.setItalic(m_oblique);
    ui->obliqueE->setFont(fontB);
}
void PrintSetter::on_fontSizeE_currentIndexChanged(int const& i){
    QFont font(ui->enTete->currentFont().family(), ui->enTete->currentFont().pointSize());
    font.setPointSize(ui->fontSizeE->currentText().toInt());
    ui->enTete->setCurrentFont(font);
}
void PrintSetter::on_leftToRight_clicked(){
    ui->enTete->setAlignment(Qt::AlignLeft);
    QFont font(ui->leftToRight->font());

    ui->center->setFont(font);
    ui->rightToLeft->setFont(font);

    font.setBold(true);
    ui->leftToRight->setFont(font);
}
void PrintSetter::on_rightToLeft_clicked(){
    ui->enTete->setAlignment(Qt::AlignRight);

    QFont font(ui->rightToLeft->font());

    ui->center->setFont(font);
    ui->leftToRight->setFont(font);

    font.setBold(true);
    ui->rightToLeft->setFont(font);
}
void PrintSetter::on_center_clicked(){
    ui->enTete->setAlignment(Qt::AlignCenter);

    QFont font(ui->center->font());

    ui->rightToLeft->setFont(font);
    ui->leftToRight->setFont(font);

    font.setBold(true);
    ui->center->setFont(font);
}

void PrintSetter::on_affQues_currentIndexChanged(int const& i){
    ui->persoQues->setEnabled(i == 9);
}
void PrintSetter::on_boldQ_clicked(){
    if(ui->boldQ->isChecked())
        ui->resultQ->setText("<strong>Résultat<!strong>");
    else
        ui->resultQ->setText("Résultat");
}
void PrintSetter::on_fontQ_currentIndexChanged(int const& i){
    ui->resultQ->setFont(QFont(ui->fontQ->currentText(), ui->resultQ->font().pointSize()));
}
void PrintSetter::on_fontSizeQ_currentIndexChanged(int const& i){
    ui->resultQ->setFont(QFont(ui->resultQ->font().family(), ui->fontSizeQ->currentText().toInt()));
}

void PrintSetter::on_affC_currentIndexChanged(int const& i)
{
    ui->persoC->setEnabled(i == 3);
}
void PrintSetter::on_boldC_clicked(){
    if(ui->boldC->isChecked())
        ui->resultC->setText("<strong>Résultat<!strong>");
    else
        ui->resultC->setText("Résultat");
}
void PrintSetter::on_fontC_currentIndexChanged(int const& i){
    ui->resultC->setFont(QFont(ui->fontC->currentText(), ui->resultC->font().pointSize()));
}
void PrintSetter::on_fontSizeC_currentIndexChanged(int const& i){
    ui->resultC->setFont(QFont(ui->resultC->font().family(), ui->fontSizeC->currentText().toInt()));
}
PrintSetter::PrintSetter(const PrintSetter &prtStr){
    ui = prtStr.ui;
}


Print::Print(const PrintSetter &prtStr,
             const vector<Question*> &questions, const QString &path):
    m_pdf(),
    m_printSetter(prtStr),     
    m_xTaken(50),
    m_yTaken(0),
    m_questions(questions),
    m_path(path){}
bool Print::printToPdf(){
    writeHead();
    writeBody();
    writeBottom();
    std::string a; 
    return m_pdf.writeToFile(toString(m_path), a);

}

void Print::writeHead(){
    //std::cout << m_printSetter.text()->toHtml().toStdString() << std::endl;
    //QString a;

}
void Print::writeBody(){
    vector<Question*> questions = chooseQuestions();



    int yUseNext = 0;
    const quint8 fontSizeQ = m_printSetter.fontSizeQ();
    const quint8 fontSizeC = m_printSetter.fontSizeC();
    const PDF::Font fontQ = m_printSetter.fontQ();
    const PDF::Font fontC = m_printSetter.fontC();
    const quint16 width = m_pdf.getWidth()-100;
    const quint8 qsize = questions.size();

    int yuse = 0;
    for(quint64 i(0); i<qsize; i++){
        if(yuse > 730)
            m_pdf.newPage();


        m_pdf.setFont(fontQ, fontSizeQ);
        std::string r = toString(getIntitQ(*questions[i]));
        vector<std::string> words = m_pdf.wrapText(r, 100, false);

        for(quint64 n(0), wSize(words.size()); n<wSize; n++){
            m_pdf.showTextXY(words[n], 50, 745-yuse);
            yuse += 20;
        }

        m_pdf.setFont(fontC, fontSizeC);
        for(quint64 j(0), n(m_questions[i]->choices().size()); j<n; j++){
            r = toString(getIntitC(i, j, *questions[i]->choices()[j]));
            words = m_pdf.wrapText(r, 100, false);
            for(quint64 x(0), m(words.size()); x<m; x++){


                m_pdf.showTextXY(words[x], 50, 745-yuse);
                yuse += 20;
            }
        }

    }

    /*for(quint8 i(0); i<qsize; i++){
        yUseNext = 0;
        if(i+1 < qsize)

            yUseNext += addCountY(m_pdf.wrapText(toString(getIntitQ(*questions[i+1])), width, false),
                                  fontSizeQ);
        if(m_yTaken + yUseNext > 705){
            m_pdf.newPage();
            m_yTaken = 0;
            m_xTaken = 50;
        }

        addLine();

        m_pdf.setFont(fontQ, fontSizeQ);

        addText(getIntitQ(*questions[i]), fontSizeQ);

        m_xTaken = 50;

        const quint8 csize = questions[i]->choices().size();

        for(quint8 j(0); j<csize;j++){
            if(i+1 < qsize && j < questions[i+1]->choices().size())
                yUseNext += addCountY(m_pdf.wrapText(toString(getIntitC(i,j,*questions[i+1]->choices()[j])), width, false),
                                     fontSizeC);

            m_pdf.setFont(fontC, fontSizeC);
            addText(getIntitC(i, j, *questions[i]->choices()[j]), fontSizeC);
            m_xTaken = 50;
        }
    }*/
}
void Print::writeBottom(){

}
void Print::addLine(){
    m_yTaken += 20;
    m_pdf.showTextXY("", m_xTaken, 745-m_yTaken);
}
void Print::addText(const QString &t, const uchar &fontSize){
    vector<string> words = wordsOf(toString(t));
    for(unsigned i(0); i<words.size(); i++){
        addWord(words[i], fontSize);
    }
    m_yTaken += fontSize;
}
void Print::addWord(const std::string &word, const uchar &fontSize){
    if(m_xTaken + int(unsigned(fontSize)*word.size()/1.5) > m_pdf.getWidth()-50+fontSize){
        m_yTaken += fontSize;
        m_xTaken = 50;
    }
    for(unsigned i(0); i<word.size(); i++, m_xTaken += int(fontSize/1.5)){
        m_pdf.showTextXY(word[i], m_xTaken, 745-m_yTaken);

    }
}
vector<string> Print::wordsOf(const string &str){
    vector<string> words;
    string current;
    for(unsigned i(0); i<str.size(); i++){
        if(str[i] != ' ')
            current += str[i];
        else{
            words.push_back(current+" ");
            current = "";
        }
    }
    words.push_back(current);
    return words;
}
QString Print::getIntitQ(const Question &ques){
    if(m_printSetter.preQ() == "Personaliser"){
        if(m_printSetter.letterQ()){
            return m_printSetter.persoQ().replace("&X", QString(ques.num()+97)) + " " + ques.name(0);
        }
        else
            return m_printSetter.persoQ().replace("&X", ques.num("")) + " "+ques.name(0);
    }
    else{
        if(m_printSetter.letterQ()){
            return m_printSetter.preQ().replace("&X",QString(ques.num()+96)) + " " + ques.name(0);
        }
        else
            return m_printSetter.preQ().replace("&X", ques.num("")) + " "+ques.name(0);
    }
}
QString Print::getIntitC(const quint8 i, const quint8 j, const Choice& c){
    if(m_printSetter.preC() == "Personnaliser..."){
        if(m_printSetter.letterC()){
            return m_printSetter.persoC().replace("&X", QString(j+97)) + " " + c.name();
        }
        else
            return m_printSetter.persoC().replace("&X", QString().setNum(j+1)) + " "+c.name();
    }
    else{
        if(m_printSetter.letterC()){
            return m_printSetter.preC().replace("&X", QString(j+97)) + " " + c.name();
        }
        else
            return m_printSetter.preC().replace("&X", QString().setNum(j+1)) + " "+c.name();
    }
}
int Print::addCountY(vector<std::string> intit, int fontSize){
    int yTaken = 0,
        xTaken = 50;
    for(unsigned t(0); t<intit.size(); t++, yTaken += fontSize+8){
        for(unsigned t2(0); t2<intit[t].size(); t2++, xTaken+=int(fontSize/1.5)){
            if(xTaken > PDF().getWidth()-50){
                yTaken += fontSize+8;
                xTaken = 50;
            }
        }
    }
    return yTaken;
}
vector<Choice*> Print::chooseChoices(const Question *q, const uchar &n, const bool &random){
    bool containOk = false;

    unsigned posOk = -1;
    for(unsigned i(0); i<q->choices().size(); i++){
        if(q->choices()[i]->isCorrect())
            posOk = i;
    }

    vector<Choice*> r;

    if(random){
        vector<unsigned> posAvailable;
        for(unsigned i(0); i<q->choices().size(); i++)
            posAvailable.push_back(i);

        for(uchar tempPos(0); tempPos < n; tempPos++){

            unsigned pos = rand()%posAvailable.size();

            unsigned i = posAvailable[pos];
            posAvailable.erase(vector<unsigned>::iterator(posAvailable.begin()+pos));

            Choice temp = *q->choices()[i];
            temp.setNum(tempPos+49);

            r.push_back(new Choice(temp));
            if(i == posOk)
                containOk = true;
        }
    }
    else{
        for(unsigned i(0); i<n && i<q->choices().size(); i++){
            r.push_back(new Choice(*q->choices()[i]));
            if(i == posOk)
                containOk = true;
        }

    }
    if(!containOk){
        unsigned randPos = rand()%r.size();
        delete r[randPos];
        r[randPos] = new Choice(*q->choices()[posOk]);
    }
    return r;

}
vector<Question*> Print::chooseQuestions(){
    vector<Question*> r = sortQuestions(m_printSetter.nbQues(), m_printSetter.randQues());

    quint8 nbChoice = m_printSetter.nbChoice();
    bool rnd = m_printSetter.randChoices();

    for(unsigned i(0); i<r.size(); i++){
        r[i]->setChoices(chooseChoices(r[i], nbChoice, rnd));
    }

    return r;
}
vector<Question*> Print::sortQuestions(const uchar &number, const bool &random){
    vector<Question*> returned;

    if(random){
        vector<unsigned> posAvailable;
        for(unsigned i(0); i<m_questions.size(); i++)
            posAvailable.push_back(i);

        for(uchar tempPos(0); tempPos < number; tempPos++){

            unsigned pos = rand()%posAvailable.size();

            unsigned i = posAvailable[pos];
            posAvailable.erase(vector<unsigned>::iterator(posAvailable.begin()+pos));

            Question temp(*m_questions[i]);
            temp.setNum(tempPos+49);
            for(int i(0); i<temp.choices().size(); i++){
                std::cout << temp.choices()[i]->name().toStdString() << "\n";
            }

            returned.push_back(new Question(temp));

        }
    }
    else{
        for(unsigned i(0); i<number && i<m_questions.size(); i++){
            returned.push_back(new Question(*m_questions[i]));
        }
    }

    return returned;
}
string Print::toString(const QString &q){
    std::string returned = "";
    for(int i(0); i<q.size(); i++)
        returned += q[i].toLatin1();
    return returned;
}
void check(const vector<Question*> questions){
    
}
