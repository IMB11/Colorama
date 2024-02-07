#pragma once

#include "Colorama.hpp"
#include "HMUI/ImageView.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "Utilities/SettingsPanelObjectGrabber.hpp"
#include "custom-types/shared/coroutine.hpp"

#define VOID_VECT3 UnityEngine::Vector3(0.0f, -1000.0f, 0.0f)
#define DEFAULT_GRABBER_POS UnityEngine::Vector3(3.53f, 1.1f, 2.4f)

DECLARE_CLASS_CODEGEN(
    Colorama::UI, PreviewViewController, HMUI::ViewController,
    DECLARE_INSTANCE_FIELD(Colorama::Utilities::SettingsPanelObjectGrabber*,
                           objectGrabber);
    DECLARE_INSTANCE_FIELD_DEFAULT(bool, previewToggleIsReady, false);
    DECLARE_INSTANCE_FIELD_DEFAULT(int, currentTab, -1);

    DECLARE_INSTANCE_FIELD(ArrayW<UnityEngine::UI::Image*>, multiplierCircles);
    DECLARE_INSTANCE_FIELD(HMUI::CurvedTextMeshPro*, multiplierText);
    DECLARE_INSTANCE_FIELD_DEFAULT(bool, previewCoroOn8x, false);

    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Image*, energyBar);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, fillAmount, 0.01f);

    DECLARE_INSTANCE_FIELD(ArrayW<HMUI::ImageView*>, comboLines);
    DECLARE_INSTANCE_FIELD(HMUI::CurvedTextMeshPro*, numText);
    DECLARE_INSTANCE_FIELD(HMUI::CurvedTextMeshPro*, comboText);

    DECLARE_INSTANCE_FIELD(ArrayW<UnityEngine::UI::Image*>,
                           progressPanelImages);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, progressFillAmount, 0.01f);

    DECLARE_INSTANCE_FIELD(HMUI::CurvedTextMeshPro*, scoreText);
    DECLARE_INSTANCE_FIELD(HMUI::CurvedTextMeshPro*, percentageText);
    DECLARE_INSTANCE_FIELD(HMUI::CurvedTextMeshPro*, rankText);
    DECLARE_INSTANCE_FIELD_DEFAULT(float, rank, 0.00f);

    DECLARE_INSTANCE_METHOD(void, UpdateEnergyBar);
    DECLARE_INSTANCE_METHOD(void, UpdateComboPanel);
    DECLARE_INSTANCE_METHOD(void, UpdateProgressBar);

    DECLARE_INSTANCE_METHOD(void, UpdatePanelVisibility, int idx);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate,
                                  &HMUI::ViewController::DidActivate,
                                  bool firstActivation, bool addedToHierarchy,
                                  bool screenSystemEnabling);
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidDeactivate,
                                  &HMUI::ViewController::DidDeactivate,
                                  bool removedFromHierarchy,
                                  bool screenSystemDisabling);
    DECLARE_INSTANCE_METHOD(void, Update); DECLARE_DEFAULT_CTOR(); public
    : custom_types::Helpers::Coroutine FinalizePanels();
    custom_types::Helpers::Coroutine MultiplierPreviewCoroutine();)