#pragma once

#include <optional>
#include <string>

using std::optional;
using std::string;

namespace ox
{
    /// Który gracz ma pierwszy ruch.
    enum ConfigStart
    {
        CROSS,
        CIRCLE
    };

    /// Z jakiej taktyki korzystają boty.
    enum ConfigBotTactic
    {
        HEURISTIC,
        GAME_TREE
    };

    /// Rozmiar interfejsu gracza.
    enum ConfigUiSize
    {
        SMALL,
        MEDIUM,
        LARGE,
        RESIZABLE,
    };

    /// \brief Plik konfiguracyjny gry.
    /// \details
    /// Jest wczytywany ze zmiennych ze skryptu w pythonie o nazwie config.py
    /// w katalogu w którym uruchomiony został program lub ze ścieżki
    /// podanej jako argument wywołania programu.
    /// Możliwe konfiguracje widoczne w pliku config.py w głównym folderze projektu.
    struct Config
    {
        /// Czy krzyżykiem steruje bot.
        bool cross_is_bot;
        /// Czy kółkiem steruje bot.
        bool circle_is_bot;
        /// Który gracz rozpoczyna grę.
        ConfigStart start;
        /// Jaką taktyką posługują się boty.
        ConfigBotTactic bot_tactic;
        /// Rozmiar interfejsu gracza.
        ConfigUiSize ui_size;
        /// Głębokość przeszukiwania drzewa w przypadku taktyki GAME_TREE botów.
        int depth;
        /// Ścieżka do pliku z zapisaną grą.
        std::string save_path;

        /// Spróbuj wczytać plik konfiguracyjny z tekstu skryptu python.
        static std::optional<Config> try_from_script(const char *config_string);
    };

} // namespace ox
