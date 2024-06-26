#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets/QWidget>
#include "ui_actorsethelper.h"
#include <fbsdk/fbsdk.h>
#include "BodyIndex.h"

class MyActSetWidget : public QWidget
					 , private Ui_toolWidget
{
	Q_OBJECT
public:
	MyActSetWidget( QWidget* pParent = 0 );
	virtual ~MyActSetWidget();

public slots:
	void CreateActorMarkerSet();
	void FitToTrackers();
	void RotateYdeg();
	void ResetAll();
	void AdjustActorSize(int);
	void BindMarkerModel();

private:
	FBActor* actor;
	FBSystem* sys;
	MyActSet_MarkertSetIndex* mIndex;
};


#endif // WIDGET_H