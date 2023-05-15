#include "CardData.h"

bool CardData::FindString(const QString &sToFind) const
{
	if(m_sName.contains(sToFind))
		return true;

	for(auto objButton : m_vecButtonData){
		if(QString::number(objButton.m_nConnectionID).contains(sToFind))
			return true;
	}

	for(auto objWorker : m_vecWorkerData){
		if(objWorker.m_sName.contains(sToFind))
			return true;

		if(objWorker.m_sNumber.contains(sToFind))
			return true;

		if(objWorker.m_sPosition.contains(sToFind))
			return true;
	}

	if(m_sAdditionalInfo.contains(sToFind))
		return true;

	return false;
}
