#include "QNoTitleWidget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QStyle>
#include <QToolButton>
#include <QMouseEvent>

QNoTitleWidget::QNoTitleWidget(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
	, mTitleWidget(NULL)
	, mIsDrag(false)
{
	setWindowFlags(Qt::FramelessWindowHint);
}

QNoTitleWidget::~QNoTitleWidget()
{

}

void QNoTitleWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (mIsDrag){
		QPoint movePot = event->globalPos() - mMousePosition;
		//move是移动的位置是相对于全局而言(即屏幕)
		move(movePot);
	}
}

void QNoTitleWidget::mousePressEvent(QMouseEvent *event)
{
	mMousePosition = event->pos();
	QRect geometry = mTitleWidget->geometry();
	mIsDrag = geometry.contains(mMousePosition);
}

void QNoTitleWidget::mouseReleaseEvent(QMouseEvent *event)
{
	mIsDrag = false;
}

void QNoTitleWidget::paintEvent(QPaintEvent *event)
{
	//mTitleWidget->paintEvent();
	QWidget::paintEvent(event);
}

void QNoTitleWidget::init()
{
	mTitleWidget = new QWidget();

	QHBoxLayout* layout = new QHBoxLayout(mTitleWidget);
	mTitleLabel = new QLabel(this->windowTitle(), NULL);
	mMinBtn = new QToolButton(NULL);
	mMinBtn = new QToolButton(NULL);
	mCloseBtn = new QToolButton(NULL);

	//QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
	//QPixmap helpPix = style()->standardPixmap(QStyle::SP_TitleBarContextHelpButton);
	//QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
	//QPixmap maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
	//QPixmap shadePix = style()->standardPixmap(QStyle::SP_TitleBarShadeButton);
	//QPixmap unshadePix = style()->standardPixmap(QStyle::SP_TitleBarUnshadeButton);
	//QPixmap normalPix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);
	//QPixmap menuPix = style()->standardPixmap(QStyle::SP_TitleBarMenuButton);

	//mMinBtn->setIcon(minPix);
	//mMaxBtn->setIcon(maxPix);
	//mCloseBtn->setIcon(closePix);

	//设置最小化、关闭等按钮的样式
	//mMinBtn->setStyleSheet("background-color:transparent;");
	//mMaxBtn->setStyleSheet("background-color:transparent;");
	//mCloseBtn->setStyleSheet("background-color:transparent;");

	layout->addWidget(mTitleLabel);
	//layout->addStretch();
	//layout->addWidget(mMinBtn);
	//layout->addWidget(mMaxBtn);
	//layout->addWidget(mCloseBtn);

	mTitleWidget->setLayout(layout);
	mTitleWidget->setGeometry(QRect(0, 0, this->width(), 20));
}
