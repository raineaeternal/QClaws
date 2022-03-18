#pragma once

#include "GlobalNamespace/OVRPlugin.hpp"
#include "GlobalNamespace/OVRPlugin_SystemHeadset.hpp"

namespace Claws {
    enum class Devices {
        Unknown = -1,
        Quest1 = 0,
        Quest2 = 1
    };

    using namespace GlobalNamespace;
    class DevicesExtensions {
      public:
        static Devices Headset() {
            switch (OVRPlugin::GetSystemHeadsetType()) {
                case OVRPlugin::SystemHeadset::Oculus_Quest_2:
                    return Devices::Quest2;
                case OVRPlugin::SystemHeadset::Oculus_Quest:
                    return Devices::Quest1;
                default:
                    return Devices::Unknown;
            }
        }
    };
}
