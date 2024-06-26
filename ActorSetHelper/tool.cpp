#include "widget.h"
#include "tool.h"
#include <fbsdk/fbconsole.h>

//--- Registration defines
#define MYACTSET__CLASS MYACTSET__CLASSNAME
#define MYACTSET__LABEL "Original_ActorSetHelper"
#define MYACTSET__DESC	"OR - Actor Set Helper"

//--- FiLMBOX implementation and registration
FBToolImplementation( MYACTSET__CLASS );
FBRegisterTool		( MYACTSET__CLASS,
					  MYACTSET__LABEL,
					  MYACTSET__DESC,
					  FB_DEFAULT_SDK_ICON);

QWidget* CreateMyActSetWidget(QWidget* pParent) {
	MyActSetWidget* lWidget = new MyActSetWidget(pParent);
	return lWidget;
}

bool MyActSet::FBCreate()
{
	StartSize[0] = 300;
	StartSize[1] = 275;

	// Create UI
	UICreate();
	return true;
}

void MyActSet::FBDestroy() {
}

void MyActSet::UICreate()
{
    AddRegion("ParentedWidget", "ActorSetHelper",
        0, kFBAttachLeft, "", 1.0,
        0, kFBAttachTop, "", 1.0,
        0, kFBAttachRight, "", 1.0,
        0, kFBAttachBottom, "", 1.0);

    mQtHolder.SetCreator( CreateMyActSetWidget );
    SetControl( "ParentedWidget", mQtHolder );
}