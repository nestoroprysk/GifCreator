#pragma once

#include <QWidget>

class QCheckBox;
class QGridLayout;
class QHBoxLayout;
class QLabel;
class QMovie;
class QSlider;
class QSpinBox;
class QToolButton;
class QVBoxLayout;

class GifCreatorGui : public QWidget
{
	Q_OBJECT

public:
	GifCreatorGui(QWidget *parent = 0);

public:
	void saveProject();
	void openProject(const QString &fileName);
	void closeProject();

private slots:
	void create();
	void open();
	void close();
	void save();
	void goToFrame(int frame);
	void fitToWindow();
	void updateFitToWindow();
	void updateFrameSlider();
	void updateSpeedSlider();
	void updateButtons();

private:
	void createControls();
	void createButtons();

private:
	QString currentMovieDirectory;
	QLabel *movieLabel;
	QMovie *movie;
	QToolButton *applyButton;
	QToolButton *createButton;
	QToolButton *openButton;
	QToolButton *closeButton;
	QToolButton *playButton;
	QToolButton *saveButton;
	QToolButton *pauseButton;
	QToolButton *stopButton;
	QCheckBox *fitCheckBox;
	QSlider *frameSlider;
	QSpinBox *speedSpinBox;
	QLabel *frameLabel;
	QLabel *speedLabel;

private:
	QGridLayout *controlsLayout;
	QHBoxLayout *buttonsLayout;
	QVBoxLayout *mainLayout;
};
