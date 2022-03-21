#pragma once

#include <map>
#include "UnityEngine/Vector3.hpp"
#include "Enums/Devices.hpp"
#include "UnityEngine/XR/XRNode.hpp"

namespace Claws::Utilities::ClawUtils {
    class Preference {
    public:
        constexpr static const float length = 0.3f;         // Sets the length
        constexpr static const float width = 0.3f;          // Sets the width, currently unused.

        static inline std::map<Devices, UnityEngine::Vector3> DefaultTranslation = {
                {Devices::Unknown, UnityEngine::Vector3()},
                {Devices::Quest1,  UnityEngine::Vector3(-0.005, 0, -0.1)},
                {Devices::Quest2,  UnityEngine::Vector3(-0.005, 0.01, -0.1)}
        };

        static inline std::map<Devices, UnityEngine::Vector3> DefaultRotation = {
                {Devices::Unknown, UnityEngine::Vector3()},
                {Devices::Quest1,  UnityEngine::Vector3(25, 0, 90)},
                {Devices::Quest2,  UnityEngine::Vector3(25, -5, 90)}
        };
    };
}
