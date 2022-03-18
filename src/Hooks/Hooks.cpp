#include "GlobalNamespace/ConditionalMaterialSwitcher.hpp"
#include "GlobalNamespace/SaberModelContainer.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/GamePause.hpp"
#include "GlobalNamespace/SaberTypeObject.hpp"

#include "GlobalNamespace/OculusVRHelper.hpp"
#include "GlobalNamespace/VRController.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "include/Utilities/HookingUtility.hpp"
#include "include/Utilities/ClawUtils.hpp"

#include "Enums/Devices.hpp"
#include "Utilities/Config.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"

MAKE_HOOK_MATCH(SaberModelContainer_Start, &GlobalNamespace::SaberModelContainer::Start,
                void, GlobalNamespace::SaberModelContainer* self) {
    SaberModelContainer_Start(self);

    if (SaberModelContainer_Start == nullptr) return; {
        if (UnityEngine::SceneManagement::Scene().get_name() == "GameCore") {
            auto saber = self->dyn__saber();
            auto model = self->GetComponent<GlobalNamespace::SaberModelController*>();

            auto saberTop = saber->dyn__saberBladeBottomTransform();
            auto modelTop = model->get_gameObject()->get_transform();

            auto saberPos = saberTop->get_localPosition();
            auto modelScale = modelTop->get_localScale();

            saberPos.z = 0.3f;
            modelScale.z = 0.3f;

            saberTop->set_localPosition(saberPos);
            modelTop->set_localScale(modelScale);
        }
    }
}

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace Claws::Utilities;
MAKE_HOOK_MATCH(ControllerTransform,
                &OculusVRHelper::AdjustControllerTransform,
                void,
                OculusVRHelper* self,
                UnityEngine::XR::XRNode node,
                Transform* transform,
                Vector3 position,
                Vector3 rotation) {
    if (!getClawsConfig().Enabled.GetValue()) {
        return;
    }

    if (node == XR::XRNode::RightHand) {
        auto position = Claws::Utilities::ClawUtils::Preference::DefaultTranslation[Claws::DevicesExtensions::Headset()];
        auto rotation = Claws::Utilities::ClawUtils::Preference::DefaultRotation[Claws::DevicesExtensions::Headset()];
        self->AdjustControllerTransform(node, transform, position, rotation);
    }

    // if (node == XR::XRNode::LeftHand) {
    //     position = Claws::Utilities::ClawUtils::Preference::DefaultTranslation[Claws::DevicesExtensions::Headset()];
    //     rotation = Claws::Utilities::ClawUtils::Preference::DefaultRotation[Claws::DevicesExtensions::Headset()];
    //     self->AdjustControllerTransform(node, transform, position, rotation);
    // }
    ControllerTransform(self, node, transform, position, rotation);
}

void InstallClawHooks(Logger& logger) {
    INSTALL_HOOK(logger, SaberModelContainer_Start)
}

ClawsInstallHooks(InstallClawHooks);