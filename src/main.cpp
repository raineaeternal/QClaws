#include "main.hpp"

#include "paper/shared/logger.hpp"

#include "Utilities/HookingUtility.hpp"
#include "include/Utilities/Config.hpp"
#include "config-utils/shared/config-utils.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

DEFINE_CONFIG(ClawsConfig);

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    std::string ID = "Qclaws";

    info.id = ID;
    info.version = VERSION;
    modInfo = info;

    getClawsConfig().Init(modInfo);
	getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}



// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    if (!Paper::Logger::IsInited()) {
        Paper::Logger::Init("/sdcard/Android/data/com.beatgames.beatsaber/files/logs");
    }

    QuestUI::Init();
    QuestUI::Register::RegisterGameplaySetupMenu(modInfo, QuestUI::Register::MenuType::All, GameplaySettings);

    Claws::HookingUtility::InstallHooks(getLogger());

}