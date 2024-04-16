SET(SOURCES screens/ui_Home.c
    screens/ui_Menu.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c)

add_library(ui ${SOURCES})
