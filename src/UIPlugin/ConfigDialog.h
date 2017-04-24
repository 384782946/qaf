#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include "ui_ConfigDialog.h"
#include <QDialog>

class QSortFilterProxyModel;

namespace QAF
{
    class ConfigDialog : public QDialog
	{
		Q_OBJECT

	public:
		ConfigDialog(QWidget *parent = 0);
		~ConfigDialog();

	private slots:
		void on_pushButtonOK_clicked(bool);
		void on_pushButtonCancel_clicked(bool);
		void on_pushButtonApply_clicked(bool);
		void on_pushButtonFilter_clicked(bool);
		void on_treeView_clicked(const QModelIndex &);

	private:
		Ui::ConfigDialog ui;
		QSortFilterProxyModel* mModel;
	};
}

#endif // CONFIGDIALOG_H
