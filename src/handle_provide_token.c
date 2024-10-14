#include "plugin.h"

// Remember, the information for tokens are held in `msg->token1` and `msg->token2`.
// If those pointers are `NULL`, this means the ethereum app didn't
// find any info regarding the requested tokens!
void handle_provide_token(ethPluginProvideInfo_t *msg) {
    msg->result = ETH_PLUGIN_RESULT_OK;
}
