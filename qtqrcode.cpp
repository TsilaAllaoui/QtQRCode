#include <QtSql>

#include "qtqrcode.h"

QtQRCode::QtQRCode(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// Init connection status as Disconnected
	isConnected = false;
	ui.statusValueLabel->setText("Disconnected");
	ui.statusValueLabel->setStyleSheet("color: red;");

	// Setting default parameters
	ui.dbText->setText("products");
	ui.ipText->setText("localhost");
	ui.tableText->setText("items");

	// Set username as root by default
	ui.usernameText->setText("root");

	// Instanciating attributes
	model = new QSqlTableModel;
}

void QtQRCode::on_loginButton_clicked()
{
	// Creating connection to database
	db = QSqlDatabase::addDatabase("QMYSQL");

	// Opening database at localhost
	db.setDatabaseName(ui.dbText->text());
	db.setHostName(ui.ipText->text());

	// Credentials
	db.setUserName(ui.usernameText->text());
	db.setPassword(ui.passwordText->text());

	// If connexion is failed
	if (!db.open())
	{
		ui.statusValueLabel->setText("Connection Error.");
		ui.statusValueLabel->setText("Disconnected");
		ui.statusValueLabel->setStyleSheet("color: red;");
		isConnected = false;
	}

	// If connexion is successful
	else
	{
		ui.statusValueLabel->setText("Connection Successful.");
		ui.statusValueLabel->setText("Connected");
		ui.statusValueLabel->setStyleSheet("color: green;");
		isConnected = true;
	}
}

void QtQRCode::on_refreshButton_clicked()
{
	// Getting items table
	model = new QSqlTableModel(nullptr, db);
	model->setTable(ui.tableText->text());
	model->select();

	// Showing table contents
	ui.tableView->setModel(model);
}

void QtQRCode::on_insertButton_clicked()
{
	// Creating insert widget
	insert = new Insert(model);

	// Show form widget
	insert->show();
}

