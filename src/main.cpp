#include "main.hpp"

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

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
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

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    if(firstActivation) 
    {
        UnityEngine::GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());

        UnityEngine::UI::Toggle* isEnabled = AddConfigValueToggle(container->get_transform(), getClawsConfig().Enabled);
        QuestUI::BeatSaberUI::AddHoverHint(isEnabled->get_gameObject(), "Claws innit");
    }
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    QuestUI::Init();
    QuestUI::Register::RegisterModSettingsViewController(modInfo, DidActivate);

    getLogger().info("Installing Claws hooks...");
    Claws::HookingUtility::InstallHooks(getLogger());
    getLogger().info("Installed all hooks!");
}