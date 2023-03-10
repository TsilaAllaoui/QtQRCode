#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtqrcode.h"
#include "insert.h"
#include <QSqlDatabase>

class QtQRCode : public QMainWindow
{
	Q_OBJECT

	public:
		QtQRCode(QWidget *parent = Q_NULLPTR);
		Insert* insert;

	private:
		Ui::QtQRCodeClass ui;
		bool isConnected;
		QSqlDatabase db;
		QSqlTableModel* model;

	private slots:
		void on_loginButton_clicked();
		void on_refreshButton_clicked();
		void on_insertButton_clicked();

};
