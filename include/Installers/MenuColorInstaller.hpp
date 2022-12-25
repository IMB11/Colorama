#pragma once

#include "Colorama.hpp"

#include "Zenject/Installer.hpp"

DECLARE_CLASS_CODEGEN(Colorama::Installers, MenuColorInstaller, Zenject::Installer,
                      DECLARE_OVERRIDE_METHOD_MATCH(void, InstallBindings, &Zenject::Installer::InstallBindings);
)