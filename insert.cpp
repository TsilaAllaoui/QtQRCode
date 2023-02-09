#include "insert.h"
#include <QSqlRecord>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>

Insert::Insert(QSqlTableModel* model, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// Updating model instance
	this->model = model;

	// Getting table headers
	for (int i = 1; i < this->model->columnCount(); i++)
		headers.append(this->model->record().fieldName(i));

	// Creating fields inputs for data insertion
	QVBoxLayout* vLayout = new QVBoxLayout(this);
	for (auto& header : headers)
	{
		QHBoxLayout* hLayout = new QHBoxLayout();
		hLayout->addWidget(new QLabel(header));
		QLineEdit* lineEdit = new QLineEdit();
		hLayout->addWidget(lineEdit);
		lineEdits.emplace_back(lineEdit);
		vLayout->addLayout(hLayout);
	}

	// Adding button
	button = new QPushButton("Add");
	vLayout->addWidget(button);

	// Sonnecting slot and button
	QObject::connect(button, &QPushButton::clicked, this, &Insert::addRow);
}

Insert::~Insert()
{

}

void Insert::addRow()
{
	// Creating record to add to table
	QSqlRecord record = model->record();
	record.setValue("ID", QString::number(model->rowCount() + 1));
	for (int i=0; i<lineEdits.size(); i++)
		record.setValue(headers[i], lineEdits[i]->text());

	// Insert record to table
	if (model->insertRecord(-1, record)) 
	{
		QMessageBox::information(this, "Success", "Item added succefully", QMessageBox::Ok);
		model->submitAll();
	}
	else {
		QMessageBox::critical(this, "Error", "Error adding item", QMessageBox::Ok);
	}

	this->close();
}