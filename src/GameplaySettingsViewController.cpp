#include "main.hpp"
#include "HMUI/ViewController.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "include/Utilities/Config.hpp"
#include "Utilities/GameplaySettingsViewController.hpp"
#include "questui/shared/CustomTypes/Components/WeakPtrGO.hpp"

using namespace QuestUI;

WeakPtrGO<UnityEngine::GameObject> settingsGO;

UnityEngine::Transform* GetSubcontainer(UnityEngine::UI::VerticalLayoutGroup* vertical) {
    auto horizontal = BeatSaberUI::CreateHorizontalLayoutGroup(vertical);
    horizontal->GetComponent<UnityEngine::UI::LayoutElement*>()->set_minHeight(8);
    horizontal->set_childForceExpandHeight(true);
    horizontal->set_childAlignment(UnityEngine::TextAnchor::MiddleCenter);
    return horizontal->get_transform();
}

void DidActivate(UnityEngine::GameObject* gameObject, bool firstActivation){
    if(firstActivation)
    {
        auto* container = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(gameObject->get_transform());
        container->get_rectTransform()->set_anchoredPosition({0, 31});
        UnityEngine::UI::Toggle* isEnabled = BeatSaberUI::CreateToggle(GetSubcontainer(container), getClawsConfig().Enabled.GetName(), getClawsConfig().Enabled.GetValue(), [](bool enabled) {
            getClawsConfig().Enabled.SetValue(enabled);
        });
        QuestUI::BeatSaberUI::AddHoverHint(isEnabled->get_gameObject(), "Claws innit");
    }
    settingsGO = gameObject;
}