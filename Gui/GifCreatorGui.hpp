#pragma once

#include <QMainWindow>

class QWidget;
class QMovie;
class QLabel;
class QDockWidget;
class QPushButton;

class GifCreatorGui : public QMainWindow
{
	Q_OBJECT

public:
	GifCreatorGui(QWidget* parent = nullptr);

private:
	void initWindow();

private:
	void createCentralWidget();
	QMovie* movie_ = nullptr;
	QLabel* movieLabel_ = nullptr;

private:
	void createButtons();
	QPushButton* openProject_ = nullptr;
	QPushButton* play_ = nullptr;

private:
	void createLowerDock();
	QDockWidget* lowerDock_ = nullptr;

private:
	void openProject();

private:
	void deleteBoarder(QDockWidget*);
};
