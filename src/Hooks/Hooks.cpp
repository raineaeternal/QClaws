#include "GlobalNamespace/ConditionalMaterialSwitcher.hpp"
#include "GlobalNamespace/SaberModelContainer.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/GamePause.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "include/Utilities/HookingUtility.hpp"
#include "include/Utilities/ClawUtils.hpp"

#include "UnityEngine/Transform.hpp"

MAKE_HOOK_MATCH(SaberModelContainer_Start, &GlobalNamespace::SaberModelContainer::Start, void, GlobalNamespace::SaberModelContainer* self) {
    SaberModelContainer_Start(self);

    auto saber = self->dyn__saber();
    auto saberTop = saber->dyn__saberBladeTopTransform();
    auto saberBottom = saber->dyn__saberBladeBottomTransform();

    auto pos = saberTop->get_localPosition();
    pos.z += 0.3;

    saberTop->set_localPosition(pos);
}


void InstallClawHooks(Logger& logger) {
    INSTALL_HOOK(logger, SaberModelContainer_Start)
}

ClawsInstallHooks(InstallClawHooks);