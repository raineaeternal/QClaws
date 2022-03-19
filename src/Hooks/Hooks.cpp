#include "GlobalNamespace/ConditionalMaterialSwitcher.hpp"
#include "GlobalNamespace/SaberModelContainer.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/GamePause.hpp"
#include "GlobalNamespace/SaberTypeObject.hpp"
#include "GlobalNamespace/SaberTrail.hpp"

#include "GlobalNamespace/OculusVRHelper.hpp"
#include "GlobalNamespace/VRController.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "include/Utilities/HookingUtility.hpp"
#include "include/Utilities/ClawUtils.hpp"

#include "Enums/Devices.hpp"
#include "Utilities/Config.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/SceneManagement/Scene.hpp"
#include "UnityEngine/SceneManagement/SceneManager.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace Claws::Utilities;

MAKE_HOOK_MATCH(SaberModelContainer_Start, &SaberModelContainer::Start, void, SaberModelContainer* self) {
    SaberModelContainer_Start(self);
    if (!getClawsConfig().Enabled.GetValue()) return;
    if (SceneManagement::SceneManager::GetActiveScene().get_name() == "GameCore") {
        getLogger().info("knob 3");
        auto saber = self->dyn__saber();
        auto model = self->get_transform()->GetComponentInChildren<SaberModelController*>(); // the previous line of this was causing a null deref lol

        auto saberTop = saber->dyn__saberBladeBottomTransform();
        auto saberIdk = model->dyn__saberTrail()->get_gameObject()->get_transform()->get_parent(); // dunno why this works but it moves both saber and trail

        auto saberPos = saberTop->get_localPosition();
        auto saberScale = saberIdk->get_localScale();

        saberPos.z = 0.3f;
        saberScale.z = 0.3f;
        
        saberIdk->set_localScale(saberScale);
        saberTop->set_localPosition(saberPos);
    }
}

Vector3 Mirror(Vector3 toMirror, bool isRot){
    return isRot ? Vector3(toMirror.x, -1 * toMirror.y, -1 * toMirror.z) : Vector3(-1 * toMirror.x, toMirror.y, toMirror.z);

}

MAKE_HOOK_MATCH(ControllerTransform,
                &OculusVRHelper::AdjustControllerTransform,
                void,
                OculusVRHelper* self,
                XR::XRNode node,
                Transform* transform,
                Vector3 position,
                Vector3 rotation) {
    if (getClawsConfig().Enabled.GetValue()) {
        if (node == XR::XRNode::RightHand){
            if (transform->get_name() == "RightHand"){ //only applies to sabers while in level
                position = position + ClawUtils::Preference::DefaultTranslation[Claws::DevicesExtensions::Headset()];
                rotation = rotation + ClawUtils::Preference::DefaultRotation[Claws::DevicesExtensions::Headset()];
            }
        }
        else if (node == XR::XRNode::LeftHand){
            if (transform->get_name() == "LeftHand"){
                position = position + Mirror(ClawUtils::Preference::DefaultTranslation[Claws::DevicesExtensions::Headset()], false);
                rotation = rotation + Mirror(ClawUtils::Preference::DefaultRotation[Claws::DevicesExtensions::Headset()], true);
            }
        }
        ControllerTransform(self, node, transform, position, rotation);
    }
} 

void InstallClawHooks(Logger& logger) {
    INSTALL_HOOK(logger, SaberModelContainer_Start)
    INSTALL_HOOK(logger, ControllerTransform)
}

ClawsInstallHooks(InstallClawHooks);