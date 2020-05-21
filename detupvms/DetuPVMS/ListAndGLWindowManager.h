/************************************************
* \file ListAndGLWindowManager.h
*
* \author HuZhengdong 
* \date 20170721
* 在线保存设备列表和glwindow的对应关系,维护两个map
************************************************/
#pragma once
#include <iostream>
#include <string>
#include <map>
#include <memory>

#include <QObject>

#include "UiSingleton.h"

#define  ListAndGLWindowManagerIns ListAndGLWindowManager::Instance()

class DetuPVMS;

class ListAndGLWindowManager :public QObject, public CUiSingleton<ListAndGLWindowManager>
{
	Q_OBJECT
		friend class CUiSingleton<ListAndGLWindowManager>;
private:
	ListAndGLWindowManager();

public:
	void UpdateMap(int list_item_num, int glwindow_num);
	void RemoveMap(int list_item_num, int glwindow_num);
	int GetGLValue(int key);
	int  GetItemValue(int key);
	void ClearMap();

	int getMapSize();

private:
	DetuPVMS *mainwindow_;

	std::map<int, int > list_item_to_glwindow_;
	std::map<int, int > glwindow_to_list_item_;
};

