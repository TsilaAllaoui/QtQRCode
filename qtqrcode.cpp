#include "qtqrcode.h"
#include <QtSql>

QtQRCode::QtQRCode(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// Init connection status as Disconnected
	isConnected = false;
	ui.statusValueLabel->setText("Disconnected");
	ui.statusValueLabel->setStyleSheet("color: red;");

	// Set username as root by default
	ui.usernameText->setText("root");

	// Making cell width dynamic
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void QtQRCode::on_loginButton_clicked()
{
	// Creating connection to database
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

	// Opening database at localhost
	db.setDatabaseName("products");
	db.setHostName("localhost");

	// Credentials
	db.setUserName(ui.usernameText->text());
	db.setPassword(ui.passwordText->text());

	// If connexion is successful
	if (!db.open())
	{
		ui.statusValueLabel->setText("Connection Error.");
		ui.statusValueLabel->setText("Disconnected");
		ui.statusValueLabel->setStyleSheet("color: red;");
		isConnected = false;
	}

	// If connexion is failed
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
	QSqlTableModel model;
	model.setTable("items");
	model.select();

	// Setting row and column counts
	ui.tableWidget->setRowCount(model.rowCount());
	ui.tableWidget->setColumnCount(model.columnCount());

	// Getting table headers
	std::vector<QString> headers;
	for (int i=0; i<ui.tableWidget->columnCount(); i++)
		headers.emplace_back(model.record().fieldName(i));

	// Fetching data from table and show in widget
	for (int i = 0; i < model.rowCount(); ++i) 
	{
		int j = 0;
		for (auto& header : headers)
		{
			QString value = model.record(i).value(header).toString();
			QTableWidgetItem* item = new QTableWidgetItem(value);
			ui.tableWidget->setItem(i, j, item);
			j++;
		}
	}
}

