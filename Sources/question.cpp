#include "Headers\question.h"

Question::Question(const QString &name, const unsigned &choices, const unsigned &index)
{

    m_layout = new QFormLayout;
        m_name = new QLineEdit(name);
        m_layout->addRow(QString().setNum(index)+"/", m_name);

    for(unsigned i(0); i<choices; i++){
        m_choices.push_back(new QLineEdit(""));
        m_layout->addRow(QString(char(97+i))+")", m_choices[i]);
    }

    m_add = new QPushButton("+");
    m_del = new QPushButton("-");

}
