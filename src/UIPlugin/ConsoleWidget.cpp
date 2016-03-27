#include "ConsoleWidget.h"
#include "qafcore.h"
#include "LogModel.h"

#include <QStandardItemModel>
#include <QSortFilterProxyModel>

ConsoleWidget::ConsoleWidget(QWidget *parent)
	: QWidget(parent)
	, mModel(NULL)
{
	ui.setupUi(this);

	mModel = new QSortFilterProxyModel(this);
	mModel->setSourceModel(QAFCorePtr->getLogModel());
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
		<< LStr("全部")
		<< LStr("信息")
		<< LStr("调试")
		<< LStr("警告")
		<< LStr("危险")
		<< LStr("错误"));
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
