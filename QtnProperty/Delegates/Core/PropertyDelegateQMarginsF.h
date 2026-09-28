#ifndef PROPERTY_DELEGATE_QMARGINSF_H
#define PROPERTY_DELEGATE_QMARGINSF_H

#include "QtnProperty/Delegates/Utils/PropertyDelegateMisc.h"
#include "QtnProperty/Core/PropertyQMarginsF.h"

class QTN_IMPORT_EXPORT QtnPropertyDelegateQMarginsF
    : public QtnPropertyDelegateTypedEx<QtnPropertyQMarginsFBase>
{
	Q_DISABLE_COPY(QtnPropertyDelegateQMarginsF)

	int m_precision;

public:
	QtnPropertyDelegateQMarginsF(
	    QtnPropertyQMarginsFBase &owner);

	static void Register(QtnPropertyDelegateFactory &factory);

protected:
	virtual void applyAttributesImpl(
	    const QtnPropertyDelegateInfo &info) override;

	virtual QWidget *createValueEditorImpl(QWidget *parent, const QRect &rect,
	                                       QtnInplaceInfo *inplaceInfo = nullptr) override;

	virtual bool propertyValueToStrImpl(QString &strValue) const override;

private:
	enum
	{
		LEFT = 0,
		TOP = 1,
		RIGHT = 2,
		BOTTOM = 3
	};
};

#endif // PROPERTY_DELEGATE_QMARGINSF_H
