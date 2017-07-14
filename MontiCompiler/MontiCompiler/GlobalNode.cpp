#include "GlobalNode.h"



CGlobalNode::CGlobalNode()
{
}


CGlobalNode::~CGlobalNode()
{
}

std::string CGlobalNode::GetInfo()
{
	std::string info;
	info = m_name + ",";
	info += m_category + ',';
	info += m_type + ',';
	info += m_iDimension + ',';
	info += "null,";
	if(ptrLocal != nullptr)
		info += ptrLocal->GetInfo() + ",";
	if (ptrNext != nullptr)
		info += ptrNext->GetInfo() + ",";
	return info;
}
