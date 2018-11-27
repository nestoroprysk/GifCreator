#include <QtWidgets>

#include "ObjectList.hpp"
#include "BehaviourList.hpp"
#include "GifCreatorGui.hpp"

GifCreatorGui::GifCreatorGui(QWidget* parent)
	: QMainWindow(parent)
{
	initWindow();
	createCentralWidget();
	createLowerDock();
	createButtons();
	createLeftDock();
	createLeftList();
	createRightDock();
	createRightList();
}

void GifCreatorGui::initWindow()
{
	setWindowTitle(tr("Gif Creator"));
	resize(800, 600);
}

void GifCreatorGui::createCentralWidget()
{
	movieLabel_ = new QLabel(tr("No project selected"), this);
	movieLabel_->setAlignment(Qt::AlignCenter);
	movieLabel_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	movieLabel_->setBackgroundRole(QPalette::Dark);
	movieLabel_->setAutoFillBackground(true);

	movie_ = new QMovie(movieLabel_);
	
	setCentralWidget(movieLabel_);
}

void GifCreatorGui::createLowerDock()
{
	lowerDock_ = new QDockWidget;
	lowerDock_->setFeatures(QDockWidget::NoDockWidgetFeatures);
	deleteBoarder(lowerDock_);
	addDockWidget(Qt::BottomDockWidgetArea, lowerDock_);
}

void GifCreatorGui::createButtons()
{
	openProject_ = new QPushButton(QLatin1String("Open Project"));
	play_ = new QPushButton(QLatin1String("Play"));

	QObject::connect(openProject_, &QPushButton::clicked, [this]{ openProject(); });

	auto* layout = new QHBoxLayout;
	layout->addWidget(openProject_);
	layout->addStretch();
	layout->addWidget(play_);

	auto* lowerDockMultiWidget_ = new QWidget(this);
	lowerDockMultiWidget_->setLayout(layout);
	lowerDock_->setWidget(lowerDockMultiWidget_);
}

void GifCreatorGui::createLeftDock()
{
	leftDock_ = new QDockWidget(QLatin1String("Objects"));
	leftDock_->setMinimumSize(70, 70);
	leftDock_->setFeatures(QDockWidget::NoDockWidgetFeatures);
	addDockWidget(Qt::LeftDockWidgetArea, leftDock_);
	setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
}

void GifCreatorGui::createLeftList()
{
	leftList_ = new ObjectList;
	leftDock_->setWidget(leftList_);
}

void GifCreatorGui::createRightDock()
{
	rightDock_ = new QDockWidget(QLatin1String("Behaviours"));
	rightDock_->setMinimumSize(70, 70);
	rightDock_->setFeatures(QDockWidget::NoDockWidgetFeatures);
	addDockWidget(Qt::RightDockWidgetArea, rightDock_);
}

void GifCreatorGui::createRightList()
{
	rightList_ = new BehaviourList;
	rightDock_->setWidget(rightList_);
	setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

void GifCreatorGui::openProject()
{
	auto fileName = QFileDialog::getOpenFileName(this, tr("Open a projevt"));
	movie_->stop();
	movieLabel_->setMovie(movie_);
	movie_->setFileName(fileName);
	movie_->start();
}

void GifCreatorGui::deleteBoarder(QDockWidget* dw)
{
	auto* titleBarWidget = new QWidget;
	dw->setTitleBarWidget(titleBarWidget);
	dw->titleBarWidget()->hide();
}

GifCreatorGui::~GifCreatorGui()
{
	delete leftList_;
}
