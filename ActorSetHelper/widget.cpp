#include "widget.h"

/* Impremented Qt Widget : MyActSetWidget */
MyActSetWidget::MyActSetWidget(QWidget* pParent) : QWidget(pParent)
{
	setupUi(this); // from ui_actorsethelper.h
    sys = new FBSystem();
    mIndex = new MyActSet_MarkertSetIndex();
}

MyActSetWidget::~MyActSetWidget() {
    delete sys;
    delete mIndex;
}


/************* UI Functions ************/

/* Create new Actor and MarkerSet */
void MyActSetWidget::CreateActorMarkerSet() {
    actor = new FBActor("NewActor");
    actor->MarkerSet = new FBMarkerSet("NewMarkerSet");
}


/* Fetch Actor to Selected Model */
void MyActSetWidget::FitToTrackers() {
    if (actor != nullptr) {
        FBModelList targetmodel;
        FBVector3d  targetposition;
        FBGetSelectedModels(targetmodel);

        if (targetmodel.GetCount() == 0) {
            FBMessageBox("Caution", "Error : No Model Selected", "OK");
        }
        else {
            targetmodel.GetAt(0)->GetVector(targetposition, kModelTransformation);
            actor->SetActorTranslation(targetposition);
        }
    }
}


/* Rotate Actor by 180 degrees */
void MyActSetWidget::RotateYdeg() {
    if ( actor != nullptr ) {
        FBVector3d hipvector;
        FBVector3d resultvector;
        actor->GetDefinitionRotationVector(kFBSkeletonHipsIndex, hipvector);
        resultvector = FBVector3d(hipvector[0], hipvector[1] + 180, hipvector[2]);
        actor->SetDefinitionRotationVector(kFBSkeletonHipsIndex, resultvector);
    }
}


/* Delete Created both Actor and MarkerSet */
void MyActSetWidget::ResetAll() {
    if (actor == nullptr) {
        FBMessageBox("Caution", "Error : Created Actor or MarkerSet already removed.", "OK");
    }
    else {
        int check = FBMessageBox("Caution",
            "the Actor and MarkerSet will be removed. \nAre you sure you want to continue?",
            "Yes", "No");
        if (check == 1) {
            actor->MarkerSet->FBDelete();
            actor->FBDelete();
            horizontalSlider->setSliderPosition(50);
            actor = nullptr;
        }
    }
}


/* Change Actor Size by slider */
void MyActSetWidget::AdjustActorSize(int pValue) {
    if (actor != nullptr) {
        FBVector3d lScale(pValue / 50.0, pValue / 50.0, pValue / 50.0);

        // Chagnge Scale at Actor SkeletonIndex other than invalid, reference, last index
        for (int lActorIter = kFBSkeletonHipsIndex; lActorIter < kFBSkeletonReferenceIndex; lActorIter++) {
            actor->SetDefinitionScaleVector((FBSkeletonNodeId)lActorIter, lScale);
        }
    }
}


/* Register Markers and Snap Actor */
void MyActSetWidget::BindMarkerModel() {
    if (actor == nullptr) {
        FBMessageBox("Caution", "Error : Created Actor or MarkerSet not found", "OK");
    }
    else {
        int trackerNumber = 20;
        int counter = 0;

        // Search for all trackers in mIndex from BodyIndex.h
        for (const auto& pair : mIndex->getData()) {
            const char* tracker = pair.first;
            FBModel* model = FBFindModelByLabelName(tracker);

            if (model == nullptr) {
                break;
            }

            // Add 4 children models to MarkerSet
            for (size_t i = 0; i < model->Children.GetCount() && i < 4; ++i) {
                FBModel* child = model->Children.operator[](i);
                const FBSkeletonNodeId nodeid = pair.second;
                actor->MarkerSet->AddMarker(nodeid, child);
                counter += 1;
            }
        }

        if (counter == trackerNumber) {
            // Execute Snap 
            actor->Snap(kFBRecalcMarkerSetOffsetTR);

            FBMessageBox("message",
                "Binding Tracker was completed ! \n Check Actor Settings before playing.",
                "OK");
        }
        else {
            FBMessageBox("Caution", "Error : Some Tracker not found.\nCheck Scene data and Actor Settings.", "OK");
        }
    }
}