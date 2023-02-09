#pragma once

#include <QWidget>
#include <QSqlTableModel>
#include <QPushButton>
#include "ui_insert.h"

class Insert : public QWidget
{
	Q_OBJECT

public:
	Insert(QSqlTableModel* model,  QWidget *parent = Q_NULLPTR);
	~Insert();
private slots:
	void addRow();

private:
	Ui::Insert ui;
	QPushButton* button;
	QStringList headers;
	QSqlTableModel* model;
	std::vector<QLineEdit*> lineEdits;
};
