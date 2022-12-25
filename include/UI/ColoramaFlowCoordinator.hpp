#pragma once

#include "Colorama.hpp"

#include "HMUI/FlowCoordinator.hpp"
#include "System/IDisposable.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "Zenject/IInitializable.hpp"

#include "Coloring/Services/ColorizerService.hpp"

#define ColoramaFlowCoordinator_INTERFACES                                     \
  { classof(::Zenject::IInitializable *), classof(::System::IDisposable *) }

___DECLARE_TYPE_WRAPPER_INHERITANCE(
    Colorama::UI, ColoramaFlowCoordinator, Il2CppTypeEnum::IL2CPP_TYPE_CLASS,
    HMUI::FlowCoordinator, "Colorama::UI", ColoramaFlowCoordinator_INTERFACES,
    0, nullptr,
    DECLARE_INSTANCE_FIELD(
        ListWrapper<Colorama::Coloring::Services::ColorizerService *>,
        colorizerServices);
    DECLARE_OVERRIDE_METHOD(void, Initialize,
                            il2cpp_utils::il2cpp_type_check::MetadataGetter<
                                &::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose,
                            il2cpp_utils::il2cpp_type_check::MetadataGetter<
                                &::System::IDisposable::Dispose>::get());
    //    DECLARE_DEFAULT_CTOR();
    //    DECLARE_INSTANCE_METHOD(void, PreviewColor, UnityEngine::Color
    //    colorToChangeTo);
    //
    //    DECLARE_OVERRIDE_METHOD_MATCH(void, Update,
    //    &UnityEngine::MonoBehaviour::Update)
    //
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate,
                                  &HMUI::FlowCoordinator::DidActivate,
                                  bool firstActivation, bool addedToHierarchy,
                                  bool screenSystemEnabling);

    DECLARE_OVERRIDE_METHOD(
        void, BackButtonWasPressed,
        il2cpp_utils::FindMethodUnsafe("HMUI", "FlowCoordinator",
                                       "BackButtonWasPressed", 1),
        HMUI::ViewController *topViewController);

)