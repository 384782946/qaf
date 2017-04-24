#include "ConfigDialog.h"
#include <ConfigSystem.h>
#include <ConfigModel.h>
#include <QAFContext.h>

namespace QAF
{
	ConfigDialog::ConfigDialog(QWidget *parent)
        : QDialog(parent)
		, mModel(0)
	{
		ui.setupUi(this);

		mModel = new ConfigProxyModel(this);
		using namespace QAF;
		ConfigSystem* configSystem = static_cast<ConfigSystem*>(QAFContext::getSingleton()->getSystem(ST_CONFIG));
		ConfigModel* configModel = configSystem->getConfig("run");
		if (configModel){
			mModel->setSourceModel(configModel);
			mModel->setFilterRole(Qt::DisplayRole);
			mModel->setFilterKeyColumn(0);
			mModel->setDynamicSortFilter(false);
			mModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
		}
		
		ui.treeView->setModel(mModel);
		ui.treeView->header()->setStretchLastSection(true);
	}

	ConfigDialog::~ConfigDialog()
	{

	}

	void ConfigDialog::on_pushButtonOK_clicked(bool)
	{
		this->accept();
	}

	void ConfigDialog::on_pushButtonCancel_clicked(bool)
	{
		this->reject();
	}

	void ConfigDialog::on_pushButtonApply_clicked(bool)
	{
		
	}

	void ConfigDialog::on_pushButtonFilter_clicked(bool)
	{
		QString regx = ui.lineEdit->text();
		mModel->setFilterRegExp(regx);
	}

	void ConfigDialog::on_treeView_clicked(const QModelIndex &index)
	{
		QString str = ui.treeView->model()->data(index, Qt::StatusTipRole).toString();
		ui.lineEditPath->setText(str);
	}
}
