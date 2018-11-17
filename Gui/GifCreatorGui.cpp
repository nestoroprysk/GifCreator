#include <QtWidgets>

#include "GifCreatorGui.hpp"

GifCreatorGui::GifCreatorGui(QWidget *parent)
	: QWidget(parent)
{
	movie = new QMovie(this);
	movie->setCacheMode(QMovie::CacheAll);

	movieLabel = new QLabel(tr("No project selected"));
	movieLabel->setAlignment(Qt::AlignCenter);
	movieLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	movieLabel->setBackgroundRole(QPalette::Dark);
	movieLabel->setAutoFillBackground(true);

	currentMovieDirectory = "movies";

	createControls();
	createButtons();

	connect(movie, SIGNAL(frameChanged(int)), this, SLOT(updateFrameSlider()));
	connect(movie, SIGNAL(stateChanged(QMovie::MovieState)),
			this, SLOT(updateFitToWindow()));
	connect(movie, SIGNAL(stateChanged(QMovie::MovieState)),
			this, SLOT(updateSpeedSlider()));
	connect(movie, SIGNAL(stateChanged(QMovie::MovieState)),
			this, SLOT(updateButtons()));
	connect(fitCheckBox, SIGNAL(clicked()), this, SLOT(fitToWindow()));
	connect(frameSlider, SIGNAL(valueChanged(int)), this, SLOT(goToFrame(int)));
	connect(speedSpinBox, SIGNAL(valueChanged(int)),
			movie, SLOT(setSpeed(int)));

	mainLayout = new QVBoxLayout;
	mainLayout->addWidget(movieLabel);
	mainLayout->addLayout(controlsLayout);
	mainLayout->addLayout(buttonsLayout);
	setLayout(mainLayout);

	updateFitToWindow();
	updateFrameSlider();
	updateSpeedSlider();
	updateButtons();

	setWindowTitle(tr("Gif Creator"));
	resize(400, 400);
}

void GifCreatorGui::create()
{

}

void GifCreatorGui::close()
{
	movie->stop();
	movieLabel->clear();
	movieLabel->setText(tr("No project selected"));

	updateFrameSlider();
	updateSpeedSlider();
	updateButtons();
}

void GifCreatorGui::open()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open a Movie"),
							   currentMovieDirectory);
	if (!fileName.isEmpty())
		openProject(fileName);
}

void GifCreatorGui::save()
{

}

void GifCreatorGui::openProject(const QString &fileName)
{
	currentMovieDirectory = QFileInfo(fileName).path();

	movie->stop();
	movieLabel->setMovie(movie);
	movie->setFileName(fileName);
	movie->start();

	updateFrameSlider();
	updateSpeedSlider();
	updateButtons();
}

void GifCreatorGui::goToFrame(int frame)
{
	movie->jumpToFrame(frame);
}

void GifCreatorGui::fitToWindow()
{
	movieLabel->setScaledContents(fitCheckBox->isChecked());
}

void GifCreatorGui::updateFitToWindow()
{
	fitCheckBox->setEnabled(movie->isValid());
}

void GifCreatorGui::updateFrameSlider()
{
	bool hasFrames = (movie->currentFrameNumber() >= 0);

	if (hasFrames) {
		if (movie->frameCount() > 0) {
			frameSlider->setMaximum(movie->frameCount() - 1);
		} else {
			if (movie->currentFrameNumber() > frameSlider->maximum())
				frameSlider->setMaximum(movie->currentFrameNumber());
		}
		frameSlider->setValue(movie->currentFrameNumber());
	} else {
		frameSlider->setMaximum(0);
	}
	frameLabel->setEnabled(hasFrames);
	frameSlider->setEnabled(hasFrames);
}

void GifCreatorGui::updateSpeedSlider()
{
	speedLabel->setEnabled(movie->isValid());
	speedSpinBox->setEnabled(movie->isValid());
}

