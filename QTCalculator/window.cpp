#include "window.h"
#include "action.h"
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QValidator>
#include <QObject>

Window::Window(QWidget *parent) : QWidget(parent)
{

        this -> actionObject = new action;
        QLineEdit* firstOperator = new QLineEdit();
        firstOperator->setValidator(new QDoubleValidator());
        QLineEdit* secondOperator = new QLineEdit();
        secondOperator->setValidator(new QDoubleValidator());


        QGridLayout* layout = new QGridLayout();
        layout->addWidget(firstOperator, 1, 1);
        layout->addWidget(secondOperator, 1, 2);

        QObject::connect(
                        firstOperator,
                        SIGNAL(textChanged(QString)),
                        this->actionObject,
                        SLOT(SetOperator1(QString))
                        );


         QObject::connect(
                        secondOperator,
                        &QLineEdit::textChanged,
                        this->actionObject,
                        &action::SetOperator2
                        );

        QPushButton *btnPlus = new QPushButton("+");
        QPushButton *btnMinus = new QPushButton("-");
        QPushButton *btnMult = new QPushButton("*");
        QPushButton *btnDiv = new QPushButton("/");
        QPushButton *btnPow = new QPushButton("^");
        QPushButton *btnRoot = new QPushButton("√");
        QPushButton *btnLn = new QPushButton("ln");
        QPushButton *btnSin = new QPushButton("sin");
        QPushButton *btnCos = new QPushButton("cos");
        QPushButton *btnTan = new QPushButton("tan");

        layout->addWidget(btnPlus, 1, 3);
        layout->addWidget(btnMinus, 2, 2);
        layout->addWidget(btnMult, 2, 3);
        layout->addWidget(btnDiv, 3, 1);
        layout->addWidget(btnPow, 3, 2);
        layout->addWidget(btnRoot, 3, 3);
        layout->addWidget(btnLn, 2, 1);
        layout->addWidget(btnSin, 4, 1);
        layout->addWidget(btnCos, 4, 2);
        layout->addWidget(btnTan, 4, 3);


        QObject::connect(
                        btnPlus,
                        &QPushButton::clicked,
                        this->actionObject,
                        &action::initPLus
                        );

        QObject::connect(
                    btnMinus,
                    &QPushButton::clicked,
                    this->actionObject,
                    &action::initMinus
                    );

        QObject::connect(
                    btnMult,
                    &QPushButton::clicked,
                    this->actionObject,
                    &action::initMult
                    );

        QObject::connect(
                    btnDiv,
                    &QPushButton::clicked,
                    this->actionObject,
                    &action::initDiv
                    );

        QObject::connect(
                    btnPow,
                    &QPushButton::clicked,
                    this->actionObject,
                    &action::initPow
                    );

        QObject::connect(
                    btnRoot,
                    &QPushButton::clicked,
                    this->actionObject,
                    &action::initRoot
                    );

        QObject::connect(
                    btnLn,
                    &QPushButton::clicked,
                    this->actionObject,
                    &action::initLn
                    );

        QObject::connect(
                    btnSin,
                    &QPushButton::clicked,
                    this->actionObject,
                    &action::initSin
                    );

        QObject::connect(
                    btnCos,
                    &QPushButton::clicked,
                    this->actionObject,
                    &action::initCos
                    );

        QObject::connect(
                    btnTan,
                    &QPushButton::clicked,
                    this->actionObject,
                    &action::initTan
                    );






        QLineEdit* result = new QLineEdit();
        result->setReadOnly(true);
        QObject::connect(
                    this->actionObject,
                    &action::setResult,
                    result,
                    &QLineEdit::setText
                    );


        layout->addWidget(result, 5, 1, 1, 3);

        this->setMaximumWidth(300);
        this->setMaximumHeight(400);

        this->setLayout(layout);


}
