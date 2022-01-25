#include "include/Utilities/ClawUtils.hpp"

namespace Claws {
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
}
