#include "plugin.h"

void handle_finalize(ethPluginFinalize_t *msg) {
    context_t *context = (context_t *) msg->pluginContext;

    msg->uiType = ETH_UI_TYPE_GENERIC;

    msg->numScreens = 0;

    if (context->selectorIndex == BATCH_DEPOSIT) {
        msg->numScreens = 3;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
