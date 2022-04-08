#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ClawsConfig,
    CONFIG_VALUE(Enabled, bool, "Enable Mod", false);
    CONFIG_VALUE(UseDefaultSaber, bool, "Use Default Saber", false);
    CONFIG_VALUE(ThinSaber, bool, "Use Thin Sabers", false);
    CONFIG_VALUE(UseQosmetics, bool, "Use Qosmetics Saber", false); // Waiting for the Qosmetics Rewrite to be done.

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(Enabled);
        CONFIG_INIT_VALUE(UseDefaultSaber)
        CONFIG_INIT_VALUE(ThinSaber);
        CONFIG_INIT_VALUE(UseQosmetics); // Currently unused
    )
)