void GifCreatorGui::updateButtons()
{
	closeButton->setEnabled(movie->isValid()); // if project opened
	playButton->setEnabled(movie->isValid() && movie->frameCount() != 1
						   && movie->state() == QMovie::NotRunning);
	applyButton->setEnabled(movie->isValid()); // if project opened
	saveButton->setEnabled(movie->isValid()); // if changes made
	pauseButton->setEnabled(movie->state() != QMovie::NotRunning);
	pauseButton->setChecked(movie->state() == QMovie::Paused);
	stopButton->setEnabled(movie->state() != QMovie::NotRunning);
}

void GifCreatorGui::createControls()
{
	fitCheckBox = new QCheckBox(tr("Fit to window"));

	frameLabel = new QLabel(tr("Frame:"));

	frameSlider = new QSlider(Qt::Horizontal);
	frameSlider->setTickPosition(QSlider::TicksBelow);
	frameSlider->setTickInterval(10);

	speedLabel = new QLabel(tr("Speed:"));

	speedSpinBox = new QSpinBox;
	speedSpinBox->setRange(1, 9999);
	speedSpinBox->setValue(100);
	speedSpinBox->setSuffix(tr("%"));
	speedSpinBox->setStyleSheet("color: rgb(110,110,110); ");

	controlsLayout = new QGridLayout;
	controlsLayout->addWidget(fitCheckBox, 0, 0, 1, 2);
	controlsLayout->addWidget(frameLabel, 1, 0);
	controlsLayout->addWidget(frameSlider, 1, 1, 1, 2);
	controlsLayout->addWidget(speedLabel, 2, 0);
	controlsLayout->addWidget(speedSpinBox, 2, 1);
	controlsLayout->setAlignment(Qt::AlignLeft);
}

void GifCreatorGui::createButtons()
{
	QSize iconSize(24, 24);

	applyButton = new QToolButton;
	applyButton->setIcon(style()->standardIcon(QStyle::SP_DialogApplyButton));
	applyButton->setIconSize(iconSize);
	applyButton->setToolTip(tr("Apply changes"));
	connect(applyButton, SIGNAL(clicked()), this, SLOT(create()));

	createButton = new QToolButton;
	createButton->setIcon(style()->standardIcon(QStyle::SP_DirHomeIcon));
	createButton->setIconSize(iconSize);
	createButton->setToolTip(tr("Create project"));
	connect(createButton, SIGNAL(clicked()), this, SLOT(create()));

	openButton = new QToolButton;
	openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
	openButton->setIconSize(iconSize);
	openButton->setToolTip(tr("Open project"));
	connect(openButton, SIGNAL(clicked()), this, SLOT(open()));

	closeButton = new QToolButton;
	closeButton->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
	closeButton->setIconSize(iconSize);
	closeButton->setToolTip(tr("Close project"));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	saveButton = new QToolButton;
	saveButton->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
	saveButton->setIconSize(iconSize);
	saveButton->setToolTip(tr("Save project"));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(save()));

	playButton = new QToolButton;
	playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
	playButton->setIconSize(iconSize);
	playButton->setToolTip(tr("Play"));
	connect(playButton, SIGNAL(clicked()), movie, SLOT(start()));

	pauseButton = new QToolButton;
	pauseButton->setCheckable(true);
	pauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	pauseButton->setIconSize(iconSize);
	pauseButton->setToolTip(tr("Pause"));
	connect(pauseButton, SIGNAL(clicked(bool)), movie, SLOT(setPaused(bool)));

	stopButton = new QToolButton;
	stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
	stopButton->setIconSize(iconSize);
	stopButton->setToolTip(tr("Stop"));
	connect(stopButton, SIGNAL(clicked()), movie, SLOT(stop()));

	buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(applyButton);
	buttonsLayout->addWidget(createButton);
	buttonsLayout->addWidget(openButton);
	buttonsLayout->addWidget(closeButton);
	buttonsLayout->addStretch();
	buttonsLayout->addWidget(saveButton);
	buttonsLayout->addWidget(playButton);
	buttonsLayout->addWidget(pauseButton);
	buttonsLayout->addWidget(stopButton);
}
