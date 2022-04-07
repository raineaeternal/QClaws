#include "main.hpp"
#include "HMUI/ViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "include/Utilities/Config.hpp"

using namespace QuestUI;

void DidActivate(UnityEngine::GameObject* self, bool firstActivation){
    if(firstActivation)
    {
        UnityEngine::GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());

        UnityEngine::UI::Toggle* isEnabled = AddConfigValueToggle(container->get_transform(), getClawsConfig().Enabled);
        QuestUI::BeatSaberUI::AddHoverHint(isEnabled->get_gameObject(), "Claws innit");
    }
}