#include "ConsoleWidget.h"
#include <LogModel.h>
#include <QAFContext.h>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

using QAF::QAFContext;

ConsoleWidget::ConsoleWidget(QWidget *parent)
	: QWidget(parent)
	, mModel(nullptr)
{
	ui.setupUi(this);

	mModel = new QSortFilterProxyModel(this);
	mModel->setSourceModel(QAFContext::getSingleton()->getLogModel());
	mModel->setFilterKeyColumn(0);
	//mModel->setFilterRole(Qt::UserRole);
	mModel->setFilterRole(Qt::DisplayRole);
	ui.tableView->setModel(mModel);
	ui.tableView->verticalHeader()->hide();
	ui.tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	//ui.tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	//ui.tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
	ui.tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	ui.comboBox->addItems(QStringList()
		<< QString::fromLocal8Bit("全部")
		<< QString::fromLocal8Bit("信息")
		<< QString::fromLocal8Bit("调试")
		<< QString::fromLocal8Bit("警告")
		<< QString::fromLocal8Bit("危险")
		<< QString::fromLocal8Bit("错误"));
}

ConsoleWidget::~ConsoleWidget()
{

}

void ConsoleWidget::on_comboBox_currentIndexChanged(int type)
{
	if (type == 0)
	{
		mModel->setFilterRegExp("");
	}
	else
	{
		mModel->setFilterRegExp(ui.comboBox->currentText());
	}
}
