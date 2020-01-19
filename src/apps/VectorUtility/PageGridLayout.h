#pragma once

#include <QGridLayout>


class PageGridLayout : public QGridLayout
{
public:
    PageGridLayout(QWidget * parent=nullptr);
    QSize maximumSize(void) const;
};

