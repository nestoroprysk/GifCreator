#pragma once

#include <QWidget>

class QListView;

class AList : public QWidget
{
	Q_OBJECT

public:
	AList(QWidget* parent = nullptr);

private:
	QListView* listView_ = nullptr;
};
