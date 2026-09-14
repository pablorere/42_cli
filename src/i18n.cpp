#include "i18n.hpp"
#include "config.hpp"

#include <algorithm>
#include <unordered_map>

namespace i18n {

std::string language() {
    std::string lang = Config::get().language;
    std::transform(lang.begin(), lang.end(), lang.begin(),
                   [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return lang == "es" ? "es" : "en";
}

static const std::unordered_map<std::string, std::string>& table_en() {
    static const std::unordered_map<std::string, std::string> t = {
        // Menu items
        {"resume",              "Resume"},
        {"settings",            "Settings"},
        {"theme_chooser",       "Theme chooser"},
        {"help",                "Help"},
        {"about",               "About"},
        {"logout",              "Logout / switch account"},
        {"quit",                "Quit"},

        // Titles
        {"menu_title",          " MENU "},
        {"settings_title",      " SETTINGS "},
        {"help_title",          " HELP "},
        {"about_title",         " ABOUT "},
        {"edit_title",          " EDIT "},
        {"logout_confirm_title"," LOGOUT "},
        {"discard_confirm_title"," DISCARD CHANGES "},

        // Footers
        {"menu_footer",         "[j/k] Move  [Enter] Select  [Esc] Resume"},
        {"settings_footer",     "[j/k] Move  [< >] Adjust  [Enter] Edit  [Esc] Back"},
        {"settings_footer_dirty","[j/k] Move  [< >] Adjust  [Enter] Edit  [s] Save  [Esc] Back  • unsaved"},
        {"help_footer",         "[j/k] Scroll  [Esc] Back"},
        {"about_footer",        "[Esc] Back"},
        {"edit_footer",         "[Enter] OK  [Esc] Cancel"},
        {"confirm_footer",      "[Y] Yes   [N/Esc] Cancel"},
        {"yes",                 "Yes"},
        {"no",                  "No"},

        // Settings labels
        {"set_theme",           "Theme"},
        {"set_border",          "Border style"},
        {"set_offset",          "Slot offset (min)"},
        {"set_duration",        "Default slot duration (min)"},
        {"set_glow",            "Box glow"},
        {"set_cookie",          "Cookie path"},
        {"set_start_tab",       "Startup tab"},
        {"set_confirm_quit",    "Confirm before quit"},
        {"set_language",        "Language"},
        {"save",                "Save settings"},

        // Values
        {"on",                  "on"},
        {"off",                 "off"},
        {"border_rounded",      "rounded"},
        {"border_sharp",        "sharp"},
        {"border_double",       "double"},
        {"tab_dashboard",       "Dashboard"},
        {"tab_roadmap",         "Roadmap"},
        {"tab_slots",           "Slots"},
        {"tab_cluster",         "Cluster"},
        {"lang_en",             "English"},
        {"lang_es",             "Español"},

        // Confirms / messages
        {"logout_confirm_msg",  "Delete the session cookie and return to login?"},
        {"discard_confirm_msg", "Discard unsaved settings changes?"},
        {"msg_settings_saved",  "Settings saved"},
        {"msg_settings_discarded","Changes discarded"},
        {"msg_logged_out",      "Logged out — session cookie removed"},
        {"msg_quit_armed",      "Press q again to quit"},

        // About
        {"about_version",       "Version"},
        {"about_repo",          "Repository"},
        {"about_license",       "License"},
        {"about_config",        "Config file"},
        {"about_data",          "Data dir"},
        {"about_deps",          "Built against"},
        {"about_curl",          "libcurl"},
        {"about_ncurses",       "ncurses"},
    };
    return t;
}

static const std::unordered_map<std::string, std::string>& table_es() {
    static const std::unordered_map<std::string, std::string> t = {
        {"resume",              "Reanudar"},
        {"settings",            "Ajustes"},
        {"theme_chooser",       "Selector de tema"},
        {"help",                "Ayuda"},
        {"about",               "Acerca de"},
        {"logout",              "Cerrar sesión / cambiar cuenta"},
        {"quit",                "Salir"},

        {"menu_title",          " MENÚ "},
        {"settings_title",      " AJUSTES "},
        {"help_title",          " AYUDA "},
        {"about_title",         " ACERCA DE "},
        {"edit_title",          " EDITAR "},
        {"logout_confirm_title"," CERRAR SESIÓN "},
        {"discard_confirm_title"," DESCARTAR CAMBIOS "},

        {"menu_footer",         "[j/k] Mover  [Enter] Elegir  [Esc] Reanudar"},
        {"settings_footer",     "[j/k] Mover  [< >] Ajustar  [Enter] Editar  [Esc] Volver"},
        {"settings_footer_dirty","[j/k] Mover  [< >] Ajustar  [Enter] Editar  [s] Guardar  [Esc] Volver  • sin guardar"},
        {"help_footer",         "[j/k] Desplazar  [Esc] Volver"},
        {"about_footer",        "[Esc] Volver"},
        {"edit_footer",         "[Enter] OK  [Esc] Cancelar"},
        {"confirm_footer",      "[Y] Sí   [N/Esc] Cancelar"},
        {"yes",                 "Sí"},
        {"no",                  "No"},

        {"set_theme",           "Tema"},
        {"set_border",          "Estilo de borde"},
        {"set_offset",          "Desfase de slot (min)"},
        {"set_duration",        "Duración por defecto (min)"},
        {"set_glow",            "Brillo de cajas"},
        {"set_cookie",          "Ruta de cookies"},
        {"set_start_tab",       "Pestaña inicial"},
        {"set_confirm_quit",    "Confirmar al salir"},
        {"set_language",        "Idioma"},
        {"save",                "Guardar ajustes"},

        {"on",                  "activado"},
        {"off",                 "desactivado"},
        {"border_rounded",      "redondeado"},
        {"border_sharp",        "recto"},
        {"border_double",       "doble"},
        {"tab_dashboard",       "Panel"},
        {"tab_roadmap",         "Ruta"},
        {"tab_slots",           "Slots"},
        {"tab_cluster",         "Cluster"},
        {"lang_en",             "English"},
        {"lang_es",             "Español"},

        {"logout_confirm_msg",  "¿Eliminar la cookie de sesión y volver al login?"},
        {"discard_confirm_msg", "¿Descartar los cambios sin guardar?"},
        {"msg_settings_saved",  "Ajustes guardados"},
        {"msg_settings_discarded","Cambios descartados"},
        {"msg_logged_out",      "Sesión cerrada — cookie eliminada"},
        {"msg_quit_armed",      "Pulsa q otra vez para salir"},

        {"about_version",       "Versión"},
        {"about_repo",          "Repositorio"},
        {"about_license",       "Licencia"},
        {"about_config",        "Archivo de config"},
        {"about_data",          "Directorio de datos"},
        {"about_deps",          "Compilado con"},
        {"about_curl",          "libcurl"},
        {"about_ncurses",       "ncurses"},
    };
    return t;
}

std::string tr(const std::string& key) {
    const auto& t = (language() == "es") ? table_es() : table_en();
    auto it = t.find(key);
    if (it != t.end()) return it->second;
    auto en = table_en().find(key);
    return en != table_en().end() ? en->second : key;
}

static const std::vector<std::string>& help_en() {
    static const std::vector<std::string> lines = {
        " NAVIGATION",
        "   h j k l        Vim movement across tabs, trees and lists",
        "   Tab / S-Tab    Next / previous tab",
        "   gt / gT        Next / previous tab",
        "   1 2 3 4        Jump to Dashboard / Roadmap / Slots / Cluster",
        "   [ / ]          Cycle Dashboard subviews / Cluster rooms",
        "   /              Focus global search (online users + projects)",
        "   Esc            Open the main menu",
        "   q              Quit (press twice to confirm)",
        "",
        " MAIN MENU",
        "   Esc            Open the menu; Esc again to resume",
        "   s              Settings",
        "   t              Theme chooser",
        "   h              Help",
        "   a              About",
        "   l              Logout / switch account",
        "   q              Quit (press twice)",
        "",
        " SETTINGS",
        "   j / k          Move between settings",
        "   < / >          Adjust the selected value",
        "   Enter          Edit the value in a popup",
        "   s / Save row   Persist changes to config.ini",
        "   *              Marks a value changed but not yet saved",
        "",
        " DASHBOARD",
        "   [ / ]          Overview / Scale Teams / Points & Pool",
        "   Enter / f      Inspect pending feedback and critiques",
        "   Click minimap  Open the hovered user's profile",
        "",
        " ROADMAP",
        "   Space / Enter  Expand milestone / open project action menu",
        "   p              Preview the downloaded subject PDF",
        "   s / d          Download subject PDF",
        "   n / p          Next / previous PDF page (preview open)",
        "",
        " SLOTS",
        "   s              Create a slot",
        "   d              Trim the last 15 minutes",
        "   D / x          Delete the selected slot block",
        "",
        " CLUSTER",
        "   h j k l        Move between occupied desks",
        "   [ / ] / c      Switch cluster room",
        "   Enter          Open the selected user's profile",
        "   y              Copy the selected login to the clipboard",
        "",
        " SEARCH",
        "   /              Focus the search bar; type to filter",
        "   Up / Down      Move through results",
        "   Enter          Open the selected result",
        "   Esc            Clear the query, then leave",
        "",
        " MOUSE",
        "   Click          Tabs, lists, desks, menu rows",
        "   Wheel          Scroll lists and the menu",
        "   Right-click    Copy a cluster login",
    };
    return lines;
}

static const std::vector<std::string>& help_es() {
    static const std::vector<std::string> lines = {
        " NAVEGACIÓN",
        "   h j k l        Movimiento vim por pestañas, árboles y listas",
        "   Tab / S-Tab    Pestaña siguiente / anterior",
        "   gt / gT        Pestaña siguiente / anterior",
        "   1 2 3 4        Ir a Panel / Ruta / Slots / Cluster",
        "   [ / ]          Cambiar subvistas / salas del Cluster",
        "   /              Enfocar búsqueda global (usuarios y proyectos)",
        "   Esc            Abrir el menú principal",
        "   q              Salir (pulsa dos veces para confirmar)",
        "",
        " MENÚ PRINCIPAL",
        "   Esc            Abrir el menú; Esc de nuevo para reanudar",
        "   s              Ajustes",
        "   t              Selector de tema",
        "   h              Ayuda",
        "   a              Acerca de",
        "   l              Cerrar sesión / cambiar cuenta",
        "   q              Salir (pulsa dos veces)",
        "",
        " AJUSTES",
        "   j / k          Mover entre ajustes",
        "   < / >          Ajustar el valor seleccionado",
        "   Enter          Editar el valor en una ventana",
        "   s / Guardar    Guardar los cambios en config.ini",
        "   *              Marca un valor modificado sin guardar",
        "",
        " PANEL",
        "   [ / ]          Vista general / Scale Teams / Puntos y pool",
        "   Enter / f      Inspeccionar feedback y críticas pendientes",
        "   Clic minimapa  Abrir el perfil del usuario señalado",
        "",
        " RUTA",
        "   Espacio/Enter  Expandir hito / abrir menú de proyecto",
        "   p              Previsualizar el PDF descargado",
        "   s / d          Descargar PDF del proyecto",
        "   n / p          Página siguiente / anterior (vista previa)",
        "",
        " SLOTS",
        "   s              Crear un slot",
        "   d              Recortar los últimos 15 minutos",
        "   D / x          Eliminar el bloque de slot seleccionado",
        "",
        " CLUSTER",
        "   h j k l        Moverse entre puestos ocupados",
        "   [ / ] / c      Cambiar de sala",
        "   Enter          Abrir el perfil del usuario seleccionado",
        "   y              Copiar el login al portapapeles",
        "",
        " BÚSQUEDA",
        "   /              Enfocar la barra de búsqueda; escribe para filtrar",
        "   Arriba/Abajo   Moverse por los resultados",
        "   Enter          Abrir el resultado seleccionado",
        "   Esc            Borrar la consulta y salir",
        "",
        " RATÓN",
        "   Clic           Pestañas, listas, puestos, filas del menú",
        "   Rueda          Desplazar listas y el menú",
        "   Clic derecho   Copiar el login del cluster",
    };
    return lines;
}

const std::vector<std::string>& help_lines() {
    return language() == "es" ? help_es() : help_en();
}

} // namespace i18n
