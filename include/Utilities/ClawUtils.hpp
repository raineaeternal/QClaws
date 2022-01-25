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

            static std::map<> DefaultTranslation();
    };
}
