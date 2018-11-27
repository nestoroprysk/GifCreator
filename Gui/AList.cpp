#include <QListView>
#include <QStandardItemModel>

#include "AList.hpp"

AList::AList(QWidget* parent)
	: QWidget(parent)
	, listView_(new QListView(this))
{
	listView_->viewport()->setAutoFillBackground(false);
	listView_->setFrameStyle(QFrame::NoFrame);
	const auto nbRows = 10;
	auto* model = new QStandardItemModel(nbRows, 1, this);
	static int id = 0;
	for (auto r = 0; r < nbRows; ++r){
		const auto nb = QString::number(++id);
		auto* item = new QStandardItem(nb);
		model->setItem(r, 0, item);
	}
	listView_->setModel(model);
}
