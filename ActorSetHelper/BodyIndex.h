#ifndef BODYINDEX_H
#define BODYINDEX_H

#include <fbsdk/fbsdk.h>
#include <unordered_map>
#include <string>

class MyActSet_MarkertSetIndex {
private:
    std::unordered_map<const char*, FBSkeletonNodeId> data;

public:
    MyActSet_MarkertSetIndex() {
        data = {
            // for HipTracker
            { "HipTracker", kFBSkeletonHipsIndex },

            // for LeftKnee / Foot Tracker
            { "LeftKneeTracker", kFBSkeletonLeftKneeIndex },
            { "LeftFootTracker", kFBSkeletonLeftAnkleIndex },

            // for RightKnee / Foot Tracker
            { "RightKneeTracker", kFBSkeletonRightKneeIndex },
            { "RightFootTracker", kFBSkeletonRightAnkleIndex },

            // for BodyTracker
            { "BodyTracker", kFBSkeletonChestIndex },

            // for LeftShoulder / Elbow / Hand Tracker
            { "LeftShoulderTracker", kFBSkeletonLeftCollarIndex },
            { "LeftElbowTracker", kFBSkeletonLeftElbowIndex },
            { "LeftHandTracker", kFBSkeletonLeftWristIndex },

            // for RightShoulder / Elbow / Hand Tracker
            { "RightShoulderTracker", kFBSkeletonRightCollarIndex },
            { "RightElbowTracker", kFBSkeletonRightElbowIndex },
            { "RightHandTracker", kFBSkeletonRightWristIndex },

            // for headTracker
            { "headTracker", kFBSkeletonHeadIndex },
        };
    }

    ~MyActSet_MarkertSetIndex() {}

    std::unordered_map<const char*, FBSkeletonNodeId> getData() {
        return data;
    }
};

#endif // BODYINDEX_H
