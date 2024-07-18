
/*
    Interface for plugin and other debugger-specific functions
*/


#include "send_debugger_command.h"
#include "data.h"
#include "insert_output_marker.h"
#include "parse_debugger_output.h"
#include "update_windows.h"
#include "plugins.h"
#include "utilities.h"
#include "render_window.h"



void
send_debugger_command (int      plugin_index,
                       state_t *state)
{
    bool quitting = false;
    int curr_debugger = state->debugger->curr;

    render_window (HEADER_TITLE_COLOR_ON, -1, plugin_index, state);

    insert_output_start_marker (state);

    switch (plugin_index) {
    case Con:
        switch (curr_debugger) {
        case (DEBUGGER_GDB): send_command (state, 1, "-exec-continue\n"); break;
        }
        break;
    case Fin:
        switch (curr_debugger) {
        case (DEBUGGER_GDB): send_command (state, 1, "-exec-finish\n"); break;
        }
        break;
    case Kil:
        switch (curr_debugger) {
        case (DEBUGGER_GDB): send_command (state, 1, "-exec-abort\n"); break;
        }
        break;
    case Nxt:
        switch (curr_debugger) {
        case (DEBUGGER_GDB): send_command (state, 1, "-exec-next\n"); break;
        }
        break;
    case Stp:
        switch (curr_debugger) {
        case (DEBUGGER_GDB): send_command (state, 1, "step\n"); break;
        }
        break;
    case Run:
        switch (curr_debugger) {
        case (DEBUGGER_GDB): send_command (state, 1, "-exec-run\n"); break;
        }
        break;
    case Unt:
        switch (curr_debugger) {
        case (DEBUGGER_GDB): send_command (state, 2, "-exec-until", "15\n"); break;       // TODO: until
        }
        break;
    case Qut:
        switch (curr_debugger) {
        case (DEBUGGER_GDB): send_command (state, 1, "-gdb-exit\n"); break;
        }
        state->debugger->running = false;
        quitting = true;
    }

    if (!quitting) {

        insert_output_end_marker (state);

        parse_debugger_output (state);

        render_window (DATA, -1, Prm, state);
        render_window (DATA, -1, Out, state);

        render_window (HEADER_TITLE_COLOR_OFF, -1, plugin_index, state);

        update_windows (state, 6, Brk, LcV, Out, Reg, Src, Wat);
    }
}


