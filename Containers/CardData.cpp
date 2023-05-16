#include "CardData.h"

bool CardData::FindString(const QString &sToFind) const
{
	if(m_sName.contains(sToFind))
		return true;

	for(const auto &objButton : m_vecButtonData){
		if(QString::number(objButton.m_nConnectionID).contains(sToFind, Qt::CaseInsensitive))
			return true;
	}

	for(const auto &objWorker : m_vecWorkerData){
		if(objWorker.m_sName.contains(sToFind, Qt::CaseInsensitive))
			return true;

		if(objWorker.m_sNumber.contains(sToFind, Qt::CaseInsensitive))
			return true;

		if(objWorker.m_sPosition.contains(sToFind, Qt::CaseInsensitive))
			return true;
	}

	if(m_sAdditionalInfo.contains(sToFind, Qt::CaseInsensitive))
		return true;

	return false;
}
