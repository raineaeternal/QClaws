#include "GlobalNamespace/ConditionalMaterialSwitcher.hpp"
#include "GlobalNamespace/SaberModelContainer.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/SaberTrailRenderer.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "GlobalNamespace/GamePause.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "include/Utilities/HookingUtility.hpp"
#include "include/Utilities/ClawUtils.hpp"

#include "UnityEngine/Transform.hpp"

namespace Claws {
    MAKE_HOOK_MATCH(SaberModelContainer_Start, &GlobalNamespace::SaberModelContainer::Start, void, GlobalNamespace::SaberModelContainer* self) {
        SaberModelContainer_Start(self);

        auto saber = self->dyn__saber();
        auto saberTop = saber->dyn__saberBladeTopTransform();
        auto saberBottom = saber->dyn__saberBladeBottomTransform();

        saberTop->set_localPosition(UnityEngine::Vector3
            (saberTop->get_localPosition().x, saberTop->get_localPosition().y, saberBottom->get_localPosition().z + 0.3));
    }
}

void InstallClawHooks(Logger& logger) {
     ::Hooking::InstallHook<Claws::Hook_SaberModelContainer_Start>(logger);
}

ClawsInstallHooks(InstallClawHooks);