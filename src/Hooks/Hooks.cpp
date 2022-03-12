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

#include "include/main.hpp"
#include "Enums/Devices.hpp"
#include "Utilities/Config.hpp"

#include "UnityEngine/Transform.hpp"

MAKE_HOOK_MATCH(SaberModelContainer_Start, &GlobalNamespace::SaberModelContainer::Start,
                void, GlobalNamespace::SaberModelContainer* self) {
    SaberModelContainer_Start(self);

    if (SaberModelContainer_Start == nullptr) return; {
        auto saber = self->dyn__saber();
        auto model = self->GetComponent<GlobalNamespace::SaberModelController*>();

        auto saberTop = saber->dyn__saberBladeTopTransform();
        auto modelTop = model->get_transform();

        auto saberPos = saberTop->get_localPosition();
        auto modelScale = modelTop->get_localScale();

        saberPos.z = Claws::Utilities::Preference::length;
        modelScale.z = Claws::Utilities::Preference::length;

        saberTop->set_localPosition(saberPos);
        modelTop->set_localScale(modelScale);
    }
}

MAKE_HOOK_MATCH(ControllerTransform,
                &OculusVRHelper::AdjustControllerTransform,
                void, OculusVRHelper* self, XR::XRNode node,
                Transform* transform, Vector3 position,
                Vector3 rotation) {
    if (node == UnityEngine::XR::XRNode::RightHand)
        if (Claws::Utilities::Con)

}

void InstallClawHooks(Logger& logger) {
    INSTALL_HOOK(logger, SaberModelContainer_Start)
}

ClawsInstallHooks(InstallClawHooks);