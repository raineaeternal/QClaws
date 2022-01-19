#pragma once
#include "main.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

namespace Claws {
    class HookingUtility {
    private:
        inline static std::vector<void (*)(Logger &logger)> installFuncs;
    public:
        static void AddInstallFunc(void (*installFunc)(Logger &logger)) {
            installFuncs.push_back(installFunc);
        }

        static void InstallHooks(Logger &logger) {
            for (auto installFunc : installFuncs) {
                installFunc(logger);
            }
        }
    };
}
#define ClawsInstallHooks(func) \
struct __ClawsRegister##func { \
    __ClawsRegister##func() { \
       Claws::HookingUtility::AddInstallFunc(func); \
    } \
}; \
static __ClawsRegister##func __ClawsRegisterInstance##func