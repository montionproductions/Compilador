#include "LocalNode.h"



CLocalNode::CLocalNode()
{
}


CLocalNode::~CLocalNode()
{
}

void CLocalNode::Save(std::ofstream * file)
{
	*file << m_category << ',';
	*file << m_type << ',';
	*file << m_context_name << ',';
	*file << m_iDimention << ',';
	if (ptrLocal != nullptr)
		ptrLocal->Save(file);
	else
		*file << "null,";

	if (ptrNext != nullptr)
		ptrNext->Save(file);
	else
		*file << "null";

}
