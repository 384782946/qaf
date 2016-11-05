#ifndef QCUSTOMMAINWINDOW_H
#define QCUSTOMMAINWINDOW_H

#include "qtcustomwidgets_global.h"
#include <QWidget>

class QToolButton;
class QLabel;

class QTCUSTOMWIDGETS_EXPORT QNoTitleWidget : public QWidget
{
public:
	QNoTitleWidget(QWidget *parent = Q_NULLPTR, Qt::WindowFlags flags = Qt::WindowFlags());
	virtual ~QNoTitleWidget();

	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

protected:
	virtual void paintEvent(QPaintEvent *event);

protected:
	bool mIsDrag;
	QLabel* mTitleLabel;
	QToolButton* mMaxBtn;
	QToolButton* mMinBtn;
	QToolButton* mCloseBtn;
	QWidget* mTitleWidget;
	QPoint mMousePosition;
	QLayout* mLayout;
};

#endif // QCUSTOMMAINWINDOW_H
