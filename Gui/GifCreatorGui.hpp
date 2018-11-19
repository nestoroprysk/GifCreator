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
	GifCreatorGui(QWidget* parent = 0);

public:
	void saveProject();
	void openProject(const QString& fileName);
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
	QLabel* movieLabel = nullptr;
	QMovie* movie = nullptr;
	QToolButton* applyButton = nullptr;
	QToolButton* createButton = nullptr;
	QToolButton* openButton = nullptr;
	QToolButton* closeButton = nullptr;
	QToolButton* playButton = nullptr;
	QToolButton* saveButton = nullptr;
	QToolButton* pauseButton = nullptr;
	QToolButton* stopButton = nullptr;
	QCheckBox* fitCheckBox = nullptr;
	QSlider* frameSlider = nullptr;
	QSpinBox* speedSpinBox = nullptr;
	QLabel* frameLabel = nullptr;
	QLabel* speedLabel = nullptr;

private:
	QGridLayout* controlsLayout = nullptr;
	QHBoxLayout* buttonsLayout = nullptr;
	QVBoxLayout* mainLayout = nullptr;
};
