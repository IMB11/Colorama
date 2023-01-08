# Colorama

Colorama is a mod for Beat Saber on the Meta Quest 2 and Meta Quest 2 Pro that allows you to change the atmospheric colors of each menu location.

Download from the releases page.

## Contribution

Contributions are accepted, please respect the license when creating a PR and keep code standards high (where possible).

## Compiling

If you want to build colorama yourself, you will need Ninja, CMake, and qpm-rust installed. 

Run these commands in order to create a QMod file that can be uploaded to QuestPatcher or BMBF.

```shell
qpm-rust restore # restore QPM dependencies
./build.ps1 -Clean
./createqmod.ps1 Colorama
```

