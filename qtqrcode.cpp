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

	// Making cell width dynamic
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	// Instantiating form widget
	insert = new Insert();
	insert->hide();

}

void QtQRCode::on_loginButton_clicked()
{
	// Creating connection to database
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

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
	QSqlTableModel model;
	model.setTable(ui.tableText->text());
	model.select();

	// Setting row and column counts
	ui.tableWidget->setRowCount(model.rowCount());
	ui.tableWidget->setColumnCount(model.columnCount());

	// Getting table headers
	QStringList headers;
	for (int i = 0; i < ui.tableWidget->columnCount(); i++)
		headers.append(model.record().fieldName(i));

	// Setting table widget headers
	ui.tableWidget->setHorizontalHeaderLabels(headers);

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

void QtQRCode::on_insertButton_clicked()
{
	// Show form widget
	if (insert->isHidden())
		insert->show();
}

