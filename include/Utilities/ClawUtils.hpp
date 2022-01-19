#pragma once

#include "UnityEngine/Vector3.hpp"

namespace Claws {
    class Preference {
        public:
            constexpr static const float length = 0.3f; // Sets the length
            constexpr static const float width = 0.5f;  // Sets the width
            static UnityEngine::Vector3 leftRotation;   // Defines the left controller rotation
            static UnityEngine::Vector3 rightRotation;  // Defines the right controller rotation
    };
}
