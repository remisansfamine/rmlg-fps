#include "key_axis.hpp"

namespace Core::Input
{
	KeyAxis::KeyAxis(int negativeKeyID, int positiveKeyID)
		: m_positiveKeyID(positiveKeyID), m_negativeKeyID(negativeKeyID)
	{ }

	void KeyAxis::compute()
	{
		m_value = (float)(glfwGetKey(window, m_positiveKeyID) - glfwGetKey(window, m_negativeKeyID));
	}

	float KeyAxis::getValue()
	{
		return m_value;
	}
}