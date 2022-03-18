#pragma once

#include "config-utils/shared/config-utils.hpp"

DECLARE_CONFIG(ClawsConfig,
    CONFIG_VALUE(Enabled, bool, "Enable Mod", false);

    CONFIG_INIT_FUNCTION(
        CONFIG_INIT_VALUE(Enabled);
    )
)
