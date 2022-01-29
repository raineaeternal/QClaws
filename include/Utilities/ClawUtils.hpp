#pragma once

#include <map>
#include "UnityEngine/Vector3.hpp"
#include "Enums/Devices.hpp"


namespace Claws {
    class Preference {
        public:
            constexpr static const float length = 0.3f;     // Sets the length
            constexpr static const float width = 0.3f;      // Sets the width
            static UnityEngine::Vector3 leftRotation;       // Defines the left controller rotation
            static UnityEngine::Vector3 rightRotation;      // Defines the right controller rotation
            static UnityEngine::Vector3 leftTranslation;    //
            static UnityEngine::Vector3 rightTranslation;

        std::map<Devices, UnityEngine::Vector3> DefaultTranslation = {
                { Devices::Unknown, UnityEngine::Vector3() },
                { Devices::Quest1,  UnityEngine::Vector3(-0.1, -0.0225, -0.06) },
                { Devices::Quest2,  UnityEngine::Vector3(-0.05, -0.01, -0.1) }
        };

        std::map<Devices, UnityEngine::Vector3> DefaultRotation = {
                { Devices::Unknown, UnityEngine::Vector3() },
                { Devices::Quest1,  UnityEngine::Vector3(25, 0, 90) },
                { Devices::Quest2,  UnityEngine::Vector3(75, -5, 90) }
        };
    };
}
