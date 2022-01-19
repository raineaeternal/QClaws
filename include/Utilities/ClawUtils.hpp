//
// Created by Dawn on 1/19/2022.
//

#ifndef QCLAWS_CLAWUTILS_HPP
#define QCLAWS_CLAWUTILS_HPP

#include "include/UnityEngine.hpp"

namespace Claws {
    class Preference
        public:
            static const float length = 0.3f;           // Sets the length
            static const float width = 0.5f;            // Sets the width
            static UnityEngine::Vector3 leftRotation;   // Defines the left controller rotation
            static UnityEngine::Vector3 rightRotation;  // Defines the right controller rotation

}

#endif //QCLAWS_CLAWUTILS_HPP
