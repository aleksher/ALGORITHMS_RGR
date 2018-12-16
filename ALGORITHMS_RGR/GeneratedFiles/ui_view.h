/********************************************************************************
** Form generated from reading UI file 'view.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_View
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *gbPlayMode;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rbBandit;
    QRadioButton *rbPoliceman;
    QGroupBox *groupBox;
    QLineEdit *m_lineEdit;
    QLineEdit *n_lineEdit;
    QGroupBox *gbLevel;
    QVBoxLayout *verticalLayout_3;
    QSpinBox *sbAILevel;
    QPushButton *pbPlay;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *View)
    {
        if (View->objectName().isEmpty())
            View->setObjectName(QStringLiteral("View"));
        View->setWindowModality(Qt::NonModal);
        View->resize(915, 800);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(View->sizePolicy().hasHeightForWidth());
        View->setSizePolicy(sizePolicy);
        View->setMinimumSize(QSize(515, 400));
        View->setMaximumSize(QSize(1500, 1000));
        View->setBaseSize(QSize(500, 400));
        centralWidget = new QWidget(View);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(100, 0));
        widget->setMaximumSize(QSize(115, 16777215));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, 0, -1);
        gbPlayMode = new QGroupBox(widget);
        gbPlayMode->setObjectName(QStringLiteral("gbPlayMode"));
        gbPlayMode->setMinimumSize(QSize(0, 0));
        gbPlayMode->setMaximumSize(QSize(91, 16777215));
        verticalLayout_2 = new QVBoxLayout(gbPlayMode);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        rbBandit = new QRadioButton(gbPlayMode);
        rbBandit->setObjectName(QStringLiteral("rbBandit"));
        rbBandit->setChecked(true);

        verticalLayout_2->addWidget(rbBandit);

        rbPoliceman = new QRadioButton(gbPlayMode);
        rbPoliceman->setObjectName(QStringLiteral("rbPoliceman"));

        verticalLayout_2->addWidget(rbPoliceman);


        verticalLayout->addWidget(gbPlayMode);

        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(0, 80));
        m_lineEdit = new QLineEdit(groupBox);
        m_lineEdit->setObjectName(QStringLiteral("m_lineEdit"));
        m_lineEdit->setGeometry(QRect(10, 20, 71, 20));
        m_lineEdit->setMaximumSize(QSize(71, 16777215));
        n_lineEdit = new QLineEdit(groupBox);
        n_lineEdit->setObjectName(QStringLiteral("n_lineEdit"));
        n_lineEdit->setGeometry(QRect(10, 50, 71, 20));
        n_lineEdit->setMaximumSize(QSize(71, 16777215));

        verticalLayout->addWidget(groupBox);

        gbLevel = new QGroupBox(widget);
        gbLevel->setObjectName(QStringLiteral("gbLevel"));
        gbLevel->setMaximumSize(QSize(91, 16777215));
        verticalLayout_3 = new QVBoxLayout(gbLevel);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        sbAILevel = new QSpinBox(gbLevel);
        sbAILevel->setObjectName(QStringLiteral("sbAILevel"));
        sbAILevel->setMaximumSize(QSize(91, 16777215));
        sbAILevel->setMinimum(1);
        sbAILevel->setMaximum(4);
        sbAILevel->setValue(3);

        verticalLayout_3->addWidget(sbAILevel);


        verticalLayout->addWidget(gbLevel);

        pbPlay = new QPushButton(widget);
        pbPlay->setObjectName(QStringLiteral("pbPlay"));
        pbPlay->setMaximumSize(QSize(91, 16777215));

        verticalLayout->addWidget(pbPlay);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        gbPlayMode->raise();
        gbLevel->raise();
        pbPlay->raise();
        groupBox->raise();

        horizontalLayout->addWidget(widget);

        View->setCentralWidget(centralWidget);

        retranslateUi(View);

        QMetaObject::connectSlotsByName(View);
    } // setupUi

    void retranslateUi(QMainWindow *View)
    {
        View->setWindowTitle(QApplication::translate("View", "View", nullptr));
        gbPlayMode->setTitle(QApplication::translate("View", "Play mode", nullptr));
        rbBandit->setText(QApplication::translate("View", "bandit", nullptr));
        rbPoliceman->setText(QApplication::translate("View", "policeman", nullptr));
        groupBox->setTitle(QApplication::translate("View", "Size", nullptr));
        m_lineEdit->setPlaceholderText(QApplication::translate("View", "m", nullptr));
        n_lineEdit->setPlaceholderText(QApplication::translate("View", "n", nullptr));
        gbLevel->setTitle(QApplication::translate("View", "Level", nullptr));
        pbPlay->setText(QApplication::translate("View", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class View: public Ui_View {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_H
