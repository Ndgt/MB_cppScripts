#ifndef TOOL_H
#define TOOL_H

#include <fbsdk/fbsdk.h> 

#define MYACTSET__CLASSNAME MyActSet
#define MYACTSET__CLASSSTR "MyActSet"

class MyActSet : public FBTool {
	//--- FiLMBOX Tool declaration
	FBToolDeclare(MyActSet, FBTool);

public:
	//--- FiLMBOX Construction/Destruction,
	virtual bool FBCreate();		//!< FiLMBOX Creation function.
	virtual void FBDestroy();		//!< FiLMBOX Destruction function.

private:
	/* UI Creation */
	void UICreate();

private:
	FBWidgetHolder mQtHolder;
};

#endif // TOOL_H