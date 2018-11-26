#include "ObjectList.hpp"

ListViewExample::ListViewExample( QWidget *parent)
    : QWidget( parent )
{
    /*set number of row and column, listview only support 1 column */
    nrow = 8;
    ncol = 3;
 
    /*create QListView */
    m_listView = new QListView(this);
    QStandardItemModel *model = new QStandardItemModel( nrow, 1, this );
 
    //fill model value
    for( int r=0; r<nrow; r++ )
    {
            QString sstr = "[ " + QString::number(r) + " ]";
            QStandardItem *item = new QStandardItem(QString("Idx ") + sstr);
            model->setItem(r, 0, item);
    }
 
    //set model
    m_listView->setModel(model);
}
