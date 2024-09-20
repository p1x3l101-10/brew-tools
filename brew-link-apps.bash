#!/usr/bin/env bash
mkdir -p $HOME/Applications/Homebrew
mkdir -p $HOME/Applications/Sideloaded
mkdir -p $HOME/Applications/WhiskyApps
mkdir -p $HOMEBREW_PREFIX/Applications/Sideloaded
mkdir -p $HOMEBREW_PREFIX/Applications/WhiskyApps
find $HOME/Applications/Homebrew -maxdepth 1 -type l -name '*.app' -exec rm -v {} \;
find $HOME/Applications/Sideloaded -maxdepth 1 -type l -name '*.app' -exec rm -v {} \;

find $HOMEBREW_PREFIX/Applications -maxdepth 1 -type d -name '*.app' -print0 | while IFS='' read -d '' line ; do
  ln -vs "$line" "$HOME/Applications/Homebrew/$(basename "$line")"
done

find $HOMEBREW_PREFIX/Applications/Sideloaded -maxdepth 1 -type d -name '*.app' -print0 | while IFS='' read -d '' line ; do
  ln -vs "$line" "$HOME/Applications/Sideloaded/$(basename "$line")"
done

find $HOMEBREW_PREFIX/Applications/WhiskyApps -maxdepth 1 -type d -name '*.app' -print0 | while IFS='' read -d '' line ; do
  ln -vs "$line" "$HOME/Applications/Sideloaded/$(basename "$line")"
done