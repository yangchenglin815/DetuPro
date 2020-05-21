#include "SetAdminMananger.h"


SetAdminMananger::SetAdminMananger() :is_admin_(false)
{
}

void SetAdminMananger::setAdmin(bool is_admin)
{
	is_admin_ = is_admin;
}

