#include "LocalNode.h"



CLocalNode::CLocalNode()
{
}


CLocalNode::~CLocalNode()
{
}

void CLocalNode::Save(std::ofstream * file)
{
	switch (m_category)
	{
	case Category::Global:
		*file << " {Globa,";
		break;
	case Category::Local:
		*file << " {Local,";
		break;
	case Category::Param:
		*file << " {Param,";
		break;
	case Category::Indef:
		*file << " {Indef,";
		break;
	case Category::Process:
		*file << " {Process,";
		break;
	case Category::Function:
		*file << " {Function,";
		break;
	default:
		break;
	}

	switch (m_type)
	{
	case Type::FLOAT:
		*file << "Float,";
		break;
	case Type::INT:
		*file << "Int,";
		break;
	case Type::STRING:
		*file << "String,";
		break;
	case Type::BOOLEAN:
		*file << "Boolean,";
		break;
	case Type::INDEF:
		*file << "Indef,";
		break;
	default:
		break;
	}

	*file << m_context_name << ',';
	*file << m_iDimention << ',';
	if (ptrLocal != nullptr)
		ptrLocal->Save(file);
	else
		*file << "null,";

	if (ptrNext != nullptr)
		ptrNext->Save(file);
	else
		*file << "null} ";

}
