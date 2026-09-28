#include "PropertyDelegateQMarginsF.h"

#include "QtnProperty/Delegates/PropertyDelegateFactory.h"
#include "QtnProperty/PropertyDelegateAttrs.h"
#include "QtnProperty/Utils/DoubleSpinBox.h"

#include <QLineEdit>

QtnPropertyDelegateQMarginsF::QtnPropertyDelegateQMarginsF(
    QtnPropertyQMarginsFBase &owner)
    : QtnPropertyDelegateTypedEx<QtnPropertyQMarginsFBase>(owner)
    , m_precision(std::numeric_limits<qreal>::digits10 - 1)
{
	addSubProperty(owner.createLeftProperty());
	addSubProperty(owner.createTopProperty());
	addSubProperty(owner.createRightProperty());
	addSubProperty(owner.createBottomProperty());
}

void QtnPropertyDelegateQMarginsF::Register(QtnPropertyDelegateFactory &factory)
{
	factory.registerDelegateDefault(&QtnPropertyQMarginsFBase::staticMetaObject,
	                                &qtnCreateDelegate<QtnPropertyDelegateQMarginsF, QtnPropertyQMarginsFBase>,
	                                "QMarginsF");
}

extern void qtnApplyQMarginsDelegateAttributes(QtnPropertyDelegate *to,
                                            const QtnPropertyDelegateInfo &info);

void QtnPropertyDelegateQMarginsF::applyAttributesImpl(
    const QtnPropertyDelegateInfo &info)
{
	info.loadAttribute(qtnPrecisionAttr(), m_precision);
	m_precision = qBound(0, m_precision, std::numeric_limits<qreal>::digits10);
	qtnApplyQMarginsDelegateAttributes(this, info);
}

QWidget *QtnPropertyDelegateQMarginsF::createValueEditorImpl(
    QWidget *parent, const QRect &rect, QtnInplaceInfo *inplaceInfo)
{
	return createValueEditorLineEdit(parent, rect, true, inplaceInfo);
}

bool QtnPropertyDelegateQMarginsF::propertyValueToStrImpl(QString &strValue) const
{
	auto value = owner().value();

	QLocale locale;
	strValue = QString("[(%1, %2, %3, %4)]")
	               .arg(QtnDoubleSpinBox::valueToText(value.left(), locale, m_precision, true),
	                    QtnDoubleSpinBox::valueToText(value.top(), locale, m_precision, true),
	                    QtnDoubleSpinBox::valueToText(value.right(), locale, m_precision, true),
	                    QtnDoubleSpinBox::valueToText(value.bottom(), locale, m_precision, true));

	return true;
}

