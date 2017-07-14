#include "LocalNode.h"



CLocalNode::CLocalNode()
{
}


CLocalNode::~CLocalNode()
{
}

std::string CLocalNode::GetInfo()
{
	std::string info;
	info = m_category + ',';
	info += m_type + ',';
	info += m_context_name + ',';
	info += m_iDimention + ',';
	if(ptrLocal != nullptr)
		info += ptrLocal->GetInfo() + ",";
	if (ptrNext != nullptr)
		info += ptrNext->GetInfo() + ",";

	return info;
}
