#ifndef CHOICE_H
#define CHOICE_H

#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
class Choice : public QWidget
{
    Q_OBJECT
public:
    Choice(const QString &name = "", const char &num = 1, const bool &isCorrect = false, QWidget *parent = nullptr);
    ~Choice();

    QString name() const;
    unsigned char num() const;
    bool isCorrect() const;
    QHBoxLayout* layout();

    void setNum(unsigned char n);

public slots:
    void del();

signals:
    void destroyed(int const& index);

private:
    QPushButton *m_delete;
    QLineEdit *m_name;
    QLabel *m_num;
    QCheckBox *m_correct;
    QHBoxLayout *m_layout;
};

#endif // CHOICE_H