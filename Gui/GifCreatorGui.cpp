#include <QtWidgets>
// #include <QToolButton>
#include <iostream>
#include "GifCreatorGui.hpp"
#include "ObjectList.hpp"

GifCreatorGui::GifCreatorGui(QWidget* parent)
	: QMainWindow(parent)
{
	initWindow();
	createCentralWidget();
	createLowerDock();
	createButtons();
}

void GifCreatorGui::initWindow()
{
	setWindowTitle(tr("Gif Creator"));
	resize(800, 600);
}

void GifCreatorGui::createCentralWidget()
{
	movie_ = new QMovie(this);

	movieLabel_ = new QLabel(tr("No project selected"), this);
	movieLabel_->setAlignment(Qt::AlignCenter);
	movieLabel_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	movieLabel_->setBackgroundRole(QPalette::Dark);
	movieLabel_->setAutoFillBackground(true);
	
	setCentralWidget(movieLabel_);
}

void GifCreatorGui::createLowerDock()
{
	lowerDock_ = new QDockWidget(this);
	lowerDock_->setFeatures(QDockWidget::NoDockWidgetFeatures);
	deleteBoarder(lowerDock_);
	addDockWidget(Qt::BottomDockWidgetArea, lowerDock_);
}

void GifCreatorGui::createButtons()
{
	openProject_ = new QPushButton(QLatin1String("Open Project"), this);
	play_ = new QPushButton(QLatin1String("Play"), this);

	QObject::connect(openProject_, &QPushButton::clicked, [this]{ openProject(); });

	auto* layout = new QHBoxLayout(this);
	layout->addWidget(openProject_);
	layout->addStretch();
	layout->addWidget(play_);

	auto* lowerDockMultiWidget_ = new QWidget(this);
	lowerDockMultiWidget_->setLayout(layout);
	lowerDock_->setWidget(lowerDockMultiWidget_);
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
	auto* titleBarWidget = new QWidget(this);
	dw->setTitleBarWidget(titleBarWidget);
	dw->titleBarWidget()->hide();
}
