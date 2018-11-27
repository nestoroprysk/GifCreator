#pragma once

#include <QMainWindow>

class QWidget;
class QMovie;
class QLabel;
class QDockWidget;
class QPushButton;
class AList;

class GifCreatorGui : public QMainWindow
{
	Q_OBJECT

public:
	GifCreatorGui(QWidget* parent = nullptr);
	~GifCreatorGui();

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
	void createLeftDock();
	QDockWidget* leftDock_ = nullptr;

private:
	void createLeftList();
	AList* leftList_ = nullptr;

private:
	void createRightDock();
	QDockWidget* rightDock_ = nullptr;

private:
	void createRightList();
	AList* rightList_ = nullptr;

private:
	void openProject();

private:
	static void deleteBoarder(QDockWidget*);
};
