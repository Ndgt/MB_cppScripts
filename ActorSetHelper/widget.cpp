#include "widget.h"

MyActSetWidget::MyActSetWidget(QWidget* pParent) : QWidget(pParent)
{
	setupUi(this);
    sys = new FBSystem();
    mIndex = new MyActSet_MarkertSetIndex();
}

MyActSetWidget::~MyActSetWidget() {
    delete sys;
    delete mIndex;
}


/* UI Functions */

void MyActSetWidget::CreateActorMarkerSet() {
    actor = new FBActor("NewActor");
    actor->MarkerSet = new FBMarkerSet("NewMarkerSet");
}

void MyActSetWidget::FitToTrackers() {
    FBModelList targetmodel;
    FBVector3d  targetposition;
    FBGetSelectedModels(targetmodel);

    if (targetmodel.GetCount() == 0) {
        FBMessageBox("Caution", "Error : Select a target Model to fit", "OK");
    }
    else {
        targetmodel.GetAt(0)->GetVector(targetposition, kModelTransformation);
        actor->SetActorTranslation(targetposition);
    }
}

void MyActSetWidget::RotateYdeg() {
    FBVector3d hipvector;
    FBVector3d resultvector;
    actor->GetDefinitionRotationVector(kFBSkeletonHipsIndex, hipvector);
    resultvector = FBVector3d(hipvector[0], hipvector[1] + 180, hipvector[2]);
    actor->SetDefinitionRotationVector(kFBSkeletonHipsIndex, resultvector);
}

void MyActSetWidget::ResetAll() {
    if(actor->mAllocated && actor->MarkerSet->mAllocated){
    //if (sys->Scene->Actors.GetCount() > 0 && sys->Scene->MarkerSets.GetCount() > 0) {
        int check = FBMessageBox("Caution",
            "the Actor and MarkerSet will be removed. \n Are you sure you want to continue?",
            "Yes", "No");
        if (check == 1){
            actor->MarkerSet->FBDelete();
            actor->FBDelete();
            horizontalSlider->setSliderPosition(50);
        }
    }
}

void MyActSetWidget::AdjustActorSize(int pValue) {
    if (actor->Is(actor->TypeInfo)) {
        FBVector3d lScale(pValue / 50.0, pValue / 50.0, pValue / 50.0);

        // Actor SkeletonIndex other than invalid, reference, last index
        for (int lActorIter = kFBSkeletonHipsIndex; lActorIter < kFBSkeletonReferenceIndex; lActorIter++) {
            actor->SetDefinitionScaleVector((FBSkeletonNodeId)lActorIter, lScale);
        }
    }
}

void MyActSetWidget::BindMarkerModel() {
    for (const auto& pair : mIndex->getData()) {
        const char *tracker = pair.first;
        FBModel* model = FBFindModelByLabelName(tracker);

        for (size_t i = 0; i < model->Children.GetCount() && i < 4; ++i) {
            FBModel* child = model->Children.operator[](i);
            const FBSkeletonNodeId nodeid = pair.second;
            actor->MarkerSet->AddMarker(nodeid, child);
        }
    }

    actor->Snap(kFBRecalcMarkerSetOffsetTR);

    FBMessageBox("message",
        "Binding Tracker was completed ! \n Let's play and animate Actor.",
        "OK");
}