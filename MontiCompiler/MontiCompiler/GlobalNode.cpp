#include "GlobalNode.h"



CGlobalNode::CGlobalNode()
{
}


CGlobalNode::~CGlobalNode()
{
}

void CGlobalNode::Save(std::ofstream *file)
{
	*file << m_name << ',';
	*file << m_category << ',';
	*file << m_type << ',';
	*file << m_iDimension << ',';
	*file << "null,";
	if (ptrLocal != nullptr)
		ptrLocal->Save(file);
	else
		*file << "null,";
	if (ptrNext != nullptr)
		ptrNext->Save(file);
	else
		*file << "null";

}
