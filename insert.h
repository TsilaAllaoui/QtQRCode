#pragma once

#include <QWidget>
#include "ui_insert.h"

class Insert : public QWidget
{
	Q_OBJECT

public:
	Insert(QWidget *parent = Q_NULLPTR);
	~Insert();

private:
	Ui::Insert ui;
};
