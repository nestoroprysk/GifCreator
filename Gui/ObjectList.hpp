#ifndef LISTVIEWEXAMPLE_H
#define LISTVIEWEXAMPLE_H
 
#include <QListView>
#include <QStandardItemModel>
#include <QApplication>
 
class ListViewExample : public QWidget
{
	Q_OBJECT
 
public:
        ListViewExample( QWidget *parent=0);
 
private slots:
 
private:
        int nrow, ncol;
        QListView *m_listView;
};
 
#endif
