#include "ListAndGLWindowManager.h"


ListAndGLWindowManager::ListAndGLWindowManager()
{
// 	list_item_to_glwindow_.clear();
// 	glwindow_to_list_item_.clear();
}

void ListAndGLWindowManager::UpdateMap(int list_item_num, int glwindow_num)
{
	list_item_to_glwindow_[list_item_num] = glwindow_num;
	glwindow_to_list_item_[glwindow_num] = list_item_num;
}

void ListAndGLWindowManager::RemoveMap(int list_item_num, int glwindow_num)
{
	list_item_to_glwindow_.erase(list_item_num);
	glwindow_to_list_item_.erase(glwindow_num);
}

int ListAndGLWindowManager::GetGLValue(int key)
{
	 return list_item_to_glwindow_[key]; 
}

int ListAndGLWindowManager::GetItemValue(int key)
{
	 return glwindow_to_list_item_[key]; 
}

void ListAndGLWindowManager::ClearMap()
{
	list_item_to_glwindow_.clear();
	glwindow_to_list_item_.clear();
}

int ListAndGLWindowManager::getMapSize()
{
	return list_item_to_glwindow_.size();
}

