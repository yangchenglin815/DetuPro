#pragma once
#ifndef MEDIAFILEITEM_H
#define MEDIAFILEITEM_H

#include <QListWidgetItem>


class MediaFileItem : public QListWidgetItem
{
public:
    MediaFileItem();
    ~MediaFileItem();

private: 
	bool is_playing_;
};

#endif // MEDIAFILEITEM_H
