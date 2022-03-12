#include "config-utils/shared/config-utils.hpp"
#include "ClawUtils.hpp"

namespace Claws::Utilities {
    class Config {
        DECLARE_CONFIG(Config,
            CONFIG_VALUE(Enabled, bool, "Enable Mod", false);

            CONFIG_INIT_FUNCTION(
                CONFIG_INIT_VALUE(Enabled);
                )
        );
    };
}